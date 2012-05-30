#------------------------------------------------------------------------------------------------
#RGB based procedures

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

