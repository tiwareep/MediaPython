def image_draw_airbrush_line(image, pressure, x1, y1, x2, y2):
    if not(image_is_valid(image)):
        raise InputError(image, 'Invalid image ID')
    elif pressure>100 or pressure<0:
        raise InputError(pressure, 'Pressure must be between 0 and 100')
    elif x1>image_width(image) or x2>image_width(image):
        raise InputError(image_width, 'Coordinates must be inside the image')
    elif y1>image_height(image) or y2>image_height(image):
        raise InputError(image_height, 'Coordinates must be inside the image')
    else:
        gimp_airbrush(image_get_active_drawable(image), pressure, [x1, y1, x2, y2])
        context_update_displays()
        
def image_connect_the_dots_airbrush(image, pressure, *arg):
    if image_is_valid(image):
        if pressure<=100 and pressure>=0:
            x = []
            for y in arg:
                x.append(y[0])
                x.append(y[1])
            gimp_airbrush(image_get_active_drawable(image), pressure, x)
            context_update_displays()
        else: 
            raise InputError(pressure, 'Pressure must be between 0 and 100.')
    else:
        raise InputError(image, 'Invalid image ID')


def image_blot (image, x, y):
    if image_is_valid(image):
        if x>image_width(image):
            raise InputError(x, 'Coordinate must be within image boundaries')
        elif y>image_height(image):
            raise InputError(y, 'Coordinate must be within image boundaries')
        else:
            gimp_blot(image_get_active_drawable(image), x, y)
            context_update_displays()
    else: 
        raise InputError(image, 'Invalid image ID')

def image_smudge_line(image, pressure, x1, y1, x2, y2):
    if not(image_is_valid(image)):
        raise InputError(image, 'Invalid image ID')
    elif pressure>100 or pressure<0:
        raise InputError(pressure, 'Pressure must be between 0 and 100')
    elif x1>image_width(image) or x2>image_width(image):
        raise InputError(image_width, 'Coordinates must be inside the image')
    elif y1>image_height(image) or y2>image_height(image):
        raise InputError(image_height, 'Coordinates must be inside the image')
    else:
        gimp_smudge(image_get_active_drawable(image), pressure, [x1, y1, x2, y2])
        context_update_displays()

def image_connect_the_dots_smudge (image, pressure, *arg):
    if image_is_valid(image):
        if pressure<=100 and pressure>=0:
            x = []
            for y in arg:
                x.append(y[0])
                x.append(y[1])
            gimp_smudge(image_get_active_drawable(image), pressure, x)
            context_update_displays()
        else: 
            raise InputError(pressure, 'Pressure must be between 0 and 100.')
    else:
        raise InputError(image, 'Invalid image ID')


def image_dodgeburn_line(image, x1, y1, x2, y2):
    if not(image_is_valid(image)):
        raise InputError(image, 'Invalid image ID')
    elif x1>image_width(image) or x2>image_width(image):
        raise InputError(image_width, 'Coordinates must be inside the image')
    elif y1>image_height(image) or y2>image_height(image):
        raise InputError(image_height, 'Coordinates must be inside the image')
    else:
        gimp_dodgeburn_default(image_get_active_drawable(image), [x1, y1, x2, y2])
        context_update_displays()

def image_connect_the_dots_dodgeburn (image, *arg):
    if image_is_valid(image):
        x = []
        for y in arg:
            x.append(y[0])
            x.append(y[1])
        gimp_dodgeburn_default(image_get_active_drawable(image), x)
        context_update_displays()
    else:
        raise InputError(image, 'Invalid image ID')

def image_erase_line(image, x1, y1, x2, y2):
    if not(image_is_valid(image)):
        raise InputError(image, 'Invalid image ID')
    elif x1>image_width(image) or x2>image_width(image):
        raise InputError(image_width, 'Coordinates must be inside the image')
    elif y1>image_height(image) or y2>image_height(image):
        raise InputError(image_height, 'Coordinates must be inside the image')
    else:
        gimp_eraser_default(image_get_active_drawable(image), [x1, y1, x2, y2])
        context_update_displays()

def image_connect_the_dots_erase (image, *arg):
    if image_is_valid(image):
        x = []
        for y in arg:
            x.append(y[0])
            x.append(y[1])
        gimp_eraser_default(image_get_active_drawable(image), x)
        context_update_displays()
    else:
        raise InputError(image, 'Invalid image ID')

def image_paint_line(image, x1, y1, x2, y2):
    if not(image_is_valid(image)):
        raise InputError(image, 'Invalid image ID')
    elif x1>image_width(image) or x2>image_width(image):
        raise InputError(image_width, 'Coordinates must be inside the image')
    elif y1>image_height(image) or y2>image_height(image):
        raise InputError(image_height, 'Coordinates must be inside the image')
    else:
        gimp_paintbrush(image_get_active_drawable(image), 0, [x1, y1, x2, y2], 0, 0)
        context_update_displays()

def image_connect_the_dots_paint (image, *arg):
    if image_is_valid(image):
        x = []
        for y in arg:
            x.append(y[0])
            x.append(y[1])
        gimp_paintbrush(image_get_active_drawable(image), 0, x, 0, 0)
        context_update_displays()
    else:
        raise InputError(image, 'Invalid image ID')

