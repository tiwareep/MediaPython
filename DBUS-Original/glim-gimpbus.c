/**
 * glim-gimpbus.c
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

  I've tried two mechanisms for implmenting the PDB calls.  One
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

#include "glim-debug.h"

#include "glim-dbus.h"

#include "glim-gimpbus.h"
#include "glim-gimpbus-server.h"


// +---------------+--------------------------------------------------
// | GObject Setup |
// +---------------+

G_DEFINE_TYPE (GlimGimpbus, glim_gimpbus, G_TYPE_OBJECT);


// +--------------------+---------------------------------------------
// | Object Destruction |
// +--------------------+

/**
 * Prepare to dispose of this object.
 */
static void
glim_gimpbus_dispose (GObject *obj)
{
  // Chain up to the parent class.
  (G_OBJECT_CLASS (glim_gimpbus_parent_class))->dispose (obj);
} // glim_gimpbus_dispose

/**
 * Finalize this object.
 */
static void
glim_gimpbus_finalize (GObject *obj)
{
  GlimGimpbus *self = GLIM_GIMPBUS (obj);

  // Deallocated allocated fields
  if (self->name != NULL)
    {
      g_free (self->name);
      self->name = NULL;
    }

  (G_OBJECT_CLASS (glim_gimpbus_parent_class))->finalize (obj);
} // glim_gimpbus_finalize


// +---------------------+--------------------------------------------
// | Object Construction |
// +---------------------+

/**
 * Construct the object.
 */
static GObject *
glim_gimpbus_constructor (GType gtype,
                          guint n_properties,
                          GObjectConstructParam *properties)
{
  // Always chain up to the parent constructor.
  GObjectClass *parent_klass = G_OBJECT_CLASS (glim_gimpbus_parent_class);
  GObject *obj = parent_klass->constructor (gtype, n_properties, properties);

  // That's it, we're done.
  return obj;
} // glim_gimpbus_constructor

/**
 * Initialize the primary structure.
 */
static void
glim_gimpbus_init (GlimGimpbus *self)
{
} // glim_gimpbus_init

/**
 * Initialize the class.
 */
static void
glim_gimpbus_class_init (GlimGimpbusClass *klass)
{
  GObjectClass *gobject_class = G_OBJECT_CLASS (klass);
 
  // Set the constructor
  gobject_class->constructor = glim_gimpbus_constructor;
 
  // Set the cleanup functions
  gobject_class->dispose = glim_gimpbus_dispose;
  gobject_class->finalize = glim_gimpbus_finalize;

  // Install information on the object
  dbus_g_object_type_install_info (GLIM_TYPE_GIMPBUS, 
                                   &dbus_glib_glim_gimpbus_object_info);

} // glim_gimpbus_class_init


// +-----------------------+------------------------------------------
// | Exported Constructors |
// +-----------------------+

/**
 * Create a new, generic, gimpbus, with the given name.
 */
GlimGimpbus *
glim_gimpbus_new (void)
{
  GlimGimpbus *self = 
    (GlimGimpbus *) g_object_new (GLIM_TYPE_GIMPBUS, NULL);
  return self;
} // glim_gimpbus_new


// +---------------+--------------------------------------------------
// | Local Helpers |
// +---------------+

static void
glim_gimpbus_print_iii_i (gchar *name,
                          const gint p1,
                          const gint p2,
                          const gint p3)
{
  printf ("%s (%d, %d, %d)\n", name, p1, p2, p3);
} // glim_gimp_print_iii_i

static gboolean
glim_gimpbus_marshall_iii_i (gchar *name, 
                             const gint p1,
                             const gint p2,
                             const gint p3,
                             gint *r1,
                             GError **error)
{
  return TRUE;
} // glim_gimp_marshall_iii_i

/**
 * Some of the errors we get back from PDB calls.
 */
