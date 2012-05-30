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
