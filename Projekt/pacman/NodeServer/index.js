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
		io.emit('sendKey', { keyPressed: parseInt(shareData) });
		myPort.write('1'); // establish connection with arduino example ' No idea if we need this line or what it does
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
  socket.emit('news', { keyPressed: shareData });
  socket.on('my other event', function (data) {
    console.log(data);
  });
});