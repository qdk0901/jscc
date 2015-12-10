print('start jscc');


Http.get('http://www.baidu.com', function(err, data) {
	if (err == 200) {
		print(data);
	}
});


/*
var uart = Uart.open('/dev/ttyS2', function(data) {
	print(data);
});

uart.write('ls\r\n');
*/
//uart.close();