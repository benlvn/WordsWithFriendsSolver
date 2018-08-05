const spaces = document.querySelectorAll('.space');
const key_tiles = document.querySelectorAll('.key-tile'); 
const rack_space = document.querySelectorAll('.rack-space')

game_board = [
	['', '', '', '', '', '', '', '', '', '', '', '', '', '', ''],
	['', '', '', '', '', '', '', '', '', '', '', '', '', '', ''],
	['', '', '', '', '', '', '', '', '', '', '', '', '', '', ''],
	['', '', '', '', '', '', '', '', '', '', '', '', '', '', ''],
	['', '', '', '', '', '', '', '', '', '', '', '', '', '', ''],
	['', '', '', '', '', '', '', '', '', '', '', '', '', '', ''],
	['', '', '', '', '', '', '', '', '', '', '', '', '', '', ''],
	['', '', '', '', '', '', '', '', '', '', '', '', '', '', ''],
	['', '', '', '', '', '', '', '', '', '', '', '', '', '', ''],
	['', '', '', '', '', '', '', '', '', '', '', '', '', '', ''],
	['', '', '', '', '', '', '', '', '', '', '', '', '', '', ''],
	['', '', '', '', '', '', '', '', '', '', '', '', '', '', ''],
	['', '', '', '', '', '', '', '', '', '', '', '', '', '', ''],
	['', '', '', '', '', '', '', '', '', '', '', '', '', '', ''],
	['', '', '', '', '', '', '', '', '', '', '', '', '', '', '']
]

rack = ['', '', '', '', '', '', '']

for(var i = 0; i < 15; ++i){
	for(var j = 0; j < 15; ++j){
		space = spaces[i*15 + j]
		space.free = true;
		space.addEventListener('dragover', dragOver)
		space.addEventListener('drop', dragDrop);
		space.addEventListener('dragenter', dragEnter);
		space.addEventListener('dragleave', dragLeave);
		space.addEventListener('dragstart', spaceDragStart);
		space.coord = {}
		space.coord.x = i
		space.coord.y = j
	}
}

for(var i = 0; i < rack_space.length; ++i){
	space = rack_space[i]
	space.free = true;
	space.addEventListener('dragover', dragOver)
	space.addEventListener('drop', dragDrop);
	space.addEventListener('dragenter', dragEnter);
	space.addEventListener('dragleave', dragLeave);
	space.addEventListener('dragstart', spaceDragStart);
	space.hasind = true;
	space.ind = i
}

// for(const space of spaces){
// 	space.free = true;
// 	space.addEventListener('dragover', dragOver)
// 	space.addEventListener('drop', dragDrop);
// 	space.addEventListener('dragenter', dragEnter);
// 	space.addEventListener('dragleave', dragLeave);
// 	space.addEventListener('dragstart', spaceDragStart);
// 	space.coord.x = 
// 	// colors = ["green", "blue", "orange", "purple", "red"]
// 	// space.style.backgroundColor = colors[Math.floor(Math.random()*colors.length)]
// 	// space.style.opacity = 0.8
// }

for(const key of key_tiles){
	key.addEventListener('dragstart', dragStart);
	key.addEventListener('dragend', dragEnd);
	image_name = 'url("static/solver/tiles/' + key.id + '.png")';
	key.style.backgroundImage = image_name;
}

var dragging_letter = ""

function dragStart(){
	dragging_letter = this.id
}

function dragEnd(){
	dragging_letter = ""
}

function dragOver(e){
	e.preventDefault();
}

var dragging_div;

function dragDrop(e) {
	e.preventDefault();
	if(this.free){
		// this.id = "A";
		// this.className = "key-tile"
		// this.style.backgroundColor = "green"
		image_name = 'url("static/solver/tiles/' + dragging_letter + '.png")';
		this.style.backgroundImage = image_name;
		this.style.backgroundSize = "40px 40px"
		this.style.backgroundColor = "transparent"
		this.free = false;
		this.draggable = true;
		this.tile = dragging_letter
		if(this.coord){
			game_board[this.coord.x][this.coord.y] = this.tile
		} else if (this.hasind){
			rack[this.ind] = this.tile
		}
		if(dragging_div){
			document.querySelector('body').removeChild(dragging_div);
		}
	}
}

function dragEnter() {
	if(this.free){
		this.style.backgroundColor = 'rgba(46, 204, 113, 0.5)'
	}
}

function dragLeave() {
	this.style.backgroundColor = "transparent"
}

function spaceDragStart(e) {
	dragging_letter = this.tile
	this.style.backgroundImage = "none"
	this.tile = ""
	if(this.coord){
		game_board[this.coord.x][this.coord.y] = this.tile
	} else if (this.hasind){
		rack[this.ind] = this.tile
	}
    var dragIcon = document.createElement("img");
    dragIcon.src = 'static/solver/tiles/' + dragging_letter + '.png';
    dragIcon.style.width = "40px";
    var div = document.createElement('div');
    div.appendChild(dragIcon);
    div.style.position = "absolute"; 
    div.style.top = "0px"; 
    div.style.left= "-40px";
    document.querySelector('body').appendChild(div);
    e.dataTransfer.setDragImage(div, 20, 20);
    dragging_div = div
	this.free = true
}

function solve(){
	json_send = {
		rack: rack,
		board: game_board
	}

	$.getJSON('/solve', json_send, function(data){

		string = data['success']

		// open_chat(data['chat-window'])
		console.log(string)
	})
}