#import depecndencies
import flask
from flask import request, jsonify
from flask_socketio import SocketIO
from flask_socketio import join_room, leave_room
from flask_socketio import send, emit

from game import Game

#import the html files for the website
file1 = open("lobby.html", "r") 
lobbyHTML = file1.read()
file1.close()

file2 = open("game.html", "r")
gameHTML = file2.read()
file2.close()

#set up the games stuff
#key: player's id, value: the id of the game they're in
pid2game = {}
#key: game id, value: game object
game = {}

#configure the flask server
app = flask.Flask(__name__)
app.config["DEBUG"] = True
app.config['SECRET_KEY'] = 'secret!'
socketio = SocketIO(app)

#serve the lobby when a player connects to the home page
@app.route('/', methods=['GET'])
def home():
	return lobbyHTML

#serve the game page when the player tries to get into a game
@app.route('/game/', methods=['GET'])
def login():
	print(request.args.get('id', ''))
	return gameHTML

#helper functions for websockets:
def joinGame(user_id, game_id):
	g = game[game_id]
	pid2game[user_id] = game_id
	g.join(user_id)

#WEBSOCKETS:

@socketio.on('connect', namespace='/game')
def connection():
	#when a player connects to the games page
	print(request.sid)
	
@socketio.on('disconnect', namespace='/game')
def disconnect():
	#when a player disconnects from the games page
	print('Client disconnected')
	user_id = request.sid
	if (user_id in pid2game):
		game_id = pid2game[user_id]
		g = game[game_id]
		done = g.disconnect(user_id)
		emit('player dced', True, room=game_id)
		#remove the pid from the dict
		del pid2game[user_id]
		if (done):
			#remove the game from the game dict
			del game[game_id]
		

@socketio.on('game connection', namespace='/game')
def game_connection(data):
	# when a player joins the game in a given game id.
	user_id = request.sid
	game_id = data['gid']
	
	print("a user is connecting to game", game_id)
	
	#if the game already exists,
	if (game_id in game):
		#let the player join that game,
		g = game[game_id]
		if (g.numPlayers() >= 2):
			#tell him off
			emit('game inprogress', True)
		else:
			#or send new round to everyone in the game:
			join_room(game_id)
			joinGame(user_id, game_id)
			emit('new round', g.newRound(), room=game_id)
	#if the game doesn't exist,
	else:
		#create one, and add the player.
		g = Game()
		game[game_id] = g
		joinGame(user_id, game_id)
		join_room(game_id)
		emit('connected', True)

@socketio.on('turn input', namespace='/game')
def turn_input(data):
	#when a player submits input for the turn.
	print("A user is submitting input:", data)
	user_id = request.sid
	if (user_id in pid2game):
		game_id = pid2game[user_id]
		g = game[game_id]
		case = g.newInput(user_id, data)
		if (case == 0):
			emit('new input', g.getCurrentInputs(), room=game_id)
		elif (case == 1):
			emit('final input', g.getRoundIO(), room=game_id)
		elif (case == 2):
			emit('bad input', data)

@socketio.on('next turn', namespace='/game')
def next_turn(data):
	#when a player wants to go to the next turn.
	print("a user is requesting next turn")
	user_id = request.sid
	if (user_id in pid2game):
		game_id = pid2game[user_id]
		g = game[game_id]
		go = g.requestNextTurn(user_id)
		if (go):
			emit('end turn', True, room=game_id)

@socketio.on('round guess', namespace='/game')
def round_guess(data):
	print("a player is making a guess")
	#when a player submits a guess for the round.
	print(data)
	user_id = request.sid
	if (user_id in pid2game):
		game_id = pid2game[user_id]
		g = game[game_id]
		correct = g.evaluateGuesses(data['outputs'])
		emit('guess results', correct)
		num_cor = correct.count(True)
		emit('guess data', {'player': g.getPlayerNumber(user_id), 'correct': num_cor}, room=game_id)
		if (num_cor == 5):
			emit('new round', g.newRound(), room=game_id)

@socketio.on('next round', namespace='/game')
def round_guess(data):
	#when a player wants the next round.
	print("a user is requesting next round")
	user_id = request.sid
	if (user_id in pid2game):
		game_id = pid2game[user_id]
		g = game[game_id]
		go, nr = g.requestNextRound(user_id)
		if (go):
			emit('new round', nr, room=game_id)

#app.run(host="localhost", port=3000, debug=True)
app.run(host='0.0.0.0', port=8080, debug=True)
