#ifndef __GLIM_GIMPBUS_H__
#define __GLIM_GIMPBUS_H__

/**
 * glim-gimpbus.h
 *   Declaration for GlimGimpbus objects, which I am using in my basic
 *   explorations of DBUS services.  A GlimGimpbus object counts values.
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

#define GLIM_TYPE_GIMPBUS \
  (glim_gimpbus_get_type ())
#define GLIM_GIMPBUS(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST ((obj), GLIM_TYPE_GIMPBUS, GlimGimpbus))
#define GLIM_IS_GIMPBUS(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GLIM_TYPE_GIMPBUS))
#define GLIM_GIMPBUS_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST ((klass), GLIM_TYPE_GIMPBUS, GlimGimpbusClass))
#define GLIM_IS_GIMPBUS_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE ((klass), GLIM_TYPE_GIMPBUS)
#define GLIM_GIMPBUS_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_CLASS ((obj), GLIM_TYPE_GIMPBUS, GlimGimpbusClass))


// +-------------+----------------------------------------------------
// | D-Bus Stuff |
// +-------------+ 

#define DBUS_GLIM_GIMPBUS_PATH "/edu/grinnell/glimmer/gimpbus"


// +---------------------+--------------------------------------------
// | Objects and Classes |
// +---------------------+ 

typedef struct _GlimGimpbus           GlimGimpbus;
typedef struct _GlimGimpbusClass      GlimGimpbusClass;

struct _GlimGimpbus
{
  GObject parent;

  gchar *name;  // The name of the gimpbus
  int value;    // The value stored in the gimpbus.
}; 

struct _GlimGimpbusClass
{
  GObjectClass parent_class;
}; 


// +-------------------------+----------------------------------------
// | Standard Object Methods |
// +-------------------------+ 

GType glim_gimpbus_get_type (void);

GlimGimpbus *glim_gimpbus_new (void);


// +----------------+-------------------------------------------------
// | Bridge Methods |
// +----------------+ 

gboolean glim_gimpbus_gimp_airbrush (GlimGimpbus *ggb,  const gint drawable, const gdouble pressure, const GArray *strokes, GError **error);

gboolean glim_gimpbus_gimp_blot (GlimGimpbus *ggb, const gint drawable, const gdouble x, const gdouble y,  GError **error);

gboolean glim_gimpbus_gimp_brushes_get_list (GlimGimpbus *ggb, const gchar *filter, gchar ***brush_list, GError **error);

gboolean glim_gimpbus_gimp_context_get_background (GlimGimpbus *ggb, gdouble *red, gdouble *green, gdouble *blue, GError **error);

gboolean glim_gimpbus_gimp_context_get_foreground (GlimGimpbus *ggb, gdouble *red, gdouble *green, gdouble *blue, GError **error);

gboolean glim_gimpbus_gimp_context_get_fg (GlimGimpbus *ggb,  GimpRGB **color, GError **error);

gboolean glim_gimpbus_gimp_context_set_background (GlimGimpbus *ggb, const gdouble red, const gdouble green, const gdouble blue, GError **error);

gboolean glim_gimpbus_gimp_context_set_brush (GlimGimpbus *ggb, const gchar *name, GError **error);

gboolean glim_gimpbus_gimp_context_get_brush (GlimGimpbus *ggb, gchar **name, GError **error);

gboolean glim_gimpbus_gimp_context_set_foreground (GlimGimpbus *ggb, const gdouble red, const gdouble green, const gdouble blue, GError **error);

gboolean glim_gimpbus_gimp_display_new (GlimGimpbus *ggb, const gint image, GError **error);

gboolean glim_gimpbus_gimp_displays_flush (GlimGimpbus *ggb, GError **error);

gboolean glim_gimpbus_gimp_dodgeburn_default (GlimGimpbus *ggb, const gint drawable, const GArray *strokes, GError **error);

gboolean glim_gimpbus_gimp_drawable_height(GlimGimpbus *ggb, const gint drawable, gint *height, GError **error);

gboolean glim_gimpbus_gimp_drawable_transform_rotate_default (GlimGimpbus *ggb, const gint drawable, const gdouble angle, const gboolean auto_center, const gint center_x, const gint center_y, const gboolean interpolate, const GimpTransformResize clip_result, GError **error);

gboolean glim_gimpbus_gimp_drawable_transform_scale (GlimGimpbus *ggb, const gint drawable, const gdouble x0, const gdouble y0, const gdouble x1, const gdouble y1, const gint transform_direction, const gint interpolation, const gint supersample, const gint recursion_level, const gint clip_result, GError **error);

gboolean glim_gimpbus_gimp_drawable_type (GlimGimpbus *ggb, const gint drawable, gint *type, GError **error);

gboolean glim_gimpbus_gimp_drawable_width(GlimGimpbus *ggb, const gint drawable, gint *width, GError **error);

gboolean glim_gimpbus_gimp_edit_bucket_fill (GlimGimpbus *ggb, const gint drawable, const gint fill_mode, const gint paint_mode, const gdouble opacity, const gdouble threshold, const gint sample_merged, const gdouble x, const gdouble y, GError **error);

gboolean glim_gimpbus_gimp_edit_named_copy (GlimGimpbus *ggb, const gint drawable, const gchar *buffer_name, GError **error);

gboolean glim_gimpbus_gimp_edit_named_paste (GlimGimpbus *ggb, const gint drawable, const gchar *buffer_name, const gboolean paste_into, GError **error);

gboolean glim_gimpbus_gimp_edit_stroke(GlimGimpbus *ggb,gint drawable, GError **error);

gboolean glim_gimpbus_gimp_ellipse_select (GlimGimpbus *ggb, const gint image, const gdouble left, const gdouble top, const gdouble width, const gdouble height, const gint operation, const gint antialias, const gint feather, const gdouble radius, GError **error);

gboolean glim_gimpbus_gimp_eraser_default (GlimGimpbus *ggb, const gint drawable, const GArray *strokes, GError *error);

gboolean glim_gimpbus_gimp_file_save (GlimGimpbus *ggb, GimpRunMode run_mode, const gint image, const gint drawable, const gchar *filename, const gchar *raw_filename, GError **error);

gboolean glim_gimpbus_gimp_file_load (GlimGimpbus *ggb, GimpRunMode run_mode, const gchar *filename, const gchar *raw_filename, gint *imagep, GError **error);

gboolean glim_gimpbus_gimp_fonts_get_list (GlimGimpbus *ggb, const gchar *filter, gchar ***font_list, GError **error);

gboolean glim_gimpbus_gimp_free_select (GlimGimpbus *ggb, const gint image, const GArray *segments, const GimpChannelOps operation, const gboolean antialias, const gboolean feather, const gdouble feather_radius, GError **error);

gboolean glim_gimpbus_gimp_image_add_layer (GlimGimpbus *ggb, const gint image, const gint layer, const gint position, GError **error);

gboolean glim_gimpbus_gimp_image_crop (GlimGimpbus *ggb, const gint image, const gint new_width, const gint new_height, const gint offx, const gint offy, GError **error);

gboolean glim_gimpbus_gimp_image_flatten (GlimGimpbus *ggb, const gint image, gint *layerp, GError **error);

gboolean glim_gimpbus_gimp_image_flip (GlimGimpbus *ggb, const gint image, const gint flip_type, GError **error);

gboolean glim_gimpbus_gimp_image_get_active_drawable (GlimGimpbus *ggb, const gint image, gint *drawp, GError **error);

gboolean glim_gimpbus_gimp_image_height (GlimGimpbus *ggb, const gint image, gint *height, GError **error);

gboolean glim_gimpbus_gimp_image_is_valid (GlimGimpbus *ggb, const gint image,  gint *valid, GError **error);

gboolean glim_gimpbus_gimp_image_new (GlimGimpbus *ggb, const gint width, const gint height, const gint type, gint *imagep, GError **error);

gboolean glim_gimpbus_gimp_image_scale (GlimGimpbus *ggb, const gint image, const gint new_width, const gint new_height, GError **error);

gboolean glim_gimpbus_gimp_image_width (GlimGimpbus *ggb, const gint image, gint *width, GError **error);

gboolean glim_gimpbus_gimp_invert (GlimGimpbus *ggb, const gint drawable, GError **error);

gboolean glim_gimpbus_gimp_layer_new(GlimGimpbus *ggb, const gint image, const gchar *name, const gint width, const gint height, const gint type, const gdouble opacity, const gint mode, gint *layer, GError **error);

gboolean glim_gimpbus_gimp_message (GlimGimpbus *ggb, const gchar *message, GError **error);

gboolean glim_gimpbus_gimp_paintbrush (GlimGimpbus *ggb,  const gint drawable, const gdouble fade_out, const GArray *strokes, const gint method, const gdouble gradient_length, GError **error);

gboolean glim_gimpbus_gimp_perspective (GlimGimpbus *ggb, const gint drawable, const gboolean interpolation, const gdouble x0, const gdouble y0, const gdouble x1, const gdouble y1, const gdouble x2, const gdouble y2, const gdouble x3, const gdouble y3, GError **error);

gboolean glim_gimpbus_gimp_posterize (GlimGimpbus *ggb, const gint drawable, const gint layers, GError **error);

gboolean glim_gimpbus_gimp_rect_select (GlimGimpbus *ggb, const gint image, const gdouble left, const gdouble top, const gdouble width, const gdouble height, const gint operation, const gint feather, const gdouble radius, GError **error);

gboolean glim_gimpbus_gimp_selection_all (GlimGimpbus *ggb, const gint image, GError **error);	

gboolean glim_gimpbus_gimp_selection_invert (GlimGimpbus *ggb, const gint image, GError **error);

gboolean glim_gimpbus_gimp_selection_none (GlimGimpbus *ggb, const gint image, GError **error);

gboolean glim_gimpbus_gimp_smudge (GlimGimpbus *ggb, const gint drawable, const gdouble pressure, const GArray *strokes, GError **error);

gboolean glim_gimpbus_gimp_text_fontname (GlimGimpbus *ggb, const gint image, const gint drawable, const gdouble x, const gdouble y, const gchar *text, const gint border, const gboolean antialias, const gdouble size, const GimpSizeType size_type, const gchar *fontname, GError **error);

gboolean glim_gimpbus_list_pdb (GlimGimpbus *ggb, gchar ***functions, GError **error);

gboolean glim_gimpbus_pdb_gimp_drawable_get_pixel (GlimGimpbus *ggb, const gint drawable, const int xcord, const int ycord, GArray **pixval, GError **error);

gboolean glim_gimpbus_gimp_drawable_set_pixel (GlimGimpbus *ggb, const gint drawable, const int xcord, const int ycord, const int num_channels, const GArray *pixel, GError **error);

gboolean glim_gimpbus_pdb_gimp_image_get_layers (GlimGimpbus *ggb, const gint image, GArray **layers, GError **error);

gboolean glim_gimpbus_gimp_image_transform_get (GlimGimpbus *ggb, const gint drawable, GArray **pixels, GError **error);

gboolean glim_gimpbus_gimp_image_transform_set (GlimGimpbus *ggb, const gint drawable, GArray *pixels, GError **error);

#endif // __GLIM_GIMPBUS_H__
