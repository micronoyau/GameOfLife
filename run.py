#!/usr/bin/python

from grid import Grid
from time import sleep
from os import system
from random import random

width = 60
height = 39
speed = 0.01

colony = tuple( tuple( (1 if random() < 0.5 else 0) for _ in range(width) ) for _ in range(height) )

g = Grid( (width,height), colony )

try:
    while True:
        system('clear')
        print "GENERATION {}".format(g.generation)
        print g
        sleep(speed)
        g.evolve()

except KeyboardInterrupt:
    print "\nClosed"