const gchar *
glim_gimpbus_pdb_error_string (int status)
{
  switch (status)
    {
    case GIMP_PDB_EXECUTION_ERROR:
      return "execution error";
    case GIMP_PDB_CALLING_ERROR:
      return "calling error";
    case GIMP_PDB_PASS_THROUGH:
      return "pass through error";
    case GIMP_PDB_CANCEL:
      return "cancelled";
    default:
      return "unknown error";
    }
} // glim_gimpbus_pdb_error_message


// +------------------+-----------------------------------------------
// | Exported Methods |
// +------------------+


gboolean
glim_gimpbus_gimp_airbrush (GlimGimpbus *ggb, 
			    const gint drawable,
			    const gdouble pressure,
			    const GArray *strokes,
			    GError **error)
{
  gdouble newstrokes[strokes->len];
  gint i;
  for (i = 0; i < strokes->len; i++)
    newstrokes[i] = g_array_index(strokes, gdouble, i);
  gimp_airbrush(drawable, pressure, strokes->len, newstrokes);
  return TRUE;
} // glim_gimpbus_gimp_airbrush  




gboolean
glim_gimpbus_gimp_blot (GlimGimpbus *ggb,
			const gint drawable,
			const gdouble x,
			const gdouble y, 
			GError **error)
{
  gdouble pair[] = {x, y};
  gimp_paintbrush (drawable, 0, 2, pair, 0, 0);
  return TRUE;
} // glim_gimpbus_gimp_blot




gboolean
glim_gimpbus_gimp_brushes_get_list (GlimGimpbus *ggb, 
				    const gchar *filter,
				    gchar ***brush_list,
				    GError **error)
{
  gchar **brushes;
  gint num_brushes;
  brushes = gimp_brushes_get_list(filter, &num_brushes);
  gchar **result = g_new (char *, num_brushes + 1);
  int i;
  for (i = 0; i < num_brushes; i++)
    result[i] = brushes[i];
  result[num_brushes] = NULL;
  *brush_list = result;
  return TRUE;
} // glim_gimpbus_gimp_brushes_get_list





gboolean
glim_gimpbus_gimp_context_get_background (GlimGimpbus *ggb, 
					  gdouble *red,
					  gdouble *green,
					  gdouble *blue,
					  GError **error)
{
  GimpRGB color;
  gimp_context_get_background (&color);
  *red = color.r;
  *green = color.g;
  *blue = color.b;
  return TRUE;
} // glim_gimpbus_gimp_context_get_background




gboolean
glim_gimpbus_gimp_context_get_foreground (GlimGimpbus *ggb, 
					  gdouble *red,
					  gdouble *green,
					  gdouble *blue,
					  GError **error)
{
  GimpRGB color;
  gimp_context_get_foreground (&color);
  *red = color.r;
  *green = color.g;
  *blue = color.b;
  return TRUE;
}




gboolean
glim_gimpbus_gimp_context_set_background (GlimGimpbus *ggb, 
					  const gdouble red,
					  const gdouble green,
					  const gdouble blue,
					  GError **error)
{
  GimpRGB color;
  color.r = red;
  color.g = green;
  color.b = blue;

  gimp_context_set_background (&color);
  return TRUE;
} // glim_gimpbus_gimp_context_set_background


gboolean
glim_gimpbus_gimp_context_set_brush (GlimGimpbus *ggb, 
				     const gchar *name,
				     GError **error)
{
  gimp_context_set_brush (name);
  return TRUE;
} // glim_gimpbus_gimp_context_set_brush


gboolean
glim_gimpbus_gimp_context_get_brush (GlimGimpbus *ggb, 
				     gchar **name,
				     GError **error)
{
  *name = gimp_context_get_brush();
  return TRUE;
} // glim_gimpbus_gimp_context_get_brush

gboolean
glim_gimpbus_gimp_edit_stroke(GlimGimpbus *ggb,
			      gint drawable,
			      GError **error)
{
  gimp_edit_stroke(drawable);
}//glim_gimpbus_edit_stroke

