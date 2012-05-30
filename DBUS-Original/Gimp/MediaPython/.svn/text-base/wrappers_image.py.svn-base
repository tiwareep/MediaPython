#------------------------------------------------------------------------------------------------
#Image-based Procedures

def image_is_valid (image):
    return int(gimp_image_is_valid(image))

def image_height (image):
    if image_is_valid(image):
        return int(gimp_image_height (image))
    else:
        raise InputError(image, 'Invalid image ID.')

def image_width (image):
    if image_is_valid(image):
        return int(gimp_image_width (image))
    else:
        raise InputError(image, 'Invalid image ID.')

def image_crop (image, new_width, new_height, offx, offy):
    if image_is_valid(image):
        if (new_width+offx)>image_width(image):
            raise InputError(new_width, 'Area to crop must be inside image boundaries')
        elif (new_height+offy)>image_height(image):
            raise InputError(new_height, 'Area to crop must be inside image boundaries')
        else:
            gimp_image_crop (image, new_width, new_height, offx, offy)
    else: 
        raise InputError(image, 'Invalid image ID')


def image_flatten (image):
    if image_is_valid(image):
        gimp_image_flatten(image)
    else:
        raise InputError(image, 'Invalid image ID')

# Split image_flip into hflip and vflip.
def image_hflip (image):
    if image_is_valid(image):
        gimp_image_flip (image, 0)
        context_update_displays()
    else:
        raise InputError(image, 'Invalid image ID')

def image_vflip (image):
    if image_is_valid(image):
        gimp_image_flip (image, 1)
        context_update_displays()
    else:
        raise InputError(image, 'Invalid image ID')

def image_get_active_drawable (image):
    if image_is_valid(image):
        return int(gimp_image_get_active_drawable (image))
    else:
        raise InputError(image, 'Invalid image ID')

# Eliminates the Type parameter (sets it to RGB)
def image_new (width, height):
    if width<=0:
        raise InputError(width, 'Width must be greater than zero')
    elif height<=0:
        raise InputError(height, 'Height must be greater than zero')
    else:
        i=int(gimp_image_new (width, height, 0))
        j=int(gimp_layer_new (i, "base", width, height, 0, 100, 0))
        gimp_image_add_layer(i, j, -1)
        gimp_edit_bucket_fill(gimp_image_get_active_drawable(i), 1, 0, 100, 0, 0, 10, 10)
        print "Image ID =", i
        print "Layer ID =", j
        return i

def image_hscale (image, new_width):
    if new_width<=0:
        raise InputError(new_width, 'Width must be greater than zero.')
    else: 
        if image_is_valid(image):
            gimp_image_scale(image, new_width, image_height(image))
            context_update_displays()
        else:
            raise InputError(image, 'Invalid image ID')

def image_vscale (image, new_height):
    if new_height<=0:
        raise InputError(new_height, 'Height must be greater than zero.')
    else:
        if image_is_valid(image):
            gimp_image_scale (image, image_width(image), new_height)
            context_update_displays()
        else:
            raise InputError(image, 'invalid image ID')

def image_prop_scale (image, new_width):
    if new_width<=0:
        raise InputError(new_width, 'Width must be greater than zero.')
    else:
        if image_is_valid(image):
            gimp_image_scale (image, new_width, ((float(new_width)/float(image_width(image)))*float(image_height(image))))
            context_update_displays()
        else:
            raise InputError(image, 'Invald image ID')


def image_posterize (image, levels):
    if not(image_is_valid(image)):
        raise InputError(image, 'Invalid image ID')
    else:
        gimp_posterize (image_get_active_drawable(image), levels)
        context_update_displays()

def image_perspective(image, x0, y0, x1, y1, x2, y2, x3, y3):
    if not(image_is_valid(image)):
        raise InputError(image, 'Invalid image ID')
    else:
        gimp_perspective(image_get_active_drawable(image), 0, x0, y0, x1, y1, x2, y2, x3, y3)
        context_update_displays()


def image_invert_colors (image):
    if not(image_is_valid(image)):
        raise InputError(image, 'Invalid image ID')
    else:
        gimp_invert(image_get_active_drawable(image))
        context_update_displays()

def image_show (image):
    if not(image_is_valid(image)):
        raise InputError(image, 'Invalid image ID')
    else: 
        return gimp_display_new(image)

def image_get_pixel(image,xcord,ycord):
    drawable = image_get_active_drawable(image)
    x = pdb_gimp_drawable_get_pixel(drawable,xcord,ycord)
    a = []
    for i in range(3):
        a.append(int(x[i]))
    return a    

def image_set_pixel(image,xcord,ycord, value):
    drawable = image_get_active_drawable(image)
    gimp_drawable_set_pixel(drawable,xcord,ycord,3,value)
    context_update_displays()

def image_transform_pixel(image,xcord,ycord,func):
    old = image_get_pixel(image,xcord,ycord)
    new = func(old)
    image_set_pixel(image,xcord,ycord,new)

def image_transform(image,func):
    drawable = image_get_active_drawable(image)
    x = gimp_image_transform_get(drawable)
    a = []
    c = []
    d = []
    for i in range(len(x)):
        a.append(int(x[i]))
    b = []
    for i in range(0,len(x),3):
        b.append([a[i],a[i+1],a[i+2]])
    for i in range(len(x)/3):
        c.append(func(b[i]))
    for i in range (len(x)/3):
        for j in range (3):
            d.append(c[i][j])      
    gimp_image_transform_set(drawable,d)   
    context_update_displays()
        
# This procedure may not work for images over 250*250 due to DBUS data transfer limits.
# TODO: implement image_variant and image_compute_pixels
