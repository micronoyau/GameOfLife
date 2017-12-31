# -*- coding:utf-8 -*-

class Cell (object):

	def __init__(self, img):
		self.img = img

	def evolve(self, neighbours):
		count = 0
		for n in neighbours:
			if type(n) == LivingCell:
				count += 1
		return count

	def live(self):
		self.__class__ = LivingCell
		self.__init__()

	def kill(self):
		self.__class__ = DeadCell
		self.__init__()

class LivingCell (Cell):

	def __init__(self):
		Cell.__init__(self, "o")

	def evolve(self, neighbours):
		count = Cell.evolve(self, neighbours)
		if not 2 <= count <= 3:
			self.kill()

class DeadCell (Cell):

	def __init__(self):
		Cell.__init__(self, " ")

	def evolve(self, neighbours):
		count = Cell.evolve(self, neighbours)
		if count == 3:
			self.live()
