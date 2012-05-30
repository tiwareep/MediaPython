/**
 * glim-dbe.c
 *   A simple object that provides some GIMP services over D-Bus.  Intended
 *   as an exploration of the relationship between GIMP services and D-Bus.
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

// +-------+----------------------------------------------------------
// | Notes |
// +-------+ 

/*
  Most of this file is generic GObject stuff.  The real work gets
  done in the exported methods at the end of the file.  (I guess
  that's the case for most GObjects.)

  I've tried two mechanisms for implementing the PDB calls.  One
  is to directly call the functions in libgimp.  However, that may
  not be the best strategy when we are translating PDB functions
  en masse.  In that case, we should use a more generic strategy.
  Methods whose name includes pdb (e.g., glim_dbus_pdb_gimp_image_new)
  use the more generic strategy.
 */


// +---------+--------------------------------------------------------
// | Headers |
// +---------+ 

#include <stdio.h>

#include <glib-object.h>
#include <glib.h>

#include <libgimp/gimp.h>

#include "glim-dbe.h"
#include "glim-dbe-server.h"


// +---------------+--------------------------------------------------
// | GObject Setup |
// +---------------+

G_DEFINE_TYPE (GlimDbe, glim_dbe, G_TYPE_OBJECT);


// +--------------------+---------------------------------------------
// | Object Destruction |
// +--------------------+

/**
 * Prepare to dispose of this object.
 */
static void
glim_dbe_dispose (GObject *obj)
{
  // Chain up to the parent class.
  (G_OBJECT_CLASS (glim_dbe_parent_class))->dispose (obj);
} // glim_dbe_dispose

/**
 * Finalize this object.
 */
static void
glim_dbe_finalize (GObject *obj)
{
  GlimDbe *self = GLIM_DBE (obj);
  
  (G_OBJECT_CLASS (glim_dbe_parent_class))->finalize (obj);
} // glim_dbe_finalize


// +---------------------+--------------------------------------------
// | Object Construction |
// +---------------------+

/**
 * Construct the object.
 */
static GObject *
glim_dbe_constructor (GType gtype,
                          guint n_properties,
                          GObjectConstructParam *properties)
{
  // Always chain up to the parent constructor.
  GObjectClass *parent_klass = G_OBJECT_CLASS (glim_dbe_parent_class);
  GObject *obj = parent_klass->constructor (gtype, n_properties, properties);

  // That's it, we're done.
  return obj;
} // glim_dbe_constructor

/**
 * Initialize the primary structure.
 */
static void
glim_dbe_init (GlimDbe *self)
{
} // glim_dbe_init

/**
 * Initialize the class.
 */
static void
glim_dbe_class_init (GlimDbeClass *klass)
{
  GObjectClass *gobject_class = G_OBJECT_CLASS (klass);
 
  // Set the constructor
  gobject_class->constructor = glim_dbe_constructor;
 
  // Set the cleanup functions
  gobject_class->dispose = glim_dbe_dispose;
  gobject_class->finalize = glim_dbe_finalize;

  // Install information on the object
  dbus_g_object_type_install_info (GLIM_TYPE_DBE, 
                                   &dbus_glib_glim_dbe_object_info);

} // glim_dbe_class_init


// +-----------------------+------------------------------------------
// | Exported Constructors |
// +-----------------------+

/**
 * Create a new object.
 */
GlimDbe *
glim_dbe_new (void)
{
  GlimDbe *self = 
    (GlimDbe *) g_object_new (GLIM_TYPE_DBE, NULL);
  return self;
} // glim_dbe_new


// +------------------+-----------------------------------------------
// | Exported Methods |
// +------------------+

gboolean
glim_dbe_get_ints (GlimDbe *dbe,
                   GArray **values,
                   GError **error)
{
  GArray *ints = g_array_new (FALSE, FALSE, sizeof (gint));
  int i;
  i = 6;
  g_array_append_val (ints, i);
  i = 17;
  g_array_append_val (ints, i);
  i = 64;
  g_array_append_val (ints, i);

  *values = ints;
  return TRUE;
} // glim_dbe_get_ints

gboolean
glim_dbe_get_strings (GlimDbe *dbe,
                      gchar ***values,
                      GError **error)
{
  gchar **strings = g_new (char *, 4);
  strings[0] = g_strdup ("hello");
  strings[1] = g_strdup ("goodbye");
  strings[2] = g_strdup ("dbus");
  strings[3] = NULL;
  *values = strings;
  return TRUE;
} // glim_dbe_get_strings

gboolean
glim_dbe_sum (GlimDbe *dbe,
              GArray **values,
              gint **sump,
              GError **error)
{
  int i = 0;
  int sum = 0;
  for (i = 0; i < len; i++)
    sum += g_array_index (values, int, i);

  *sump = sum;
  
  return TRUE;
} // glim_dbe_sum
