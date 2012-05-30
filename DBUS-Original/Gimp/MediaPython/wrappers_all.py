import dbus
from get_dbus_methods_python import *
from math import sin, cos, radians, floor

class Error(Exception):
    """Base class for exceptions in this module."""
    pass

class InputError(Error):
    """Exception raised for errors in the input.

    Attributes:
        expr -- input expression in which the error occurred
        msg  -- explanation of the error
    """
    def __init__(self, expr, msg):
        self.expr = expr
        self.msg = msg


#------------------------------------------------------------------------------------------------
#Context Procedures

def context_get_bgcolor( ):
    color=gimp_context_get_background()
    t=(int(255*color[0]), int(255*color[1]), int(255*color[2]))
    return t

def context_get_fgcolor( ):
    color=gimp_context_get_foreground()
    t=(int(255*color[0]), int(255*color[1]), int(255*color[2]))
    return t


# Filter is optional in all context_list functions.
def context_list_brushes(filter=""):
    x = gimp_brushes_get_list(filter)
    a = []
    for i in range(len(x)):
        a.append(str(x[i]))
    return a

def context_list_fonts(filter=""):
    x = gimp_fonts_get_list(filter)
    a = []
    for i in range(len(x)):
        a.append(str(x[i]))
    return a

def context_update_displays( ):
    gimp_displays_flush()

# Set and get take tuples, so: context_set_bgcolor((100, 100, 100)).
def context_set_bgcolor(color):
    red=color[0]
    green=color[1]
    blue=color[2]
    if red<0 or red>255:
        raise InputError(red, 'Red value must be between 0 and 255.')
    elif green<0 or green>255:
        raise InputError(green, 'Green value must be between 0 and 255.')
    elif blue<0 or blue>255:
        raise InputError(blue, 'Blue value must be between 0 and 255.')
    else:
        red2=red/255.0
        green2=green/255.0
        blue2=blue/255.0
        gimp_context_set_background(red2, green2, blue2)
        
def context_set_fgcolor(color):
    red=color[0]
    green=color[1]
    blue=color[2]
    if red<0 or red>255:
        raise InputError(red, 'Red value must be between 0 and 255.')
    elif green<0 or green>255:
        raise InputError(green, 'Green value must be between 0 and 255.')
    elif blue<0 or blue>255:
        raise InputError(blue, 'Blue value must be between 0 and 255.')
    else:
        red2=red/255.0
        green2=green/255.0
        blue2=blue/255.0
        gimp_context_set_foreground(red2, green2, blue2)
        
def context_set_brush(brush):
    found=0
    for item in context_list_brushes():
        if item==brush:
            found=1
    if found==1:
        gimp_context_set_brush(brush)
    else:
        raise InputError(brush, 'Invalid brush name')

def context_get_brush():
    return str(gimp_context_get_brush())
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
        
def image_variant(image,func):
    x = image_show(image)
    image_transform(x,func)
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

#------------------------------------------------------------------------------------------------
#Position Procedures

from math import * 
from random import *

def position_new(x,y):
    return [x,y]


def position_col(pos):
    return pos[0]

def position_row(pos):
    return pos[1]

def position_is_valid(pos):
    if (pos[0] >= 0) and (pos[1] >= 0):
        return 1
    else :
        return 0
  
def position_offset(pos, hoff, voff):
    x = pos[0] + hoff
    y = pos[1] + voff
    newpos = [x,y]
    return newpos

def position_distance(pos1, pos2):
    y = pow(pos2[1]-pos1[1],2)
    x = pow(pos2[0]-pos1[0],2)
    return sqrt(x+y)

def position_interpolate(pos1,pos2,percent):
    x = 1 - percent
    a = percent * position_col (pos2) + x * position_col (pos1)
    b = percent * position_row (pos2) + x * position_row (pos1)
    return [a,b]

seed()

def random_positions(n, cols, rows):
    a = []
    for x in range(n):
        a.append([randint(0,cols), randint(0,rows)])
    return a
