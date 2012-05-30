from mediapylib import *

i = image_new(400, 800)
image_display_new(i)

def draw_and_fill_150_circle(i, x, y, color):
    image_select_ellipse(i, x, y, 150, 150, REPLACE)
    context_set_fgcolor(color)
    image_fill_selection(i, 0, 50)
    
def int_circle_1():
    image_select_ellipse(i, 120, 10, 150, 150, INTERSECT)
def int_circle_2():
    image_select_ellipse(i, 170, 30, 150, 150, INTERSECT)
def int_circle_3():
    image_select_ellipse(i, 200, 90, 150, 150, INTERSECT)
def int_circle_4():
    image_select_ellipse(i, 180, 150, 150, 150, INTERSECT)
def int_circle_5():
    image_select_ellipse(i, 120, 170, 150, 150, INTERSECT)   
def int_circle_6():
    image_select_ellipse(i, 60, 150, 150, 150, INTERSECT) 
def int_circle_7():
    image_select_ellipse(i, 35, 90, 150, 150, INTERSECT)  
def int_circle_8():
    image_select_ellipse(i, 60, 30, 150, 150, INTERSECT)   
    
def add_circle_1():
    image_select_ellipse(i, 120, 10, 150, 150, ADD)
def add_circle_2():
    image_select_ellipse(i, 170, 30, 150, 150, ADD)
def add_circle_3():
    image_select_ellipse(i, 200, 90, 150, 150, ADD)
def add_circle_4():
    image_select_ellipse(i, 180, 150, 150, 150, ADD)
def add_circle_5():
    image_select_ellipse(i, 120, 170, 150, 150, ADD)   
def add_circle_6():
    image_select_ellipse(i, 60, 150, 150, 150, ADD) 
def add_circle_7():
    image_select_ellipse(i, 35, 90, 150, 150, ADD)  
def add_circle_8():
    image_select_ellipse(i, 60, 30, 150, 150, ADD)  
    
    
color_1 = (236, 225, 57)
color_12 = (255, 222, 1)
color_13 = (253, 184, 19)
color_2 = (253, 184, 19)
color_23 = (246, 130, 31)
color_24 = (241, 80, 36)
color_3 = (243, 77, 0)
color_34 = (217, 31, 68)
color_35 = (153, 29, 57)
color_4 = (166, 0, 115)
color_45 = (81, 0, 79)
color_46 = (57, 0, 53)
color_5 = (0, 0, 0)
color_56 = (1, 65, 113)
color_57 = (0, 106, 146)
color_6 = (0, 90, 137)
color_67 = (0, 128, 137)
color_68 = (0, 116, 89)
color_7 = (56, 120, 86)
color_78 = (82, 149, 70)
color_71 = (119, 170, 67)
color_8 = (135, 198, 51)
color_81 = (166, 206, 57)
color_82 = (224, 209, 30)

#circle_1
add_circle_1()
context_set_fgcolor(color_1)
image_fill_selection(i, 0, 100)
#circle_2
image_select_nothing(i)
add_circle_2()
context_set_fgcolor(color_2)
image_fill_selection(i, 0, 100)
#circle_3
image_select_nothing(i)
add_circle_3()
context_set_fgcolor(color_3)
image_fill_selection(i, 0, 100)
#circle_4
image_select_nothing(i)
add_circle_4()
context_set_fgcolor(color_4)
image_fill_selection(i, 0, 100)
#circle_5
image_select_nothing(i)
add_circle_5()
context_set_fgcolor(color_5)
image_fill_selection(i, 0, 100)
#circle_6
image_select_nothing(i)
add_circle_6()
context_set_fgcolor(color_6)
image_fill_selection(i, 0, 100)
#circle_7
image_select_nothing(i)
add_circle_7()
context_set_fgcolor(color_7)
image_fill_selection(i, 0, 100)
#circle_8
image_select_nothing(i)
add_circle_8()
context_set_fgcolor(color_8)
image_fill_selection(i, 0, 100)

