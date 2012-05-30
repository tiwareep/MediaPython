/**
 * glim-counter-factory.c
 *   Implementation GlimCounterFactory objects, which I am using in my basic
 *   explorations of D-Bus services.  A GlimCounterFactory builds GlimCounter
 *   objects which it then installs on D-Bus.
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

#include "glim-counter-factory.h"
#include "glim-counter-factory-glue.h"


// +---------------+--------------------------------------------------
// | GObject Setup |
// +---------------+

G_DEFINE_TYPE (GlimCounterFactory, glim_counter_factory, G_TYPE_OBJECT);


// +--------------------+---------------------------------------------
// | Object Destruction |
// +--------------------+

/**
 * Prepare to dispose of this object.
 */
static void
glim_counter_factory_dispose (GObject *obj)
{
  // Chain up to the parent class.
  (G_OBJECT_CLASS (glim_counter_factory_parent_class))->dispose (obj);
} // glim_counter_factory_dispose

/**
 * Finalize this object.
 */
static void
glim_counter_factory_finalize (GObject *obj)
{
  GlimCounterFactory *self = GLIM_COUNTER_FACTORY (obj);

  // Deallocate allocated fields
  if (self->connection != NULL)
    {
      dbus_g_connection_unref (self->connection);
      self->connection = NULL;
    }

  (G_OBJECT_CLASS (glim_counter_factory_parent_class))->finalize (obj);
} // glim_counter_factory_finalize


// +---------------------+--------------------------------------------
// | Object Construction |
// +---------------------+

/**
 * Construct the object.
 */
static GObject *
glim_counter_factory_constructor (GType gtype,
                          guint n_properties,
                          GObjectConstructParam *properties)
{
  // Always chain up to the parent constructor.
  GObjectClass *parent_klass = G_OBJECT_CLASS (glim_counter_factory_parent_class);
  GObject *obj = parent_klass->constructor (gtype, n_properties, properties);

  // That's it, we're done.
  return obj;
} // glim_counter_factory_constructor

/**
 * Initialize the primary structure.
 */
static void
glim_counter_factory_init (GlimCounterFactory *self)
{
} // glim_counter_factory_init

/**
 * Initialize the class.
 */
static void
glim_counter_factory_class_init (GlimCounterFactoryClass *klass)
{
  GObjectClass *gobject_class = G_OBJECT_CLASS (klass);
 
  // Set the constructor
  gobject_class->constructor = glim_counter_factory_constructor;
 
  // Set the cleanup functions
  gobject_class->dispose = glim_counter_factory_dispose;
  gobject_class->finalize = glim_counter_factory_finalize;

  // Install information on the object
  dbus_g_object_type_install_info (GLIM_TYPE_COUNTER_FACTORY, 
                                   &dbus_glib_glim_counter_factory_object_info);

} // glim_counter_factory_class_init


// +-----------------------+------------------------------------------
// | Exported Constructors |
// +-----------------------+

/**
 * Create a new counter factory for a particular connection.
 */
GlimCounterFactory *
glim_counter_factory_new (DBusGConnection *connection)
{
  GlimCounterFactory *self = 
    (GlimCounterFactory *) g_object_new (GLIM_TYPE_COUNTER_FACTORY, NULL);
  self->connection = connection;
  dbus_g_connection_ref (connection);
  self->count = 0;
  return self;
} // glim_counter_factory_new


// +-----------------+------------------------------------------------
// | Service Methods |
// +-----------------+

/**
 * Build a new counter.
 * TODO: Add error checking.
 */
gboolean
glim_counter_factory_build (GlimCounterFactory *factory,
                            gchar **name, GError **error_p)
{
  char *counter_name = g_strdup_printf ("Counter%d", (factory->count)++);
  char *path = 
    g_strconcat ("/edu/grinnell/glimmer/counter/", counter_name, NULL);
  GlimCounter *counter = glim_counter_new (counter_name);
  GError *error;                // Error returned by call
  DBusGConnection *connection;  // A connection to the main application

  // Create the connection
  error = NULL;
  connection = dbus_g_bus_get (DBUS_BUS_SESSION, &error);
  if ((! connection) || error)
    {
      *error_p = error;
      return FALSE;
    }

  // Register the object
  dbus_g_connection_register_g_object (connection,
                                       path, 
                                       G_OBJECT (counter));
  g_free (path);

  *name = counter_name;
  return TRUE;
} // glim_counter_factory_build
