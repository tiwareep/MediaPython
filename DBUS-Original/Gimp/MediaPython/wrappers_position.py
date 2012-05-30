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
