#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#include "JsUart.h"

void JsUart::JsUartReader(EV_P_ ev_io *w, int events)
{
	JsUart* uart = (JsUart*)w->priv;
	uart->Read(events);
}

void JsUart::Read(int events)
{
	int n;
	
	while(1) {
		n = read(fd, buffer + buffer_index, 1);

		if (n > 0) {
			if (buffer[buffer_index] == '\n') {
			
				buffer[buffer_index + 1] = 0;
				CallBack(buffer);
				
				buffer_index = 0;
				continue;
			}
			
			buffer_index++;
			continue;
		}
		
		break;
	}
}

void JsUart::CallBack(char* data)
{
	jerry_api_value_t res;
	jerry_api_value_t val;
	val.type = JERRY_API_DATA_TYPE_STRING;
	val.v_string = jerry_api_create_string((jerry_api_char_t*)data);
	jerry_api_call_function(callback, NULL, &res, &val, 1);
	jerry_api_release_string(val.v_string);		
}

JsUart::JsUart(char* path, jerry_api_object_t* function) : JsObject(jerry_api_create_object())
{
	struct ev_loop* loop = ev_default_loop(0);
	
	callback = function;
	
	is_ok = false;
	
	fd = open(path, O_RDWR | O_NONBLOCK, 0);

	if (fd == -1) {
		printf("open %s error\n", path);
		jerry_api_release_object(callback);
		return;	
	}
	
	ev_io_init(&watcher, JsUartReader, fd, EV_READ);
	
	watcher.priv = this;
	
	ev_io_start(loop, &watcher);
	
	is_ok = true;
}

bool JsUart::METHOD(Write)
{
	char* data;
	int size;
	
	if (args_cnt != 1 || !JVAL_IS_STRING(&args_p[0])) {
		printf("uart_write: invalid arguments\n");
		ret_val_p->type = JERRY_API_DATA_TYPE_UINT32;
		ret_val_p->v_uint32 = 0;	
		return true;
	}
	
	JsUart* uart = (JsUart*)JsObject::GetInt32(this_p->v_object, "_this");
	
	size = -jerry_api_string_to_char_buffer(args_p[0].v_string, NULL, 0);
	data = new char[size];
	
	jerry_api_string_to_char_buffer(args_p[0].v_string, (jerry_api_char_t*)data, size);
	
	size = write(uart->fd, data, size);
	
	ret_val_p->type = JERRY_API_DATA_TYPE_UINT32;
	ret_val_p->v_uint32 = size;
	
	delete data;
	return true;	
}

bool JsUart::METHOD(Close)
{
	JsUart* uart = (JsUart*)JsObject::GetInt32(this_p->v_object, "_this");
	struct ev_loop* loop = ev_default_loop(0);
	jerry_api_release_object(uart->callback);
	
	ev_io_stop(loop, &uart->watcher);
	close(uart->fd);
	
	delete uart;
}

bool JsUart::METHOD(Open)
{
	char path[MAX_PATH] = {0};
	
	ret_val_p->type = JERRY_API_DATA_TYPE_OBJECT;
	ret_val_p->v_object = NULL;
	
	if (args_cnt != 2 || !JVAL_IS_STRING(&args_p[0]) || !JVAL_IS_OBJECT(&args_p[1])) {
		printf("uart_open: invalid arguments\n");
		return true;	
	}
	
	jerry_api_string_to_char_buffer(args_p[0].v_string, (jerry_api_char_t*)path, MAX_PATH);

	jerry_api_object_t* function = jerry_api_acquire_object(args_p[1].v_object);
	
	JsUart* uart = new JsUart(path, function);
	
	if (uart->is_ok) {
		ret_val_p->v_object = (jerry_api_object_t*)uart->this_obj;
		uart->SetInt32("_this", (uint32_t)uart);
		uart->SetMethod("write", Write);
		uart->SetMethod("close", Close);
	}
	
	return true;
}

void JsUart::Register()
{
	JsUart uart;
	uart.SetMethod("open", Open);
}


