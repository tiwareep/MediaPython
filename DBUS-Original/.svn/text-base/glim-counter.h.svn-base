#ifndef __GLIM_COUNTER_H__
#define __GLIM_COUNTER_H__

/**
 * glim-counter.h
 *   Declaration for GlimCounter objects, which I am using in my basic
 *   explorations of DBUS services.  A GlimCounter object counts values.
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

#define GLIM_TYPE_COUNTER \
  (glim_counter_get_type ())
#define GLIM_COUNTER(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST ((obj), GLIM_TYPE_COUNTER, GlimCounter))
#define GLIM_IS_COUNTER(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GLIM_TYPE_COUNTER))
#define GLIM_COUNTER_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST ((klass), GLIM_TYPE_COUNTER, GlimCounterClass))
#define GLIM_IS_COUNTER_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE ((klass), GLIM_TYPE_COUNTER)
#define GLIM_COUNTER_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_CLASS ((obj), GLIM_TYPE_COUNTER, GlimCounterClass))


// +-------------+----------------------------------------------------
// | D-Bus Stuff |
// +-------------+ 

#define DBUS_GLIM_COUNTER_PATH "/edu/grinnell/glimmer/counter"


// +---------------------+--------------------------------------------
// | Objects and Classes |
// +---------------------+ 

typedef struct _GlimCounter           GlimCounter;
typedef struct _GlimCounterClass      GlimCounterClass;

struct _GlimCounter
{
  GObject parent;

  gchar *name;  // The name of the counter
  int value;    // The value stored in the counter.
}; 

struct _GlimCounterClass
{
  GObjectClass parent_class;
}; 

// +---------+--------------------------------------------------------
// | Methods |
// +---------+ 

GType glim_counter_get_type (void);

GlimCounter *glim_counter_new (gchar *name);

/**
 * Get the name associated with this counter.
 */
const gchar *glim_counter_get_name (GlimCounter *counter);

/**
 * Set the name associated with this counter.
 */
void glim_counter_set_name (GlimCounter *counter, gchar *name);

/**
 * Increment the value stored in the counter.
 */
gboolean glim_counter_increment (GlimCounter *counter, GError **error);

/**
 * Get the value stored in the counter.
 */
gboolean glim_counter_get (GlimCounter *counter, gint *value, GError **error);

#endif // __GLIM_COUNTER_H__
