#Citation: Original image designed by Sam Dunnington, Jun Cheung & Chike Abuah for CSC151.
#Adapted by Chike Abuah for python.

#Notes: Use image size (500,500) with displace of 40 for nice results.
#"randomize" variable will select a slightly random brush. 
#Play with different colors!!

from mediapylib import *

def p_n(col,row):
    return position_new(col,row)

def create_chike_carpet(image,displace):
    context_set_fgcolor([0,0,0])
    image_select_all(image)
    image_fill_selection(image,0,100)	
    context_set_brush("Sparks")
    vmax = image_height(image)
    hmax = image_width(image)		
    for i in range(0,vmax,displace):
       for j in  range(0,hmax,displace):
           image_blot(image,j,i)
    image_select_nothing(image)

def noobulize(width, height, displace, randomize, rgb):
    canvas  = image_new(width,height)
    image_show(canvas)
    create_chike_carpet(canvas, displace)
    brushes = context_list_brushes("")
    color = rgb
    context_set_brush(brushes[randomize % 46])
    
    image_select_free(canvas, REPLACE, 
                             p_n((width * .4), height), 
                             p_n( (width * .6), (height * .8)),
                             p_n( (width * .2), (height * .4)), 
                             p_n( 0, (height * .6)), 
                             p_n( 0, height))

    context_set_fgcolor([235,251,13])
    image_stroke_selection(canvas)
    context_set_fgcolor(color)
    image_fill_selection(canvas,0,100)
    context_set_fgcolor(color)

    image_select_free(canvas, REPLACE,
                             p_n( (width * .2), (height * .4)),
                             p_n( (width * .3), (height * .7)),
                             p_n( (width * .6), (height * .8)),
                             p_n( (width * .3), (height * .9)),
                             p_n( (width * (4.0/15)), height),
                             p_n( (width * (2.0/15)), height),
                             p_n( (width * .1), (height * .9)),
                             p_n( 0, (height * (13.0/15))),
                             p_n( 0, (height * (11.0/15))),
                             p_n( (width * .1),(height * .7)))

    complement = rgb_complement(color)
    context_set_fgcolor(complement)
    image_fill_selection(canvas,0,100)

    image_select_free(canvas, REPLACE, 
                             p_n( (width * .2), height), 
                             p_n( (width * .4), (height * .8)), 
                             p_n( (width * .2), (height * .6)), 
                             p_n( 0, (height * .8)))

    context_set_fgcolor([235,251,13])  
    image_stroke_selection(canvas)
    context_set_fgcolor(rgb_lighter(rgb_lighter(color)))
    image_fill_selection(canvas,0,100)

    image_select_free(canvas,REPLACE, 
                             p_n( (width * .2), (height * .6)), 
                             p_n( (width * .25), (height * .75)), 
                             p_n( (width * .4), (height * .8)), 
                             p_n( (width * .25), (height * (17.0/ 20))), 
                             p_n( (width * .2), height), 
                             p_n( (width * (45.0/ 300)), (height * (17.0/ 20))),
                             p_n( 0, (height * .8)),
                             p_n( (width * (45.0/ 300)), (height * .75)))

    context_set_fgcolor(complement)
    image_fill_selection(canvas,0,100)

    image_select_free(canvas, REPLACE, 
                             p_n( (width* .2), (height* .9)), 
                             p_n( (width* .3), (height* .8)), 
                             p_n( (width* .2), (height* .7)), 
                             p_n( (width* .1), (height* .8)))

    context_set_fgcolor([235,251,13])  
    image_stroke_selection(canvas)
    context_set_fgcolor(rgb_lighter(rgb_lighter(rgb_lighter(color))))
    image_fill_selection(canvas,0,100)

    image_select_free(canvas, REPLACE,
     p_n ((width * .2), (height * .7)),
     p_n ((width * .225), (height * .775)),
     p_n ((width * .3), (height * .8)),
     p_n ((width * .225), (height * .825)),
     p_n ((width * .2), (height * .9)),
     p_n ((width * .175), (height * .825)),
     p_n ((width * .1), (height * .8)),
     p_n ((width * .175), (height * .775)))

    context_set_fgcolor(complement)
    image_fill_selection(canvas,0,100)

    image_select_free(canvas, REPLACE, 
     p_n( ( width* .2), ( height* .85)), 
     p_n( ( width* .25), ( height* .8)), 
     p_n( ( width* .2), ( height* .75)), 
     p_n( ( width* .15), ( height* .8)))

    context_set_fgcolor([237,251,13])
    image_stroke_selection(canvas)
    context_set_fgcolor(rgb_lighter(rgb_lighter(rgb_lighter(rgb_lighter(color)))))
    image_fill_selection(canvas,0,100)

    image_select_nothing(canvas)


