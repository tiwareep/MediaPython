#ifndef __GLIM_DBUS_H__
#define __GLIM_DBUS_H__

/**
 * glim-dbus.h
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

#include "glim-dbus.h"


// +--------------------+---------------------------------------------
// | Exported Functions |
// +--------------------+ 

/**
 * Create a new service with a particular name.  Returns the connection
 * for that service.  If it fails, prints an error (boo!) and returns NULL.
 */
DBusGConnection *glim_dbus_create_service (const gchar *name);

/**
 * Convert a standard C array of ints to a GArray.
 */
GArray *glim_dbus_ints_to_g_array (gint n, gint *ints);

#endif // __GLIM_DBUS_H__