gboolean
glim_gimpbus_gimp_drawable_set_pixel (GlimGimpbus *ggb, 
				      const gint drawable,
				      const gint xcord,
				      const gint ycord,
				      const gint num_channels,
				      const GArray *pixel,
				      GError **error)
{
  gimp_drawable_set_pixel (drawable, xcord, ycord, num_channels,
                           (guchar *) pixel->data);
  return TRUE;
} // glim_gimpbus_gimp_drawable_set_pixel



gboolean
glim_gimpbus_gimp_context_set_foreground (GlimGimpbus *ggb, 
					  const gdouble red,
					  const gdouble green,
					  const gdouble blue,
					  GError **error)
{
  GimpRGB color;
  color.r = red;
  color.g = green;
  color.b = blue;

  gimp_context_set_foreground (&color);
  return TRUE;
} // glim_gimpbus_gimp_context_set_foreground





gboolean
glim_gimpbus_gimp_display_new (GlimGimpbus *ggb, 
			       const gint image, 
			       GError **error)
{
  gimp_display_new (image);
  return TRUE;
} // glim_gimpbus_gimp_display_new





gboolean
glim_gimpbus_gimp_displays_flush (GlimGimpbus *ggb, 
				  GError **error)
{
  gimp_displays_flush();
  return TRUE;
} // glim_gimpbus_gimp_displays_flush




gboolean
glim_gimpbus_gimp_dodgeburn_default (GlimGimpbus *ggb, 
				     const gint drawable,
				     const GArray *strokes,
				     GError **error)
{
  gdouble newstrokes[strokes->len];
  gint i;
  for (i = 0; i < strokes->len; i++)
    newstrokes[i] = g_array_index(strokes, gdouble, i);
  gimp_dodgeburn_default(drawable, strokes->len, newstrokes);
  return TRUE;
} // glim_gimpbus_gimp_dodgeburn_default 





gboolean
glim_gimpbus_gimp_drawable_height (GlimGimpbus *ggb, 
				   const gint drawable,
				   gint *height,
				   GError **error)
{
  *height = gimp_drawable_height (drawable);
  return TRUE;
} // glim_gimpbus_gimp_drawable_height




gboolean 
glim_gimpbus_gimp_drawable_transform_rotate_default (GlimGimpbus *ggb,
						     const gint drawable,
						     const gdouble angle,
						     const gboolean auto_center,
						     const gint center_x,
						     const gint center_y,
						     const gboolean interpolate,
						     const GimpTransformResize clip_result,
						     GError **error)
{
  gimp_drawable_transform_rotate_default (drawable, angle, auto_center, center_x, center_y, interpolate, clip_result);
  return TRUE;
} // glim_gimpbus_gimp_drawable_transform_rotate_default




gboolean
glim_gimpbus_gimp_drawable_transform_scale (GlimGimpbus *ggb,
					    const gint drawable,
					    const gdouble x0,
					    const gdouble y0, 
					    const gdouble x1, 
					    const gdouble y1, 
					    const gint transform_direction, 
					    const gint interpolation, 
					    const gint supersample, 
					    const gint recursion_level, 
					    const gint clip_result,
					    GError **error)
{
  gimp_drawable_transform_scale (drawable, x0, y0, x1, y1, transform_direction, interpolation, supersample, recursion_level, clip_result);
  return TRUE;
} // glim_gimpbus_gimp_drawing_transform_scale




gboolean 
glim_gimpbus_gimp_drawable_type (GlimGimpbus *ggb, 
				 const gint drawable, 
				 gint *type, 
				 GError **error)
{
  *type = gimp_drawable_type (drawable);
  return TRUE;
} // glim_gimpbus_gimp_drawable_type




gboolean
glim_gimpbus_gimp_drawable_width (GlimGimpbus *ggb, 
				  const gint drawable,
				  gint *width,
				  GError **error)
{
  *width = gimp_drawable_width (drawable);
  return TRUE;
} // glim_gimpbus_gimp_drawable_width




