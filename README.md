# CMPT383 Final Project
### What is the overall goal of the project?

The overall goal of this project is to implement a game inspired by a reality TV show I watched. In this game, two people submit numbers to run through a function, then are given an output. Using this information, the players have to guess what function is being applied to those numbers.
The project was inspired by the "Calculation on the Web" idea on the [projects idea page](https://coursys.sfu.ca/2020su-cmpt-383-d1/pages/ProjectIdeas).

### Which languages did you use, and what parts of the system are implemented in each?

- I used [Python](https://www.python.org/) for the server.
- I used [JavaScript](https://www.javascript.com/) for the client-side web page.
- I used [C](https://en.wikipedia.org/wiki/C_(programming_language)) for the functions.

### What methods did you use to communicate between languages?

- To communicate between the server and client, I used Python with the [Flask framework](https://flask.palletsprojects.com/en/1.1.x/) to serve the client HTML web pages, CSS, and JavaScript scripts through HTTP.
- To communicate between Python and JavaScript, I used the [flask-SocketIO](https://flask-socketio.readthedocs.io/en/latest/) package in Python, and Socket.IO for JavaScript.
- To communicate between Python and C, I used [swig](http://www.swig.org/).

### Exactly what steps should be taken to get the project working, after getting your code?

#### Quick Version

`vagrant up`

`vagrant ssh`

`cd project/project`

`python3 server.py`

`http://localhost:8080/`

#### Long Version

1. Download the repository to your computer.
2. Run `vagrant up` in the repository to create a virtual machine (VM). This will:
	- create the VM defined in `Vagrantfile`,
	- install the dependencies in the `polyglot` cookbook in the `cookbooks` folder,
	- install the dependencies and run swig on the files in the `project` folder, with the commands in `setup.sh`.
3. After the VM has started, run `vagrant ssh` to ssh into the VM.
4. In the VM, type `cd project/project` to change directories into the project folder.
5. In the project folder, type `python3 server.py` to start the server on port 8080.
	- Due to the VM's configuration, this binds to port 8080 of the host machine. Please ensure that port 8080 is available both on the VM and the host machine.
6. Go to [http://localhost:8080/](http://localhost:8080/) in a browser on the host machine to access the game lobby.
	- You may need to replace `localhost` with an IP address like 127.0.0.1.
	- I configured Flask to accept connections from anywhere on the host machine's local network, so you can play on multiple devices.
	- It may not be a good idea to do this in a public LAN, but you'll probably be fine.

### What features should we be looking for when marking your project?

#### 1. Features for players (how to play).

##### Lobby

- Help button to explain what to do on this page.
- Text field to enter the id of the game to join.
	- If the game doesn't exist, a new one will be created.
	- If the game exists, and has one player waiting for another, player will join it.
	- If the game exists, and two players are playing, the player is asked to enter a new game id.

##### Game

- Board to display both players' inputs for the current turn, and the output of the function.
	- Starts turns as "???", fills in as players submit their numbers.
- Text field at the bottom of the screen for players to submit their inputs for the current turn to the server.
	- Press enter to submit a number.
	- If a non-number is submitted, the player is alerted.
- Next turn button to allow the game to advance to the next turn.
	- Both players must press it.
- List of previous player inputs/server outputs during the round.
	- Only appears in the second turn of the current round.
- List of server-given inputs, and text fields for the players to enter their guess for the output.
	- Press enter to submit a guess.
	- Turns green if correct.
- Next round button, to advance the game to the next round if neither player can guess all the outputs.
	- Both players must press it.
- Score board on either side of the game area.
	- Left for the host, right for the joining player.
	- Bottom number is the score for the current round, top is overall.

#### 2. Features for developers (how to understand the system).

##### Server

The server is written in Python, with the Flask framework. Flask was chosen due to its minimalist philosophy. This allows the system to only have code written by me, for only features that I need. Python is also a high-level language that abstracts away many details needed when setting up a web app, which I might've had to deal with when working in a lower-level language. 

The server is contained in the file `server.py`. Data and methods for the game instances are in `game.py`. The server file acts as a connection between the clients and their games, as represented in the game file.

##### Client

The client is served HTML by the server, which then fetches the CSS and JavaScript code. JavaScript is used to both update the HTML as the game progresses, and to detect and send the player's interactions with the web page to the server. JavaScript was chosen becaues it is nearly universal in modern web browsers, has the ability to alter the HTML on the page through the DOM Element, and the ability to interface with the server.

The JavaScript code for the lobby is embedded at the bottom of `lobby.html`. The JavaScript code for the game is in the `code.js` file in the `static` folder.

##### Round Functions

Every round there is a function the player has to guess. These are called "round functions". They are written in C so they are faster than an equivalent function written in Python.

Many of the functions are very simple, like the "add" function, so it many not make sense to add the extra work and overhead of switching languages for the C speed boost. However, in future versions of the game, some more complex functions may be added, justifying that decision.

The round functions are written in the `rf.c` file, and their headers are declared (and sorted by difficulty) in the `rf.h` file.

##### Other

There are some other components in this project that are important.
- The `game.html` and `lobby.html` hold the HTML layouts (`lobby.html` also holds its CSS and JS).
- `style-sheet.css` holds the CSS for `game.html`.
- `rf.i` and `rf_setup.py` holds everything needed to setup swig, and connect Python with C. `rf_setup.py` also has instructions.
- `test.py` runs all the  round functions, so you can see what outputs are like for some given inputs.

### Conclusion

This was my first time writing a web app using a framework in Python. I tried using Django at the beginning, but I found that it had many features that I didn't need, so I chose the simpler Flask (I also tried using REST APIs, but sockets provided a needed consistent connection between server and client). The project turned out very well for my first time using Flask, even though it was very challenging to learn it.

Thanks for trying out my creation! I hope you enjoyed it.
