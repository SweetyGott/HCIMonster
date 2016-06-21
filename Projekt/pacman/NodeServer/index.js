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
var lastKey = -1;
var shareData = undefined;
myPort.on('data', function(data) {
	shareData = data;
	if(data != lastKey && data != 0){
		console.log(data);
		io.emit('sendKey', { keyPressed: parseInt(shareData) });
		 // establish connection with arduino example ' No idea if we need this line or what it does
	}
	lastKey = data;
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
	
	//the ange to Blinky
	var angleBlinky = Math.floor(angle(data.blinky,data.pacman)/30)%12;

	bytes[index++] = angleBlinky;
	for(;index<20;index++){
		bytes[index] = 0;
	}

	myPort.write(bytes);
  });
});

function angle(A,B) {
	var cx = A.x; var cy = A.y;
	var ex = B.x; var ey = B.y;
	var dy = ey - cy;
	var dx = ex - cx;
	var theta = Math.atan2(dx,dy); // range (-PI, PI]
	theta *= 180 / Math.PI; // rads to degs, range (-180, 180]
	if (theta < 0) theta = 360 + theta; // range [0, 360)
	return 360-theta;
}