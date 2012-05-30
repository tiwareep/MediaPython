#ifndef __GLIM_COUNTER_FACTORY_H__
#define __GLIM_COUNTER_FACTORY_H__

/**
 * glim-counter-factory.h
 *   Declaration for GlimCounterFactory objects, which I am using in my basic
 *   explorations of DBUS services.  A GlimCounterFactory object builds
 *   GlimCounter objects.
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

#include <dbus/dbus-glib.h>


// +-------------+----------------------------------------------------
// | Type Macros |
// +-------------+ 

#define GLIM_TYPE_COUNTER_FACTORY \
  (glim_counter_factory_get_type ())
#define GLIM_COUNTER_FACTORY(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST ((obj), GLIM_TYPE_COUNTER_FACTORY, GlimCounterFactory))
#define GLIM_IS_COUNTER_FACTORY(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GLIM_TYPE_COUNTER_FACTORY))
#define GLIM_COUNTER_FACTORY_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST ((klass), GLIM_TYPE_COUNTER_FACTORY, GlimCounterFactoryClass))
#define GLIM_IS_COUNTER_FACTORY_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE ((klass), GLIM_TYPE_COUNTER_FACTORY)
#define GLIM_COUNTER_FACTORY_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_CLASS ((obj), GLIM_TYPE_COUNTER_FACTORY, GlimCounterFactoryClass))


// +-------------+----------------------------------------------------
// | D-Bus Stuff |
// +-------------+ 

#define DBUS_GLIM_COUNTER_FACTORY_PATH "/edu/grinnell/glimmer/counterfactory"


// +---------------------+--------------------------------------------
// | Objects and Classes |
// +---------------------+ 

typedef struct _GlimCounterFactory           GlimCounterFactory;
typedef struct _GlimCounterFactoryClass      GlimCounterFactoryClass;

struct _GlimCounterFactory
{
  GObject parent;

  DBusGConnection *connection;	// The connection onto which we put counters
  int count;    		// The count of counters we've created.
}; 

struct _GlimCounterFactoryClass
{
  GObjectClass parent_class;
}; 

// +---------+--------------------------------------------------------
// | Methods |
// +---------+ 

GType glim_counter_factory_get_type (void);

GlimCounterFactory *glim_counter_factory_new (DBusGConnection *connection);

/**
 * Build a new counter.  Returns the "name" of the counter object.  (A name
 * is appropriate because we're using this as a service.)
 */
gboolean glim_counter_factory_build (GlimCounterFactory *factory, gchar **name, GError **error);

#endif // __GLIM_COUNTER_FACTORY_H__
