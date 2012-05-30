#---------------------------------------------------------------------------------------------
#Selection Procedures

def image_select_rectangle(image, left, top, width, height, operation):
    if not(image_is_valid(image)):
        raise InputError(image, 'Invalid image ID')
    elif top>image_height(image) or top+height>image_height(image):
        raise InputError(image_width, 'Coordinates must be within image bounds')
    elif left>image_width(image) or left+width>image_width(image):
        raise InputError(image_height, 'Coordinates must be within image bounds')
    elif operation<0 or operation>3:
        raise InputError(operation, 'Invalid Operation')
    else:
        gimp_rect_select(image, left, top, width, height, operation, 0, 0)

def image_select_all(image):
    if not(image_is_valid(image)):
        raise InputError(image, 'Invalid image ID')
    else:
        gimp_selection_all(image)

def image_select_inverse(image):
    if not (image_is_valid(image)):
        raise InputError(image, 'Invalid image ID')
    else:
        gimp_selection_invert(image)

def image_select_nothing(image):
    if not (image_is_valid(image)):
        raise InputError(image, 'Invalid image ID')
    else:
        gimp_selection_none(image)

def image_select_ellipse(image, left, top, width, height, operation):
    if not (image_is_valid(image)):
        raise InputError(image, 'Invalid image ID')
    elif top>image_height(image) or top+height>image_height(image):
        raise InputError(image_width, 'Coordinates must be within image bounds')
    elif left>image_width(image) or left+width>image_width(image):
        raise InputError(image_height, 'Coordinates must be within image bounds')
    elif operation<0 or operation>3:
        raise InputError(operation, 'Invalid Operation')
    else:
        gimp_ellipse_select(image, left, top, width, height, operation, 0, 0, 0)

# Color_source is 0 for fg, 1 for bg. 
def image_fill_selection(image, color_source, opacity):
    if not image_is_valid(image):
        raise InputError(image, 'Invalid image ID')
    elif opacity<0 or opacity>100:
        raise InputError(opacity, 'Opacity must be between 0 and 100')
    else:
        drawable = image_get_active_drawable(image)
        gimp_edit_bucket_fill(drawable, color_source, 0, opacity, 0, 0, 0, 0)
        context_update_displays()

def image_select_free(image, operation, *arg):
    if not image_is_valid(image):
        raise InputError(image, 'Invalid image ID')
    elif operation<0 or operation>3:
        raise InputError(operation, 'Invalid Operation')
    else:
        x = []
        for y in arg:
            x.append(y[0])
            x.append(y[1])
        gimp_free_select(image, x, operation, 0, 0, 0)
        context_update_displays()


def image_stroke_selection(image):
    drawable = image_get_active_drawable(image)
    gimp_edit_stroke(drawable)
    context_update_displays()