gboolean
glim_gimpbus_gimp_edit_bucket_fill (GlimGimpbus *ggb, 
				    const gint drawable, 
				    const gint fill_mode, 
				    const gint paint_mode, 
				    const gdouble opacity, 
				    const gdouble threshold, 
				    const gint sample_merged, 
				    const gdouble x, 
				    const gdouble y,
				    GError **error)
{
  gimp_edit_bucket_fill (drawable, fill_mode, paint_mode, opacity, threshold, sample_merged, x, y);
  return TRUE;
} // glim_gimpbus_gimp_edit_bucket_fill




gboolean
glim_gimpbus_gimp_edit_named_copy (GlimGimpbus *ggb, 
				   const gint drawable, 
				   const gchar *buffer_name,
				   GError **error)
{
  gimp_edit_named_copy (drawable, buffer_name);
  return TRUE;
} // glim_gimpbus_gimp_edit_named_copy




gboolean
glim_gimpbus_gimp_edit_named_paste (GlimGimpbus *ggb, 
				    const gint drawable, 
				    const gchar *buffer_name,
				    const gboolean paste_into,
				    GError **error)
{
  gimp_edit_named_paste (drawable, buffer_name, paste_into);
  return TRUE;
} // glim_gimpbus_gimp_edit_named_paste




gboolean
glim_gimpbus_gimp_ellipse_select (GlimGimpbus *ggb, 
				  const gint image, 
				  const gdouble left, 
				  const gdouble top, 
				  const gdouble width, 
				  const gdouble height, 
				  const gint operation,
				  const gint antialias,
				  const gint feather, 
				  const gdouble radius, 
				  GError **error)
{
  gimp_ellipse_select (image, left, top, width, height, operation, antialias, feather, radius);
  return TRUE;
} // glim_gimpbus_gimp_ellipse_select


gboolean
glim_gimpbus_gimp_eraser_default (GlimGimpbus *ggb, 
				  const gint drawable, 
				  const GArray *strokes,  
				  GError *error)
{
  gdouble newstrokes[strokes->len];
  gint i;
  for (i = 0; i < strokes->len; i++)
    newstrokes[i] = g_array_index(strokes, gdouble, i);
  gimp_eraser_default(drawable, strokes->len, newstrokes);
  return TRUE;
} // glim_gimpbus_gimp_eraser



gboolean            
glim_gimpbus_gimp_file_load (GlimGimpbus *ggb,
			     GimpRunMode run_mode,
			     const gchar *filename,
			     const gchar *raw_filename,
			     gint *imagep,
			     GError **error)
{
 *imagep = gimp_file_load(run_mode, filename, raw_filename);
  return TRUE;
} //glim_gimpbus_gimp_file_load




gboolean            
glim_gimpbus_gimp_file_save (GlimGimpbus *ggb,
			     GimpRunMode run_mode,
			     const gint image,
			     const gint drawable,
			     const gchar *filename,
			     const gchar *raw_filename,
			     GError **error)
{
  gimp_file_save(run_mode, image, drawable, filename, raw_filename);
  return TRUE;
} //glim_gimpbus_gimp_file_save
  //filename is file path
  //raw is file name
	    

gboolean
glim_gimpbus_gimp_fonts_get_list (GlimGimpbus *ggb,
				  const gchar *filter,
				  gchar ***font_list,
				  GError **error)
{
  gchar **fonts;
  gint num_fonts;
  fonts = gimp_fonts_get_list (filter, &num_fonts);
  gchar **result = g_new (char *, num_fonts + 1);
  int i;
  for (i = 0; i < num_fonts; i++)
    result[i] = fonts[i];
  result[num_fonts] = NULL;
  *font_list = result;
  return TRUE;
} // glim_gimpbus_gimp_fonts_get_list