#circle_12
image_select_nothing(i)
add_circle_1()
int_circle_2()
context_set_fgcolor(color_12)
image_fill_selection(i, 0, 100)
#circle_23
image_select_nothing(i)
add_circle_2()
int_circle_3()
context_set_fgcolor(color_23)
image_fill_selection(i, 0, 100)
#circle_34
image_select_nothing(i)
add_circle_3()
int_circle_4()
context_set_fgcolor(color_34)
image_fill_selection(i, 0, 100)
#circle_45
image_select_nothing(i)
add_circle_4()
int_circle_5()
context_set_fgcolor(color_45)
image_fill_selection(i, 0, 100)
#circle_56
image_select_nothing(i)
add_circle_5()
int_circle_6()
context_set_fgcolor(color_56)
image_fill_selection(i, 0, 100)
#circle_67
image_select_nothing(i)
add_circle_6()
int_circle_7()
context_set_fgcolor(color_67)
image_fill_selection(i, 0, 100)
#circle_78
image_select_nothing(i)
add_circle_7()
int_circle_8()
context_set_fgcolor(color_78)
image_fill_selection(i, 0, 100)
#circle_81
image_select_nothing(i)
add_circle_8()
int_circle_1()
context_set_fgcolor(color_81)
image_fill_selection(i, 0, 100)

#circle_13
image_select_nothing(i)
add_circle_1()
int_circle_3()
context_set_fgcolor(color_13)
image_fill_selection(i, 0, 100)
#circle_24
image_select_nothing(i)
add_circle_2()
int_circle_4()
context_set_fgcolor(color_24)
image_fill_selection(i, 0, 100)
#circle_35
image_select_nothing(i)
add_circle_3()
int_circle_5()
context_set_fgcolor(color_35)
image_fill_selection(i, 0, 100)
#circle_46
image_select_nothing(i)
add_circle_4()
int_circle_6()
context_set_fgcolor(color_46)
image_fill_selection(i, 0, 100)
#circle_57
image_select_nothing(i)
add_circle_5()
int_circle_7()
context_set_fgcolor(color_57)
image_fill_selection(i, 0, 100)
#circle_68
image_select_nothing(i)
add_circle_6()
int_circle_8()
context_set_fgcolor(color_68)
image_fill_selection(i, 0, 100)
#circle_71
image_select_nothing(i)
add_circle_7()
int_circle_1()
context_set_fgcolor(color_71)
image_fill_selection(i, 0, 100)
#circle_82
image_select_nothing(i)
add_circle_8()
int_circle_2()
context_set_fgcolor(color_82)
image_fill_selection(i, 0, 100)

image_select_free(i, REPLACE, (170, 165), (190, 187), (212, 165), (198, 160))
image_select_ellipse(i, 170, 150, 20, 20, ADD)
image_select_ellipse(i, 193, 150, 20, 20, ADD)
image_fill_selection(i, 1, 100)

image_select_free(i, REPLACE, (183, 317), (173, 769), (221, 769), (205, 317))
image_select_ellipse(i, 178, 362, 7, 7, ADD)
image_select_ellipse(i, 178, 373, 7, 7, ADD)
image_select_ellipse(i, 178, 385, 7, 7, ADD)
image_select_ellipse(i, 204, 362, 7, 7, ADD)
image_select_ellipse(i, 204, 373, 7, 7, ADD)
image_select_ellipse(i, 204, 385, 7, 7, ADD)
context_set_fgcolor((0, 0, 0))
image_fill_selection(i, 0, 100)
image_select_nothing(i)
image_select_ellipse(i, 172, 385, 20, 20, ADD)
image_select_ellipse(i, 172, 788, 23, 23, ADD)
image_select_ellipse(i, 167, 595, 7, 7, REPLACE)
image_select_ellipse(i, 204, 595, 7, 7, ADD)