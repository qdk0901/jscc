print('start jscc');

/*
Http.get('http://www.baidu.com', function(err, data) {
	if (err == 200) {
		print(data);
	}
});
*/

/*
Timer.once(1.0, function() {
	print('once timer handler called');
});
*/
	
Timer.repeat(1.0, function() {
	print('repeat timer handler called');
});


/*
var uart = Uart.open('/dev/ttyS2', function(data) {
	print(data);
});

uart.write('ls\r\n');
*/
//uart.close();