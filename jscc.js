print('start jscc');

/*

*/

function timerHandler() {
	Http.get('http://127.0.0.1:8089/?cmd=1234', function(err, data) {
		if (err == 200) {
			print(data);
		} else {
			print(err);
		}
	});
	
	Timer.once(1.0, timerHandler);
}

Timer.once(1.0, timerHandler);

/*
var uart = Uart.open('/dev/ttyS2', function(data) {
	print(data);
});

uart.write('ls\r\n');
*/
//uart.close();