gboolean 
glim_gimpbus_gimp_free_select (GlimGimpbus *ggb, 
			       const gint image,
			       const GArray *segments,
			       const GimpChannelOps operation,
			       const gboolean antialias,
			       const gboolean feather,
			       const gdouble feather_radius, 
			       GError **error)
{
  gdouble newsegments[segments->len];
  gint i;
  for (i = 0; i < segments->len; i++)
    newsegments[i] = g_array_index(segments, gdouble, i);
  gimp_free_select(image, segments->len, newsegments,  operation, antialias, feather, feather_radius);
  return TRUE;
} // glim_gimpbus_gimp_free_select

gboolean
glim_gimpbus_gimp_image_add_layer (GlimGimpbus *ggb,
				   const gint image,
				   const gint layer,
				   const gint position,
				   GError **error)
{
  gimp_image_add_layer (image, layer, position);
  return TRUE;
}


gboolean
glim_gimpbus_gimp_image_crop (GlimGimpbus *ggb, 
			      const gint image,
			      const gint new_width,
			      const gint new_height, 
			      const gint offx, 
			      const gint offy,
			      GError **error)
{
  gimp_image_crop (image, new_width, new_height, offx, offy);
  return TRUE;
} // glim_gimpbus_gimp_image_crop




gboolean
glim_gimpbus_gimp_image_flatten (GlimGimpbus *ggb,
				 const gint image, 
				 gint *layerp,
				 GError **error)
{
  *layerp = gimp_image_flatten (image);
  return TRUE;
} // glim_gimpbus_gimp_image_flatten




gboolean 
glim_gimpbus_gimp_image_flip (GlimGimpbus *ggb, 
			      const gint image, 
			      const gint flip_type, 
			      GError **error)
{
  gimp_image_flip (image, flip_type);
  return TRUE;
} // glim_gimpbus_gimp_image_flip




gboolean
glim_gimpbus_gimp_image_get_active_drawable (GlimGimpbus *ggb,
					     const gint image, 
					     gint *drawp,
					     GError **error)
{
  *drawp = gimp_image_get_active_drawable (image);
  return TRUE;
} // glim_gimpbus_gimp_image_get_active_drawable




gboolean
glim_gimpbus_gimp_image_height (GlimGimpbus *ggb,
				const gint image,
				gint *height,
				GError **error)
{
  *height = gimp_image_height(image);
  return TRUE;
} // glim_gimpbus_gimp_image_height




int
glim_gimpbus_gimp_image_is_valid (GlimGimpbus *ggb,
                                  const gint image,
                                  gint *valid,
                                  GError **error)
{
  int result = gimp_image_is_valid (image);
  *valid = result;
  return TRUE;
} // glim_gimpbus_gimp_image_is_valid


gboolean
glim_gimpbus_gimp_image_new (GlimGimpbus *ggb,
                             const gint width,
                             const gint height,
                             const gint type,
                             gint *imagep,
                             GError **error)
{
  *imagep = gimp_image_new (width, height, type);
  return TRUE;
} // glim_gimpbus_gimp_image_new





gboolean
glim_gimpbus_gimp_image_scale (GlimGimpbus *ggb, 
			       const gint image, 
			       const gint new_width, 
			       const gint new_height, 
			       GError **error)
{
  gimp_image_scale (image, new_width, new_height);
  return TRUE;
} // glim_gimpbus_gimp_image_scale





gboolean
glim_gimpbus_gimp_image_width (GlimGimpbus *ggb,
			       const gint image,
			       gint *width,
			       GError **error)
{
  *width = gimp_image_width(image);
  return TRUE;
} // glim_gimpbus_gimp_image_width





gboolean 
glim_gimpbus_gimp_invert (GlimGimpbus *ggb, 
			  const gint drawable,
			  GError **error)
{
  gimp_invert (drawable);
  return TRUE;
} // glim_gimpbus_gimp_invert



gboolean
glim_gimpbus_gimp_layer_new(GlimGimpbus *ggb, 
			    const gint image, 
			    const gchar *name,
			    const gint width, 
			    const gint height, 
			    const gint type, 
			    const gdouble opacity, 
			    const gint mode,
			    gint *layer,
			    GError **error)
{
  *layer=gimp_layer_new (image, name, width, height, type, opacity, mode);
  return TRUE;
}// glim_gimpbus_gimp_layer_new





