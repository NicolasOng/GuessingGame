#this file is for the game class, to allow the server to keep track of the state of games much easier.
import random
import math
from rf import *

MAX_INT = 1000

def plus(a, b):
	return a + b

roundFuncs = [
	[add, add_literal, diff, div1, min1, fiftytwothousandonehundredthirtyseven, candiv, reverse, digsort, interlace],
	[multiply3, mod, squaresum, lin10, gcd, roundb, div2, digcounts, gozinta, evensum, digsum],
	[divdig, rand1, hyp, digcount, digpairsum, digsumnum, dist, fibonacci, collatz, sumvardig],
	[cubehole, cylinder, angle, pidig, ball, coinflip, rectnum, custom1, custom2, custom3],
	[sumround, reimann, acceldist, baseconv, multtablesum, binarytablesum, mult5, addtablesum, geoarithseries, seriesproduct],
]

class Game:
	def __init__(self):
		self.players = []
		self.round = -1
		self.currentInputs = [None, None]
		self.currentOutput = None
		self.roundEquation = plus
		self.roundIO = []
		self.nextTurnReq = [False, False]
		self.nextRoundReq = [False, False]
		self.dced = [False, False]
		
	def join(self, user_id):
		self.players.append(user_id)
	
	def newRound(self):
		self.round = self.round + 1
		self.roundIO = []
		#0. reset past round stuff:
		self.nextRoundReq = [False, False]
		self.currentInputs = [None, None]
		self.currentOutput = None
		self.newTurn()
		#1. select an equation based on round
		rfs = roundFuncs[self.round % len(roundFuncs)]
		self.roundEquation = rfs[random.randint(0, len(rfs))]
		##self.roundEquation = plus
		#2. generate random integer inputs and their outputs
		for i in range(5):
			ri1 = random.randint(0, MAX_INT)
			ri2 = random.randint(0, MAX_INT)
			ro = self.roundEquation(ri1, ri2)
			self.roundIO.append([ri1, ri2, ro])
		#3. send this info to the room:
		return {'inputs': self.getRoundInputs()}

	def getRoundInputs(self):
		r = []
		for i in range(5):
			ri1 = self.roundIO[i][0]
			ri2 = self.roundIO[i][1]
			r.append([ri1, ri2])
		return r

	def numPlayers(self):
		return len(self.players)
	
	def newInput(self, user_id, input1):
		#a new input by a user in the game is given.
		#0 - other player hasn't made input
		#1 - other player has
		#2 - user is player, but invalid input
		#3 - either current player has, or user is spectator
		pnum = self.getPlayerNumber(user_id)
		#check if the user is one of the players.
		if (pnum >= 0):
			try:
				a = int(input1)
				assert (a < 9999999999999999999)
			except:
				return 2
			#check if the player has made his input yet
			if (self.currentInputs[pnum] == None):
				self.currentInputs[pnum] = int(input1)
				#check if the other player has made his input yet:
				if (self.currentInputs[1-pnum] == None):
					return 0
				else:
					self.updateOutput()
					return 1
		return 3
	
	def getPlayerNumber(self, user_id):
		for i, val in enumerate(self.players):
			if (val == user_id):
				return i
		return -1
	
	def updateOutput(self):
		i = self.currentInputs
		self.currentOutput = self.roundEquation(abs(i[0]), abs(i[1]))
	
	def getCurrentInputs(self):
		return self.currentInputs
	
	def getRoundIO(self):
		return {'inputs': self.currentInputs, 'output': self.currentOutput}
	
	def requestNextTurn(self, user_id):
		pnum = self.getPlayerNumber(user_id)
		if (pnum >= 0):
			self.nextTurnReq[pnum] = True
			if (self.nextTurnReq[0] and self.nextTurnReq[1]):
				self.newTurn()
				return True
		return False
	
	def newTurn(self):
		self.nextTurnReq = [False, False]
		self.currentInputs = [None, None]
		self.currentOutput = None
	
	def evaluateGuesses(self, guesses):
		response = []
		for i, g in enumerate(guesses):
			try:
				if (int(g[1]) == self.roundIO[i][2]):
					response.append(True)
				else:
					response.append(False)
			except:
				response.append(False)
		return response
	
	def requestNextRound(self, user_id):
		pnum = self.getPlayerNumber(user_id)
		if (pnum >= 0):
			self.nextTurnReq[pnum] = True
			if (self.nextTurnReq[0] and self.nextTurnReq[1]):
				return True, self.newRound()
		return False, None
	
	def disconnect(self, user_id):
		pnum = self.getPlayerNumber(user_id)
		if (pnum >= 0):
			self.dced[pnum] = True
			if (self.dced[0] and self.dced[1]):
				return True
		return False
	
	
	
	
