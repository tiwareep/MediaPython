#! /usr/bin/env python

#THIS IS A GENERATED FILE. DO NOT EDIT.

import dbus
bus = dbus.SessionBus()
gimpbus = bus.get_object('edu.grinnell.glimmer.gimpbus', '/edu/grinnell/glimmer/gimpbus')

ADD=0
SUBTRACT=1
REPLACE=2
INTERSECT=3

gimp_image_new = gimpbus.get_dbus_method('gimp_image_new', 'edu.grinnell.glimmer.gimpbus')

gimp_selection_all = gimpbus.get_dbus_method('gimp_selection_all', 'edu.grinnell.glimmer.gimpbus')

gimp_edit_named_copy = gimpbus.get_dbus_method('gimp_edit_named_copy', 'edu.grinnell.glimmer.gimpbus')

gimp_text_fontname = gimpbus.get_dbus_method('gimp_text_fontname', 'edu.grinnell.glimmer.gimpbus')

gimp_context_get_foreground = gimpbus.get_dbus_method('gimp_context_get_foreground', 'edu.grinnell.glimmer.gimpbus')

gimp_drawable_transform_scale = gimpbus.get_dbus_method('gimp_drawable_transform_scale', 'edu.grinnell.glimmer.gimpbus')

gimp_layer_new = gimpbus.get_dbus_method('gimp_layer_new', 'edu.grinnell.glimmer.gimpbus')

gimp_selection_invert = gimpbus.get_dbus_method('gimp_selection_invert', 'edu.grinnell.glimmer.gimpbus')

gimp_drawable_height = gimpbus.get_dbus_method('gimp_drawable_height', 'edu.grinnell.glimmer.gimpbus')

pdb_gimp_drawable_get_pixel = gimpbus.get_dbus_method('pdb_gimp_drawable_get_pixel', 'edu.grinnell.glimmer.gimpbus')

gimp_selection_none = gimpbus.get_dbus_method('gimp_selection_none', 'edu.grinnell.glimmer.gimpbus')

gimp_message = gimpbus.get_dbus_method('gimp_message', 'edu.grinnell.glimmer.gimpbus')

gimp_posterize = gimpbus.get_dbus_method('gimp_posterize', 'edu.grinnell.glimmer.gimpbus')

gimp_displays_flush = gimpbus.get_dbus_method('gimp_displays_flush', 'edu.grinnell.glimmer.gimpbus')

gimp_image_transform_get = gimpbus.get_dbus_method('gimp_image_transform_get', 'edu.grinnell.glimmer.gimpbus')

gimp_blot = gimpbus.get_dbus_method('gimp_blot', 'edu.grinnell.glimmer.gimpbus')

gimp_image_scale = gimpbus.get_dbus_method('gimp_image_scale', 'edu.grinnell.glimmer.gimpbus')

gimp_free_select = gimpbus.get_dbus_method('gimp_free_select', 'edu.grinnell.glimmer.gimpbus')

gimp_edit_bucket_fill = gimpbus.get_dbus_method('gimp_edit_bucket_fill', 'edu.grinnell.glimmer.gimpbus')

gimp_context_get_background = gimpbus.get_dbus_method('gimp_context_get_background', 'edu.grinnell.glimmer.gimpbus')

list_pdb = gimpbus.get_dbus_method('list_pdb', 'edu.grinnell.glimmer.gimpbus')

gimp_image_add_layer = gimpbus.get_dbus_method('gimp_image_add_layer', 'edu.grinnell.glimmer.gimpbus')

gimp_image_flatten = gimpbus.get_dbus_method('gimp_image_flatten', 'edu.grinnell.glimmer.gimpbus')

gimp_smudge = gimpbus.get_dbus_method('gimp_smudge', 'edu.grinnell.glimmer.gimpbus')

gimp_image_crop = gimpbus.get_dbus_method('gimp_image_crop', 'edu.grinnell.glimmer.gimpbus')

gimp_drawable_transform_rotate_default = gimpbus.get_dbus_method('gimp_drawable_transform_rotate_default', 'edu.grinnell.glimmer.gimpbus')

