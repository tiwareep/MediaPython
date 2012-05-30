/**
 * glim-dbus.c
 *   Some simple utilities for dealing with D-Bus.
 *
 * Copyright (c) 2011 Samuel A. Rebelsky
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

// +---------+--------------------------------------------------------
// | Headers |
// +---------+ 

#include <glib-object.h>

#include <dbus/dbus-glib.h>

#include "glim-debug.h"
#include "glim-dbus.h"


// +--------------------+---------------------------------------------
// | Exported Functions |
// +--------------------+ 

DBusGConnection *
glim_dbus_create_service (const gchar *name)
{
  GError *error;                // Error returned by call
  DBusGConnection *connection;  // A connection to the main application
  DBusGProxy *proxy;            // The proxy
  int ok;			// The return value from dbus_g_proxy_call 
  int result;                   // The result from dbus_g_proxy_call

  // Create the connection
  error = NULL;
  connection = dbus_g_bus_get (DBUS_BUS_SESSION, &error);
  if ((! connection) || error)
    {
      g_printerr ("Error getting bus: %s\n", error->message);
      g_error_free (error);
      return NULL;
    }

  // Create the proxy to the main dbus thing
  proxy = dbus_g_proxy_new_for_name (connection,
                                     DBUS_SERVICE_DBUS,
                                     DBUS_PATH_DBUS,
                                     DBUS_INTERFACE_DBUS);
  if (proxy == NULL)
    {
      g_printerr ("Error: Failed to create proxy to D-Bus.\n");
      return NULL;
    }
 
  // Request the name (finally, we're at the real part)
  error = NULL;
  int flag = DBUS_NAME_FLAG_ALLOW_REPLACEMENT 
           & DBUS_NAME_FLAG_REPLACE_EXISTING;

  ok = dbus_g_proxy_call (proxy,
                          "RequestName",
                          &error,
                          G_TYPE_STRING,
                          name,
                          G_TYPE_UINT, flag,
                          G_TYPE_INVALID,
                          G_TYPE_UINT, &result,
                          G_TYPE_INVALID);
  if (! ok)
    {
      g_printerr ("Error registering name: %s\n", error->message);
      g_error_free (error);
      g_object_unref (proxy);
      return NULL;
    }
  switch (result)
    {
      case -1:
        if (error != NULL)
          {
            g_printerr ("Error requesting name: %s\n", error->message);
            g_error_free (error);
            return NULL;
          }
        else
          {
            g_printerr ("Error requesting name.\n");
            return NULL;
          }

      case DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER:
        return connection;

      case DBUS_REQUEST_NAME_REPLY_IN_QUEUE:
        g_printerr ("Error requesting name: Service could not become the primary owner and has been placed in the queue.\n");
        return NULL;

      case DBUS_REQUEST_NAME_REPLY_EXISTS:
        g_printerr ("Error requesting name: Service is already in the queue.\n");
        return NULL;
      
      case DBUS_REQUEST_NAME_REPLY_ALREADY_OWNER:
        g_printerr ("Error requesting name: Service is already the primary owner.\n");
        return NULL;

      default:
        g_printerr ("Error requesting name: Unknown error (result = %d)\n",
                    result);
        return NULL;
    } // switch
} // glim_dbus_create_service

GArray *
glim_dbus_ints_to_g_array (gint n, gint *ints)
{
  GArray *result = g_array_sized_new (FALSE, FALSE, sizeof (gint), n);
  g_array_append_vals (result, ints, n);
  return result;
} // glim_gimpbus_ints_to_garray