gboolean 
glim_gimpbus_gimp_message (GlimGimpbus *ggb, 
			   const gchar *message, 
			   GError **error)
{
  gimp_message (message);
  return TRUE;
} // glim_gimpbus_gimp_message




gboolean
glim_gimpbus_gimp_paintbrush (GlimGimpbus *ggb,
			      const gint drawable,
                              const gdouble fade_out,
                              const GArray *strokes,
                              const gint method,
                              const gdouble gradient_length,
			      GError **error)
{
  gdouble newstrokes[strokes->len];
  gint i;
  for (i=0; i<strokes->len; i++)
    newstrokes[i]= g_array_index(strokes, gdouble, i);
  gimp_paintbrush(drawable, fade_out, strokes->len, newstrokes, method, gradient_length);
  return TRUE;
} // glim_gimpbus_gimp_paintbrush




gboolean
glim_gimpbus_gimp_perspective (GlimGimpbus *ggb,
			       const gint drawable,
			       const gboolean interpolation,
			       const gdouble x0,
			       const gdouble y0,
			       const gdouble x1,
			       const gdouble y1,
			       const gdouble x2,
			       const gdouble y2,
			       const gdouble x3,
			       const gdouble y3,
			       GError **error)
{
  gimp_perspective (drawable, interpolation, x0, y0, x1, y1, x2, y2, x3, y3);
  return TRUE;
} // glim_gimpbus_gimp_perspective




gboolean 
glim_gimpbus_gimp_posterize (GlimGimpbus *ggb, 
			     const gint drawable, 
			     const gint levels, 
			     GError **error)
{
  gimp_posterize (drawable, levels);
  return TRUE;
} // glim_gimpbus_gimp_posterize
                                  




gboolean
glim_gimpbus_gimp_rect_select (GlimGimpbus *ggb, 
                               const gint image, 
                               const gdouble left, 
                               const gdouble top, 
                               const gdouble width, 
                               const gdouble height, 
                               const gint operation, 
                               const gint feather, 
                               const gdouble radius, 
                               GError **error)
{
  gimp_rect_select (image, left, top, width, height, operation, feather, radius);
  return TRUE;
} // glim_gimpbus_gimp_rect_select





gboolean
glim_gimpbus_gimp_selection_all (GlimGimpbus *ggb,
				 const gint image,
				 GError **error)
{
  gimp_selection_all(image);
  return TRUE;
} // glim_gimpbus_gimp_selection_invert




gboolean
glim_gimpbus_gimp_selection_invert (GlimGimpbus *ggb,
				    const gint image,
				    GError **error)
{
  gimp_selection_invert(image);
  return TRUE;
} // glim_gimpbus_gimp_selection_invert





gboolean
glim_gimpbus_gimp_selection_none (GlimGimpbus *ggb,
				  const gint image,
				  GError **error)
{
  gimp_selection_none(image);
  return TRUE;
} // glim_gimpbus_gimp_selection_invert




gboolean            
glim_gimpbus_gimp_smudge (GlimGimpbus *ggb,
			  const gint drawable,
			  const gdouble pressure,
			  const GArray *strokes,
			  GError **error)
{
  gdouble newstrokes[strokes->len];
  gint i;
  for (i = 0; i < strokes->len; i++)
    newstrokes[i] = g_array_index(strokes, gdouble, i);
  gimp_smudge (drawable, pressure, strokes->len, newstrokes);
  return TRUE;
} // glim_gimpbus_gimp_smudge



