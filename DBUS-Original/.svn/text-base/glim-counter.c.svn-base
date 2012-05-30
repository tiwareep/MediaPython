/**
 * glim-counter.c
 *   Implementation GlimCounter objects, which I am using in my basic
 *   explorations of D-Bus services.  A GlimCounter object counts values.
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

#include "glim-counter.h"
#include "glim-counter-glue.h"


// +---------------+--------------------------------------------------
// | GObject Setup |
// +---------------+

G_DEFINE_TYPE (GlimCounter, glim_counter, G_TYPE_OBJECT);


// +--------------------+---------------------------------------------
// | Object Destruction |
// +--------------------+

/**
 * Prepare to dispose of this object.
 */
static void
glim_counter_dispose (GObject *obj)
{
  // Chain up to the parent class.
  (G_OBJECT_CLASS (glim_counter_parent_class))->dispose (obj);
} // glim_counter_dispose

/**
 * Finalize this object.
 */
static void
glim_counter_finalize (GObject *obj)
{
  GlimCounter *self = GLIM_COUNTER (obj);

  // Deallocated allocated fields
  if (self->name != NULL)
    {
      g_free (self->name);
      self->name = NULL;
    }

  (G_OBJECT_CLASS (glim_counter_parent_class))->finalize (obj);
} // glim_counter_finalize


// +---------------------+--------------------------------------------
// | Object Construction |
// +---------------------+

/**
 * Construct the object.
 */
static GObject *
glim_counter_constructor (GType gtype,
                          guint n_properties,
                          GObjectConstructParam *properties)
{
  // Always chain up to the parent constructor.
  GObjectClass *parent_klass = G_OBJECT_CLASS (glim_counter_parent_class);
  GObject *obj = parent_klass->constructor (gtype, n_properties, properties);

  // That's it, we're done.
  return obj;
} // glim_counter_constructor

/**
 * Initialize the primary structure.
 */
static void
glim_counter_init (GlimCounter *self)
{
} // glim_counter_init

/**
 * Initialize the class.
 */
static void
glim_counter_class_init (GlimCounterClass *klass)
{
  GObjectClass *gobject_class = G_OBJECT_CLASS (klass);
 
  // Set the constructor
  gobject_class->constructor = glim_counter_constructor;
 
  // Set the cleanup functions
  gobject_class->dispose = glim_counter_dispose;
  gobject_class->finalize = glim_counter_finalize;

  // Install information on the object
  dbus_g_object_type_install_info (GLIM_TYPE_COUNTER, 
                                   &dbus_glib_glim_counter_object_info);

} // glim_counter_class_init


// +-----------------------+------------------------------------------
// | Exported Constructors |
// +-----------------------+

/**
 * Create a new, generic, counter, with the given name.
 */
GlimCounter *
glim_counter_new (gchar *name)
{
  GlimCounter *self = 
    (GlimCounter *) g_object_new (GLIM_TYPE_COUNTER, NULL);
  glim_counter_set_name (self, name);
  self->value = 0;
  return self;
} // glim_counter_new


// +------------------+-----------------------------------------------
// | Exported Methods |
// +------------------+

/**
 * Set the name of the counter.
 */
void
glim_counter_set_name (GlimCounter *counter, gchar *name)
{
  if (counter->name != NULL)
    g_free (counter->name);
  counter->name = g_strdup (name);
} // glim_counter_set_name

/**
 * Get the name of the counter.
 */
const gchar *
glim_counter_get_name (GlimCounter *counter)
{
  return counter->name;
} // glim_counter_get_name

/**
 * Increment the counter.
 */
gboolean
glim_counter_increment (GlimCounter *counter, GError **error)
{
  ++(counter->value);
  return TRUE;
} // glim_counter_increment

/**
 * Get the value of the counter.
 */
gboolean
glim_counter_get (GlimCounter *counter, gint *value, GError **error)
{
  *value = counter->value;
  return TRUE;
} // glim_counter_get