class Turtle:
    def __init__(self, image):
        self.x=0
        self.y=0
        self.dir=0
        self.pendown=1
        self.color=context_get_fgcolor()
        self.pentype= context_get_brush()
        self.image=image
    def turn(self, deg):
        self.dir=(int(self.dir)+deg)%360
    def forward(self, amt):
        newx=self.x+(cos(radians(self.dir))*amt)
        newy=self.y+(sin(radians(self.dir))*amt)
        if (self.pendown):
            oldbrush=context_get_brush()
            context_set_brush(self.pentype)
            oldcolor=context_get_fgcolor()
            context_set_fgcolor(self.color)
            image_paint_line(self.image, self.x, self.y, newx, newy)
            context_set_fgcolor(oldcolor)
        self.x=newx
        self.y=newy
    def pen_up(self):
        self.pendown=0
    def pen_down(self):
        self.pendown=1
    def teleport(self, x, y):
        self.x=x
        self.y=y
    def face(self, deg):
        self.dir=deg
    def set_color(self, color):
        self.color=color
    def set_pen(self, pen):
        found=0
        for item in context_list_brushes():
            if item==pen:
                found=1
                if found==1:
                    self.pentype=pen
                else:
                    raise InputError(brush, "Invalid brush name")
    def get_color(self):
        return self.color
    def get_pen(self):
        return self.pentype
    def get_angle(self):
        return self.dir
    def get_image(self):
        return self.image

#-----------------------------------------------------------------------------------------------
# Create wrappers and make things match the MediaScheme function name format.

def turtle_new(image):
    return Turtle(image)

def turtle_clone(turtle):
    i=turtle.image
    newt=Turtle(i)
    newt.x=turtle.x
    newt.y=turtle.y
    newt.set_color(turtle.color)
    newt.set_pen(turtle.pentype)
    newt.face(turtle.dir)
    newt.pendown=turtle.pendown
    return newt

def turtle_forward(turtle, distance):
    turtle.forward(distance)

def turtle_teleport(turtle, x, y):
    turtle.teleport(x, y)
    
def turtle_face(turtle, angle):
    turtle.face(angle)
    
def turtle_turn(turtle, angle):
    turtle.turn(angle)

def turtle_down(turtle):
    turtle.pen_down()
    return turtle

def turtle_up(turtle):
    turtle.pen_up()

def turtle_set_brush(turtle, brush):
    turtle.set_pen(brush)

def turtle_set_color(turtle, color):
    turtle.set_color(color)

def turtle_world(turtle):
    return turtle.image

def turtle_get_brush(turtle):
    return turtle.get_pen()

def turtle_get_color(turtle):
    return turtle.get_color()

def turtle_get_angle(turtle):
    return turtle.get_angle()

def turtle_get_x(turtle):
    return turtle.x

def turtle_get_y(turtle):
    return turtle.y

def turtle_print_position(turtle):
    return (turtle.x, turtle.y) 

#-----------------------------------------------------------------------------------------------
# TODO: Provide some form of documentation for individual procedures? May be identical to 
# MediaScheme documentation.
def rgb_red (color):
    return color[0]

def rgb_green (color):
    return color[1]

def rgb_blue (color):
    return color[2] 

def rgb_redder (color):
    new_red = color[0] + 32
    new_green = color[1] - 32
    new_blue = color[2] - 32
    if new_red > 255:
        new_red = 255
    return [new_red, new_green, new_blue]

def rgb_greener (color):
    new_red = color[0] - 32
    new_green = color[1] + 32
    new_blue = color[2] - 32
    if new_green > 255:
        new_green = 255
    return [new_red, new_green, new_blue]

def rgb_bluer (color):
    new_red = color[0] - 32
    new_green = color[1] - 32
    new_blue = color[2] + 32
    if new_blue > 255:
        new_blue = 255
    return [new_red, new_green, new_blue]

