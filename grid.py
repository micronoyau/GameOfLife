# -*- coding:utf-8 -*-

from cell import DeadCell, LivingCell
from copy import deepcopy

class Grid (object):

	def __init__(self, size, init_config):
		self.width = size[0]
		self.height = size[1]
		self.config = []
		self.generation = 1

		for y in range(len(init_config)):
			self.config.append([])
			for x in range(len(init_config[y])):
				self.config[y].append( LivingCell() if init_config[y][x] == 1 else DeadCell() )

	def findNeighbours(self, x, y):
		ret = list()
		if y != self.height-1 : ret.append(self.config[y+1][x])
		if y != self.height-1 and x != self.width-1 : ret.append(self.config[y+1][x+1])
		if x != self.width-1 : ret.append(self.config[y][x+1])
		if x != self.width-1 and y != 0 : ret.append(self.config[y-1][x+1])
		if y != 0 : ret.append(self.config[y-1][x])
		if y != 0 and x != 0 : ret.append(self.config[y-1][x-1])
		if x != 0 : ret.append(self.config[y][x-1])
		if x != 0 and y != self.height-1 : ret.append(self.config[y+1][x-1])
		return ret

	def evolve(self):
		new_config = deepcopy(self.config)
		for x in range(self.width):
			for y in range(self.height):
				new_config[y][x].evolve( self.findNeighbours(x, y) )
		self.config = new_config
		self.generation += 1

	def __str__(self):
		ret = ""
		for y in range(self.height):
			for x in range(self.width):
				ret = ret + ( self.config[y][x].img )
			ret = ret + '\n'
		return ret
