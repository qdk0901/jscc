#ifndef _JS_UART_H_
#define _JS_UART_H_

#include "libev/ev.h"
#include "JsObject.h"

#define UART_BUFFER_SIZE 512

class JsUart : public JsObject 
{
private:
	char buffer[UART_BUFFER_SIZE] = {0};
	int buffer_index = 0;
	
public:
	JsUart() : JsObject("Uart") {
	}
	JsUart(char* path, jerry_api_object_t* function);
	
	int fd;
	bool is_ok;
	ev_io watcher;
	jerry_api_object_t* callback;
	
	void CallBack(char* data);
	void Read(int events);

	static void JsUartReader(EV_P_ ev_io *w, int events);
	static bool METHOD(Open);
	static bool METHOD(Write);
	static bool METHOD(Close);
	static void Register();
};
#endif