gboolean
glim_gimpbus_gimp_text_fontname (GlimGimpbus *ggb, 
				 const gint image, 
				 const gint drawable, 
				 const gdouble x, 
				 const gdouble y, 
				 const gchar *text, 
				 const gint border,
				 const gboolean antialias,
				 const gdouble size, 
				 const GimpSizeType size_type, 
				 const gchar *fontname,
				 GError **error)
{
  gimp_text_fontname (image, drawable, x, y, text, border, antialias, size, size_type, fontname);
  return TRUE;
} // glim_gimpbus_gimp_text_fontname




gboolean
glim_gimpbus_list_pdb (GlimGimpbus *ggb,
                   gchar ***functions,
                   GError **error)
{
  gchar **procnames;
  gint nprocs;
  gimp_procedural_db_query (".*", ".*", ".*", ".*", ".*", ".*", ".*",
                            &nprocs, &procnames);
  gchar **result = g_new (char *, nprocs + 1);
  int i;
  for (i = 0; i < nprocs; i++)
    result[i] = procnames[i];
  result[nprocs] = NULL;
  *functions = result;
  return TRUE;
} // glim_gimpbus_list_pdb








// +---------------+--------------------------------------------------
// | PDB Functions |
// +---------------+

/**
 * An example of how to call a PDB function.  Note that the get-layers
 * function returns two values: an integer and an array of integers.
 * However, for D-Bus, we can just return a GArray, since a GArray has
 * a size field.
 */
gboolean
glim_gimpbus_pdb_gimp_image_get_layers (GlimGimpbus *ggb,
			                const int image,
                                        GArray **layers,
                                        GError **error)
{
  GimpParam actuals[1];
  GimpParam *returned;
  int nreturned;

  REPORT ("Starting pdb_gimp_image_get_layers");

  // Prepare the actual parameters.
  actuals[0].type = GIMP_PDB_IMAGE;
  actuals[0].data.d_int32 = image;
  GOT_HERE ();

  // Run the procedure.
  REPORT ("Running procedure");
  returned = gimp_run_procedure2 ("gimp-image-get-layers", &nreturned,
                                  1, actuals);
  REPORT_I (nreturned);

  // Check the return value
  if (returned[0].data.d_status != GIMP_PDB_SUCCESS)
    {
      fprintf (stderr, "Whoops!  The PDB call failed.\n");
      const char *errmsg =
        glim_gimpbus_pdb_error_string (returned[0].data.d_status);
      // THIS CODE IS NOT YET CORRECT!
      *error = g_error_new (dbus_g_error_quark (),
                            DBUS_GERROR_REMOTE_EXCEPTION,
                            "%s",
                            errmsg);
      return FALSE;
    }

  // Convert the return values.
  REPORT ("Converting to array");
  *layers = glim_dbus_ints_to_g_array (returned[1].data.d_int32,
                                       returned[2].data.d_int32array);

  // Clean up!
  REPORT ("Cleaning up");
  gimp_destroy_params (returned, nreturned);

  // And we're done.
  REPORT ("Done");
  return TRUE;
} // glim_gimpbus_pdb_gimp_image_get_layers



gboolean
glim_gimpbus_pdb_gimp_drawable_get_pixel(GlimGimpbus *ggb,
					 const int drawable,
					 const int xcord,
					 const int ycord,
					 GArray **pixval,
					 GError **error)
{
  GimpParam actuals[3];
  GimpParam *returned;
  int nreturned;

  REPORT ("Starting pdb_gimp_drawable_get_pixel");

  // Prepare the actual parameters.
  actuals[0].type = GIMP_PDB_DRAWABLE;
  actuals[0].data.d_int32 = drawable;

  actuals[1].type = GIMP_PDB_INT32;
  actuals[1].data.d_int32 = xcord;

  actuals[2].type = GIMP_PDB_INT32;
  actuals[2].data.d_int32 = ycord;
  GOT_HERE ();

  // Run the procedure.
  REPORT ("Running procedure");
  returned = gimp_run_procedure2 ("gimp-drawable-get-pixel", &nreturned, 
                                  3, actuals);
  REPORT_I (nreturned);

  // Check the return value
  if (returned[0].data.d_status != GIMP_PDB_SUCCESS)
    {
      fprintf (stderr, "Whoops!  The PDB call failed.\n");
      const char *errmsg = 
        glim_gimpbus_pdb_error_string (returned[0].data.d_status);
      // THIS CODE IS NOT YET CORRECT!
      *error = g_error_new (dbus_g_error_quark (),
                            DBUS_GERROR_REMOTE_EXCEPTION,
                            "%s",
                            errmsg);
      return FALSE;
    }

  // Convert the return values.
  REPORT ("Converting to array");
  gint num_channels = returned[1].data.d_int32;
  guint8 *channels = returned[2].data.d_int8array;

  REPORT_I(num_channels);

  GArray *result = g_array_sized_new (FALSE, FALSE, sizeof (gint8), num_channels);
  g_array_append_vals (result, channels, num_channels);
  *pixval = result;
           
  // Clean up!
  REPORT ("Cleaning up");
  gimp_destroy_params (returned, nreturned);  

  // And we're done.
  REPORT ("Done");
  return TRUE;


}//glim_gimpbus_pdb_gimp_drawable_get_pixel


