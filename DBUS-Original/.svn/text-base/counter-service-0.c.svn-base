/**
 * counter-service.c
 *   A simple DBUS service.  All it does is count.  You can increment
 *   it and get its value.
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
#include <gtk/gtk.h>

#include <dbus/dbus-glib.h>

#include "glim-counter.h"


// +------+-----------------------------------------------------------
// | Main |
// +------+ 

int
main (int argc, char *argv[])
{
  GError *error;                // Error returned by call
  DBusGConnection *connection;  // A connection to the main application
  DBusGProxy *proxy;            // The proxy
  GObject *object;              // An object we're registering
  int ok;			// For checking whether stuff is ok
  int result;                   // The result from dbus_g_proxy_call

  // Set up GTK
  gtk_init (&argc, &argv);

  // Create the connection
  error = NULL;
  connection = dbus_g_bus_get (DBUS_BUS_SESSION, &error);
  if ((! connection) || error)
    {
      g_printerr ("Error getting bus: %s\n", error->message);
      g_error_free (error);
      return 1; // Failure
    }

  // Create the proxy to the main dbus thing
  proxy = dbus_g_proxy_new_for_name (connection,
                                     DBUS_SERVICE_DBUS,
                                     DBUS_PATH_DBUS,
                                     DBUS_INTERFACE_DBUS);
  if (proxy == NULL)
    {
      g_printerr ("Error: Failed to create proxy to Dbus.\n");
      return 1;
    }

  // Tell the proxy about the name that we want to use.  We may be
  // better off using dbus_bus_request_name(DBusConection *connection, const char *name, unsitned int falgs, DBusError *error).
  error = NULL;
  ok = dbus_g_proxy_call (proxy,
                          "RequestName",
                          &error,
                          G_TYPE_STRING,
                          "edu.grinnell.glimmer.counter",
                          G_TYPE_UINT, 0,
                          G_TYPE_INVALID,
                          G_TYPE_UINT, &result,
                          G_TYPE_INVALID);
  if (! ok)
    {
      g_printerr ("Error registering name: %s\n", error->message);
      g_error_free (error);
      g_object_unref (proxy);
      return 1; // Failure
    }
  if (result != 1)
    {
      g_printerr ("Could not register name.\n");
      g_error_free (error);
      g_object_unref (proxy);
      return 1; // Failure
    }
  
  // Create the object we're trying to register.  
  object = G_OBJECT (glim_counter_new ("dbus"));
  if (object == NULL)
    {
      g_printerr ("Error: Failed to create object to register.\n");
      g_object_unref (proxy);
      return 1;
    }
  
  // Register that object
  dbus_g_connection_register_g_object (connection, 
                                       "/edu/grinnell/glimmer/counter",
                                       object);

  // Wait for requests
  gtk_main ();

  // And we're done
  return 0;
} // main