gimp_perspective = gimpbus.get_dbus_method('gimp_perspective', 'edu.grinnell.glimmer.gimpbus')

gimp_context_get_brush = gimpbus.get_dbus_method('gimp_context_get_brush', 'edu.grinnell.glimmer.gimpbus')

gimp_brushes_get_list = gimpbus.get_dbus_method('gimp_brushes_get_list', 'edu.grinnell.glimmer.gimpbus')

gimp_drawable_width = gimpbus.get_dbus_method('gimp_drawable_width', 'edu.grinnell.glimmer.gimpbus')

gimp_drawable_set_pixel = gimpbus.get_dbus_method('gimp_drawable_set_pixel', 'edu.grinnell.glimmer.gimpbus')

gimp_context_set_background = gimpbus.get_dbus_method('gimp_context_set_background', 'edu.grinnell.glimmer.gimpbus')

gimp_image_height = gimpbus.get_dbus_method('gimp_image_height', 'edu.grinnell.glimmer.gimpbus')

gimp_edit_named_paste = gimpbus.get_dbus_method('gimp_edit_named_paste', 'edu.grinnell.glimmer.gimpbus')

gimp_file_save = gimpbus.get_dbus_method('gimp_file_save', 'edu.grinnell.glimmer.gimpbus')

gimp_context_set_foreground = gimpbus.get_dbus_method('gimp_context_set_foreground', 'edu.grinnell.glimmer.gimpbus')

gimp_paintbrush = gimpbus.get_dbus_method('gimp_paintbrush', 'edu.grinnell.glimmer.gimpbus')

gimp_fonts_get_list = gimpbus.get_dbus_method('gimp_fonts_get_list', 'edu.grinnell.glimmer.gimpbus')

gimp_image_width = gimpbus.get_dbus_method('gimp_image_width', 'edu.grinnell.glimmer.gimpbus')

gimp_airbrush = gimpbus.get_dbus_method('gimp_airbrush', 'edu.grinnell.glimmer.gimpbus')

gimp_image_is_valid = gimpbus.get_dbus_method('gimp_image_is_valid', 'edu.grinnell.glimmer.gimpbus')

gimp_file_load = gimpbus.get_dbus_method('gimp_file_load', 'edu.grinnell.glimmer.gimpbus')

gimp_invert = gimpbus.get_dbus_method('gimp_invert', 'edu.grinnell.glimmer.gimpbus')

gimp_edit_stroke = gimpbus.get_dbus_method('gimp_edit_stroke', 'edu.grinnell.glimmer.gimpbus')

gimp_display_new = gimpbus.get_dbus_method('gimp_display_new', 'edu.grinnell.glimmer.gimpbus')

gimp_ellipse_select = gimpbus.get_dbus_method('gimp_ellipse_select', 'edu.grinnell.glimmer.gimpbus')

gimp_context_set_brush = gimpbus.get_dbus_method('gimp_context_set_brush', 'edu.grinnell.glimmer.gimpbus')

gimp_image_transform_set = gimpbus.get_dbus_method('gimp_image_transform_set', 'edu.grinnell.glimmer.gimpbus')

gimp_eraser_default = gimpbus.get_dbus_method('gimp_eraser_default', 'edu.grinnell.glimmer.gimpbus')

gimp_drawable_type = gimpbus.get_dbus_method('gimp_drawable_type', 'edu.grinnell.glimmer.gimpbus')

gimp_context_get_fg = gimpbus.get_dbus_method('gimp_context_get_fg', 'edu.grinnell.glimmer.gimpbus')

gimp_image_get_active_drawable = gimpbus.get_dbus_method('gimp_image_get_active_drawable', 'edu.grinnell.glimmer.gimpbus')

gimp_image_flip = gimpbus.get_dbus_method('gimp_image_flip', 'edu.grinnell.glimmer.gimpbus')

gimp_dodgeburn_default = gimpbus.get_dbus_method('gimp_dodgeburn_default', 'edu.grinnell.glimmer.gimpbus')

gimp_rect_select = gimpbus.get_dbus_method('gimp_rect_select', 'edu.grinnell.glimmer.gimpbus')