gboolean
glim_gimpbus_gimp_context_get_fg (GlimGimpbus *ggb, 
                                  GimpRGB **color,
                                  GError **error)
{
  GimpRGB *tmp = g_malloc (sizeof (GimpRGB));
  gimp_context_get_foreground (tmp);
  *color = tmp;
  return TRUE;
} // glim_gimpbus_gimp_context_get_fg



gboolean
glim_gimpbus_gimp_image_transform_get (GlimGimpbus *ggb,
				       const gint drawable,
				       GArray **pixels,
				       GError **error)
{
  gint         channels;
  gint         x1, y1, x2, y2;
  GimpPixelRgn rgn_in;
  guchar      *pix;
  GimpDrawable *g_drawable;


  gimp_drawable_mask_bounds (drawable,
                             &x1, &y1,
                             &x2, &y2);
  channels = gimp_drawable_bpp (drawable);

  g_drawable = gimp_drawable_get(drawable);

  gimp_pixel_rgn_init (&rgn_in,
                       g_drawable,
                       x1, y1,
                       x2 - x1, y2 - y1,
                       FALSE, FALSE);



  //Initialize memory for pix
  pix = g_new (guchar, channels * (x2*y2));


  //Do the real work
  gimp_pixel_rgn_get_rect (&rgn_in,
			   pix,
			   x1,
			   y1,
			   (x2-x1),
			   (y2-y1));

  GArray *result = g_array_sized_new (FALSE, FALSE, sizeof (guchar), 3*x2*y2);
  g_array_append_vals (result, pix, 3*x2*y2);

  *pixels = result;

  g_free(pix);

}//glim_gimpbus_gimp_image_transform_get

gboolean
glim_gimpbus_gimp_image_transform_set (GlimGimpbus *ggb,
				       const gint drawable,
				       GArray *pixels,
				       GError **error)
{
  gint         channels;
  gint         x1, y1, x2, y2;
  GimpPixelRgn rgn_out;
  GimpDrawable *g_drawable;


  gimp_drawable_mask_bounds (drawable,
                             &x1, &y1,
                             &x2, &y2);
  channels = gimp_drawable_bpp (drawable);

  g_drawable = gimp_drawable_get(drawable);

  gimp_pixel_rgn_init (&rgn_out,
                       g_drawable,
                       x1, y1,
                       x2 - x1, y2 - y1,
                       TRUE, TRUE);


  gimp_pixel_rgn_set_rect (&rgn_out,
			   (guchar*)pixels->data,
			   x1,
			   y1,
			   (x2-x1),
			   (y2-y1));

  gimp_drawable_flush (g_drawable);
  gimp_drawable_merge_shadow (drawable, TRUE);
  gimp_drawable_update (drawable,
                        x1, y1,
                        x2 - x1, y2 - y1);
  return TRUE;

}//glim_gimpbus_gimp_image_transform_set
