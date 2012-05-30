from mediapylib import *
from random import randint

def random_plus(image, num_v, num_h, top_x1, top_x2, top_y1, top_y2, left_x1, left_x2, left_y1, left_y2, right_x1, right_x2, right_y1, right_y2, bot_x1, bot_x2, bot_y1, bot_y2):
    context_set_brush("Circle (01)")
    for i in range(num_v):
        xleft = randint(left_x1, left_x2)
        yleft = randint(left_y1, left_y2)
        xright = randint(right_x1, right_x2)
        yright = randint(right_y1, right_y2)
        image_paint_line(image, xleft, yleft, xright, yright)
    for i in range(num_h):
        xtop = randint(top_x1, top_x2)
        ytop = randint(top_y1, top_y2)
        xbot = randint(bot_x1, bot_x2)
        ybot = randint(bot_y1, bot_y2)
        image_paint_line(image, xtop, ytop, xbot, ybot)
    