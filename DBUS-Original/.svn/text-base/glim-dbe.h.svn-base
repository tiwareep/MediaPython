#ifndef __GLIM_DBE_H__
#define __GLIM_DBE_H__

/**
 * glim-dbe.h
 *   Declaration for GlimDbe objects, which I am using in my basic
 *   explorations of DBUS services.  A GlimDbe object provides a
 *   variety of experimental operations (dbe => D-Bus Experment)
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
#include <glib.h>


// +-------------+----------------------------------------------------
// | Type Macros |
// +-------------+ 

#define GLIM_TYPE_DBE \
  (glim_dbe_get_type ())
#define GLIM_DBE(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST ((obj), GLIM_TYPE_DBE, GlimDbe))
#define GLIM_IS_DBE(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GLIM_TYPE_DBE))
#define GLIM_DBE_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST ((klass), GLIM_TYPE_DBE, GlimDbeClass))
#define GLIM_IS_DBE_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE ((klass), GLIM_TYPE_DBE)
#define GLIM_DBE_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_CLASS ((obj), GLIM_TYPE_DBE, GlimDbeClass))


// +-------------+----------------------------------------------------
// | D-Bus Stuff |
// +-------------+ 

#define DBUS_GLIM_DBE_PATH "/edu/grinnell/glimmer/dbe"


// +---------------------+--------------------------------------------
// | Objects and Classes |
// +---------------------+ 

typedef struct _GlimDbe           GlimDbe;
typedef struct _GlimDbeClass      GlimDbeClass;

struct _GlimDbe
{
  GObject parent;
  int value;    // The value stored in the dbe.
}; 

struct _GlimDbeClass
{
  GObjectClass parent_class;
}; 

// +--------------------------+---------------------------------------
// | Standard GObject Methods |
// +--------------------------+ 

GType glim_dbe_get_type (void);

GlimDbe *glim_dbe_new (void);


// +----------------+-------------------------------------------------
// | Public Methods |
// +----------------+ 

/**
 * Get an array of integers.
 */
gboolean glim_dbe_get_ints (GlimDbe *dbe, GArray **values, GError **error);

/**
 * Get an array of strings.
 */
gboolean glim_dbe_get_strings (GlimDbe *dbe, gchar ***values, GError **error);


#endif // __GLIM_DBE_H__
