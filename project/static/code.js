
/*
var temp = document.getElementsByTagName("template")[0];
var hehe = document.getElementById("pastTurns");
for (var i = 0; i < 10; i++) {
	var clon = temp.content.cloneNode(true);
	hehe.appendChild(clon);
}
*/
/*

*/

function removeChildren(node) {
	while (node.firstChild) {
		node.removeChild(node.firstChild);
	}
}

function displayInputs(data){
	if (data[0] != null) {
		document.getElementById('input1').innerHTML = data[0]
	}
	if (data[1] != null) {
		document.getElementById('input2').innerHTML = data[1]
	}
}

function newTurn(){
	var temp = document.getElementsByTagName("template")[0];
	var pt = document.getElementById("pastTurns");
	var clon = temp.content.cloneNode(true);
	//move the current IO to the past IO list
	clon.querySelectorAll(".pastInput")[0].innerHTML = document.getElementById("input1").innerHTML
	clon.querySelectorAll(".pastInput")[1].innerHTML = document.getElementById("input2").innerHTML
	clon.querySelectorAll(".pastOutput")[0].innerHTML = document.getElementById("answer").innerHTML
	pt.prepend(clon);
	//clean the current IO
	document.getElementById("input1").innerHTML = "???"
	document.getElementById("input2").innerHTML = "???"
	document.getElementById("answer").innerHTML = "???"
	//reset the turn btn
	turnBtn.style.cursor = 'pointer'
	turnBtn.style.backgroundColor = '#DB504A' //C4
}



//get the game id
const gid = new URLSearchParams(window.location.search).get('id')

console.log('changing page title...')
document.title = "Game " + gid

console.log('connecting to server...')
var socket = io('/game');

var inputForm = document.getElementById("inputForm")
inputForm.addEventListener("submit", sendInput);

var turnBtn = document.getElementById("nextTurnBtn")
turnBtn.addEventListener("click", nextTurn);

var roundBtn = document.getElementById("nextRoundBtn")
roundBtn.addEventListener("click", nextRound);

var p1Total = document.getElementById("player1").querySelectorAll(".totalscore")[0]
var p1Round = document.getElementById("player1").querySelectorAll(".currentscore")[0]
var p2Total = document.getElementById("player2").querySelectorAll(".totalscore")[0]
var p2Round = document.getElementById("player2").querySelectorAll(".currentscore")[0]

socket.on('connect', function() {
	/* this runs when the client connects to a game.
	get the game id from the url, send it to the server. */
	console.log('telling server to join game ' + gid);
	socket.emit('game connection', {gid: gid});
});

socket.on('connected', function(data) {
	document.getElementById('time').innerHTML = 'waiting for player 2...'
});

socket.on('game inprogress', function(data) {
	/* a spectator joined */
	alert("This game is in progress. Please join a different game.")
	console.log(data)
});

socket.on('bad input', function(data) {
	/* when this client sends bad input to the server, this message tells it that.
	Tell the user to send an integer. */
	console.log(data);
	alert("Not an integer: " + data)
});

socket.on('new input', function(data) {
	/* when the server gets a new input, it sends the ID of the player who gave the input,
	along with the input itself.
	Display this in the list of inputs. */
	displayInputs(data)
	console.log(data);
});

socket.on('final input', function(data) {
	/* when the server gets the final input for the turn OR the input time has ended,
	it gives all the inputs given for the turn in ID order, along with the answer.
	Also the players who failed to input anything.
	Display this on the board. */
	displayInputs(data['inputs'])
	document.getElementById('answer').innerHTML = data['output']
	console.log(data);
});

socket.on('end turn', function(data) {
	/* Both players agreed to move to next turn. */
	console.log("Both players decided to move on to the next turn...")
	newTurn()
});

socket.on('guess results', function(data) {
	/* the server's response to the player's guess. correct or incorrect.
	If correct, green out the form. If incorrect, mark it red for a while. */
	console.log('guess results are back')
	console.log(data);
	g = document.getElementById("guesses").querySelectorAll(".guess")
	for (var i = 0; i < 5; i++) {
		if (data[i] == true) {
			g[i].style.backgroundColor = '#A6B07E' //C5
		} else {
			g[i].style.backgroundColor = '#DB504A' //C4
		}
		
	}
});

socket.on('guess data', function(data) {
	/* a player in the game made a correct guess.
	Update that player's profile on the page. */
	console.log(data);
	round = p1Round
	if (data['player'] == 1){
		round = p2Round
	}
	round.innerHTML = data['correct']
});

socket.on('new round', function(data) {
	/* a player correctly guessed all the outputs for the round, or it's a new game.
	the server sends everyone a package of info, including:
	updated scores and the inputs to guess for the next round. */
	console.log('a new round has been started.')
	console.log(data)
	inputs = data['inputs']
	//1. clear the previous round stuff:
	newTurn()
	roundBtn.style.cursor = 'pointer'
	roundBtn.style.backgroundColor = '#DB504A' //C4
	
	var guesses = document.getElementById("guesses");
	removeChildren(guesses)
	
	var pastTurns = document.getElementById("pastTurns");
	removeChildren(pastTurns)
	
	document.getElementById("time").innerHTML = ""
	document.getElementById("input1").innerHTML = "???"
	document.getElementById("input2").innerHTML = "???"
	document.getElementById("answer").innerHTML = "???"
	
	//2. add the new round stuff:
	var temp = document.getElementsByTagName("template")[1];
	for (var i = 0; i < 5; i++) {
		var clone = temp.content.cloneNode(true);
		clone.querySelectorAll(".sinput")[0].innerHTML = inputs[i][0]
		clone.querySelectorAll(".sinput")[1].innerHTML = inputs[i][1]
		a = clone.querySelectorAll(".outputForm")[0]
		a.addEventListener("submit", sendGuess);
		guesses.appendChild(clone);
	}
	
	//3. move scores around.
	p1Total.innerHTML = (parseInt(p1Total.innerHTML) + parseInt(p1Round.innerHTML)).toString()
	p1Round.innerHTML = 0
	p2Total.innerHTML = (parseInt(p2Total.innerHTML) + parseInt(p2Round.innerHTML)).toString()
	p2Round.innerHTML = 0
	
});

socket.on('player dced', function(data) {
	alert('The other player disconnected. Please leave the game.')
});

function sendInput() {
	//this function sends the input to the server
	input = inputForm.querySelectorAll("#inputFormField")[0].value;
	socket.emit('turn input', input);
}

function sendGuess() {
	//this function sends the player's output guess to the server:
	console.log("sending guess for all inputs")
	output = []
	fields = document.getElementsByClassName("outputFormField")
	for (var i = 0; i < 5; i++) {
		var guess = fields[i].value;
		output.push([i, guess])
	}
	socket.emit('round guess', {'outputs': output});
}

function nextTurn() {
	//when player want to go to next turn
	console.log("requesting next turn...")
	turnBtn.style.cursor = 'default'
	turnBtn.style.backgroundColor = '#596475' //C0
	socket.emit('next turn', true)
}

function nextRound() {
	console.log("requesting next round...")
	roundBtn.style.cursor = 'default'
	roundBtn.style.backgroundColor = '#596475' //C0
	socket.emit('next round', true)
}

