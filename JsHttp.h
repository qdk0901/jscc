#ifndef _JS_HTTP_H_
#define _JS_HTTP_H_

#include "libev/ev.h"
#include "http-parser/http_parser.h"
#include "JsObject.h"

#define MAX_URL_LENGTH 128
#define HTTP_BUFFER_SIZE 65535

class JsHttpRequest
{
private:
	char buffer[HTTP_BUFFER_SIZE] = {0};
	int buffer_index = 0;
	
public:
	int sock;
	ev_io watcher;
	jerry_api_object_t* callback;
	void CallBack(int status_code, const char* data);
	void Read(int events);
	int SendRequest(char* host, short port, char* data, jerry_api_object_t* function);
	static int OnBodyCallback(http_parser* parser, const char *at, size_t length);
	static void JsHttpReader(EV_P_ ev_io *w, int events);
	static void ParseUrl(char* url, char* host, int* port, char* path);
};

class JsHttp : public JsObject 
{
public:
	JsHttp() : JsObject("Http") {
	}
	
	static bool METHOD(Get);
	static void Register();
};
#endif