def rgb_complement (color):
    new_red = 255 - color[0]
    new_green = 255 - color[1]
    new_blue = 255 - color[2] 
    return [new_red, new_green, new_blue]

def rgb_lighter (color):
    new_red = 32 + color[0]
    new_green = 32 + color[1] 
    new_blue = 32 + color[2]
    if new_red > 255:
        new_red = 255
    if new_green > 255:
        new_green = 255
    if new_blue > 255:
        new_blue = 255
    return [new_red, new_green, new_blue]


def rgb_darker (color):
    new_red = color[0] - 32
    new_green = color[1] - 32
    new_blue = color[2] - 32
    if new_red < 0:
        new_red = 0
    if new_green < 0:
        new_green = 0
    if new_blue < 0:
        new_blue = 0
    return [new_red, new_green, new_blue]

def rgb_new (r, g, b):
    return [r, g, b]

def rgb_phaseshift(color):
    if color[0] > 128:
        new_red = color[0] - 128
    elif color[0] < 128:
        new_red = color[0] + 128
    else:
        new_red = color[0]
    if color[1] > 128:
        new_green = color[1] - 128
    elif color[1] < 128:
        new_green = color[1] + 128
    else: 
        new_green = color[1]
    if color[2] > 128:
        new_blue = color[2] - 128
    elif color[2] < 128:
        new_blue = color[2] + 128
    else: 
        new_blue = color[2]
    return [new_red, new_green, new_blue]

def rgb_rotate (color):
    new_red = color[1]
    new_green = color[2] 
    new_blue = color[0]
    return [new_red, new_green, new_blue]

def rgb_stronger (color):
    if color[0] > color[1] and color[0] > color[2]:
        return rgb_redder (color)
    elif color[1] > color[0] and color[1] > color[2]:
        return rgb_greener (color)
    else:
        return rgb_bluer (color)
    
def rgb_get_hue (color):
    red = float(color[0])
    green = float(color[1])
    blue = float(color[2])
    largest = max (color)
    smallest = min (color)
    chroma = largest - smallest
    if chroma == 0:
        raw_hue = 0
    elif red == largest:
        raw_hue = ((green - blue) / chroma) % 6
    elif green == largest:
        raw_hue = ((blue - red) / chroma) + 2
    elif blue == largest:
        raw_hue = ((red - green) / chroma) + 4
    hue = raw_hue * 60.0
    return int(hue)

def rgb_get_saturation(rgb):
    print max(rgb)
    print min(rgb)
    if max(rgb) == 0.0:
        s = 0.0
    else:
        s = (float(max(rgb)) - float(min(rgb))) / float(max(rgb))
    return int(s*100)

def rgb_get_value(rgb):
    v = (max(rgb)/255.0) * 100.0
    return int(v)

def rgb_to_hsv(rgb):
    hue = rgb_get_hue(rgb)
    sat = rgb_get_saturation(rgb)
    value = rgb_get_value(rgb)
    return (hue, sat, value)

def hsv_to_rgb (hsv):
    hue = hsv[0]
    sat = hsv[1]/100.0
    value = hsv[2]/100.0
    chroma = value * sat
    h = hue/60.0
    x = chroma * (1 - abs (h % 2 - 1.0))
    if h >= 5:
        rgb0 = (chroma, 0, x)
    elif h >= 4:
        rgb0 = (x, 0, chroma)
    elif h >= 3:
        rgb0 = (0, x, chroma)
    elif h >= 2:
        rgb0 = (0, chroma, x)
    elif h >= 1:
        rgb0 = (x, chroma, 0)
    elif h >= 0:
        rgb0 = (chroma, x, 0)
    m = value - chroma
    rgb = (int(255*(rgb0[0] + m)), int(255*(rgb0[1] + m)), int(255*(rgb0[2] + m)))
    return rgb
        

def rgb_change_hue (color, hue):
    return hsv_to_rgb((hue, rgb_get_saturation(rgb), rgb_get_value(rgb)))

