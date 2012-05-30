from mediapylib import *
from math import cos, sqrt

i = image_new(600, 400)
image_display_new(i)
dennis = turtle_new(i)
turtle_teleport(dennis, 100, 75)
context_set_brush("Circle (01)")

def turtle_draw_polygon(turtle, sides, length):
    int_angle = (sides-2)*180/sides
    for n in range(0, sides):
        turtle_forward(turtle, length)
        turtle_turn(turtle, 180-int_angle)

def turtle_draw_many_polygons (turtle, sides, length, angle, number):
    for n in range (0, number):
        turtle_draw_polygon (dennis, sides, length)
        turtle_turn(dennis, angle)
        
turtle_draw_many_polygons (dennis, 5, 50, 10, 10)

turtle_teleport (dennis, 250, 150)

def turtle_draw_smaller_polygons (turtle, sides, length, percent):
    if length > 3:
        turtle_draw_polygon(turtle, sides, length)
        newlength = (length * (1-(percent/100.0)))
        turtle_draw_smaller_polygons (turtle, sides, newlength, percent)
    else:
        context_update_displays()
        
turtle_draw_smaller_polygons (dennis, 5, 100, 10)

def turtle_draw_smaller_polygons_spiral (turtle, sides, length, percent):
    if length > 3:
        int_angle = (sides-2)*180/sides
        turtle_draw_polygon(turtle, sides, length)
        newlength = length * (1 - (percent/100.0))
        turtle_forward(dennis, length/2)
        turtle_turn (turtle, (180-int_angle)/2 )
        turtle_draw_smaller_polygons_spiral (turtle, sides, newlength, percent)

turtle_teleport (dennis, 315, 75)
turtle_face (dennis, 0)
turtle_draw_smaller_polygons_spiral (dennis, 5, 75, 30)