#------------------------------------------------------------------------------------------------
#A simple implementation of Logo's turtles by MediaPython Glimmer'11

#------------------------------------------------------------------------------------------------
#Create the turtle object, all of its attributes and functions.
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
