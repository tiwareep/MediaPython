/**
 * dbe.c
 *   A simple DBUS service.  Mostly the goal is to experiment with things.
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

#include "glim-dbe.h"
#include "glim-dbus.h"


// +------+-----------------------------------------------------------
// | Main |
// +------+ 

int
main (int argc, char *argv[])
{
  DBusGConnection *connection;  // A connection to the main application
  GObject *object;              // An object we're registering

  // Set up GTK
  gtk_init (&argc, &argv);

  // Create the connection
  connection = glim_dbus_create_service ("edu.grinnell.glimmer.dbe");
  if (connection == NULL)
    return 1;

  // Create the object we're trying to register.  
  object = G_OBJECT (glim_dbe_new ());
  if (object == NULL)
    {
      g_printerr ("Error: Failed to create object to register.\n");
      return 1;
    }
  
  // Register that object
  dbus_g_connection_register_g_object (connection, 
                                       "/edu/grinnell/glimmer/dbe",
                                       object);

  // Wait for requests
  gtk_main ();

  // And we're done
  return 0;
} // main
