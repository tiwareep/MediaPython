from mediapylib import *

def fill_shape(image, up_left, color, opacity):
    height = image_height(image)
    width = image_width(image)
    image_select_free(image, REPLACE, 
                      (up_left, 0), 
                      (up_left, ((34.0/182)*height)), 
                      ((up_left-((87.0/485)*width)), ((77.0/182)*height)), 
                      ((up_left-((87.0/485)*width)), ((103.0/182)*height)),
                      (up_left, ((147.0/182)*height)), 
                      (up_left, height), 
                      ((up_left+((27.0/485)*width)), height),
                      ((up_left+((27.0/485)*width)), (147.0/182)*height),
                      ((up_left+((112.0/485)*width)), (103.0/182)*height),
                      ((up_left+((112.0/485)*width)), (77.0/182)*height), 
                      ((up_left+((27.0/485)*width)), (34.0/182)*height), 
                      ((up_left+((27.0/485)*width)), 0.0))
    image_select_free(image, SUBTRACT, 
                      ((up_left+(13.0/485)*width), (42.0/182)*height), 
                      ((up_left-(58.0/485)*width), (77.0/182)*height), 
                      ((up_left-(58.0/485)*width), (103.0/182)*height), 
                      ((up_left+(13.0/485)*width), (140.0/182)*height), 
                      ((up_left+(85.0/485)*width), (103.0/182)*height), 
                      ((up_left+(85.0/485)*width), (77.0/182)*height))
    context_set_fgcolor(color)
    image_fill_selection(image, 0, opacity)
    
                           

def circles_with_six_sides(width, height, n, c1, c2, opacity1, opacity2):
    i = image_new(width, height)
    image_show(i)
    offs = (width - (n*(35.0/485)*width))/2
    color = 0
    L = []
    for j in range(n):
        L.append(int(j*(35.0/485)*width+offs))
    for t in L[:]: 
        if color == 0:
            fill_shape(i, t, c1, opacity1)
            color = 1
        else:
            fill_shape(i, t, c2, opacity2)
            color = 0
    image_select_nothing(i)
        

    