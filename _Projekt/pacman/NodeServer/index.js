var socketio = require('socket.io');
var serialport = require('serialport');
var express = require('express');
var SerialPort = serialport.SerialPort;
var portname = process.argv[2];


var myPort = new SerialPort(portname, {
 baudRate: 9600,
 options: false,
 parser: serialport.parsers.readline("\r\n")
});
myPort.on('open', function(){ console.log('port is open');});
myPort.on('close', function(){ console.log('port is closed'); });
myPort.on('error', function(){ console.log('some error - ?x it'); });
var lastKey = -1, lastSpeed = -1;
var shareData = undefined;
myPort.on('data', function(data) {
	var dataArr = data.split(";");
	var dataKey = dataArr[0];
	if(dataKey != lastKey && data != 0){
		console.log(dataKey);
		io.emit('sendKey', { keyPressed: parseInt(dataKey) });
		 // establish connection with arduino example ' No idea if we need this line or what it does
	}
	var speed = parseInt(dataArr[1]);	
	//console.log(speed + "-" + lastSpeed);
	if(speed != lastSpeed){
		console.log("emitingSpeed")
		io.emit('sendSpeed', { "speed": speed });
		console.log("emited")
	}
	lastKey = dataKey;
	console.log("speed:" + speed + "- last: " + lastSpeed);
	lastSpeed = speed;
});
// server
var app = express();
var server = require('http').Server(app);
var io = require('socket.io')(server);
var fs = require('fs');

server.listen(3001);
app.use(express.static('public'));

io.on('connection', function (socket) {
  socket.on('updatePostion', function (data) { 
  	const bytes = new Buffer(20);
	var index = 0;
	bytes[index++] = getNeoSegment(data.blinky,data.pacman);
	bytes[index++] = getNeoSegment(data.pinky,data.pacman);
	bytes[index++] = getNeoSegment(data.inky,data.pacman);
	bytes[index++] = getNeoSegment(data.clyde,data.pacman);
	bytes[index++] = getDistance(data.blinky,data.pacman);
	bytes[index++] = getDistance(data.pinky,data.pacman);
	bytes[index++] = getDistance(data.inky,data.pacman);
	bytes[index++] = getDistance(data.clyde,data.pacman);
	//console.log(bytes[0]);
	//console.log(bytes[2]);
	//console.log(bytes[4]);
	//console.log(bytes[6])
	for(;index<20;index++){
		bytes[index] = 0;
	}

	myPort.write(bytes);
  });
});

function getNeoSegment(A,B) {
	var cx = A.x; var cy = A.y;
	var ex = B.x; var ey = B.y;
	if(cx<0||cy<0||ex<0||ey<0)
		return 0xff;
	var dy = ey - cy;
	var dx = ex - cx;
	var theta = Math.atan2(dx,dy); // range (-PI, PI]
	theta *= 180 / Math.PI; // rads to degs, range (-180, 180]
	if (theta < 0) theta = 360 + theta; // range [0, 360)
	return Math.floor((360-theta)/30)%12;
}

function getDistance(A,B) {
	var dist = Math.floor(Math.sqrt((A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y)));
	dist /= 2;
	return dist>255?0xff:dist;
}