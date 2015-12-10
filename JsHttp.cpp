#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "JsHttp.h"

void JsHttpRequest::ParseUrl(char* url, char* host, int* port, char* path)
{
	struct http_parser_url u;  
    if (0 == http_parser_parse_url(url, strlen(url), 0, &u)) {
		if (u.field_set & (1 << UF_PORT))  
            *port = u.port;
		else
			*port = 80;
		
		if (u.field_set & (1 << UF_HOST))
            strncpy(host, url + u.field_data[UF_HOST].off, u.field_data[UF_HOST].len);  
		
		if (u.field_set & (1 << UF_PATH))
            strncpy(path, url+u.field_data[UF_PATH].off, u.field_data[UF_PATH].len);
	}	
}

void JsHttpRequest::CallBack(int status_code, const char* data)
{
	jerry_api_value_t res;
	jerry_api_value_t val[2];
	
	val[0].type = JERRY_API_DATA_TYPE_UINT32;
	val[0].v_uint32 = status_code;
	
	val[1].type = JERRY_API_DATA_TYPE_STRING;
	val[1].v_string = jerry_api_create_string((jerry_api_char_t*)data);
	int is_ok = jerry_api_call_function(callback, NULL, &res, val, 2);
	
	jerry_api_release_string(val[1].v_string);	
}

int JsHttpRequest::OnBodyCallback(http_parser* parser, const char *at, size_t length)
{
	JsHttpRequest* req = (JsHttpRequest*)parser->data;
	
	req->CallBack(parser->status_code, at);
}

void JsHttpRequest::JsHttpReader(EV_P_ ev_io *w, int events)
{
	JsHttpRequest* req = (JsHttpRequest*)w->priv;
	req->Read(events);	
}

void JsHttpRequest::Read(int events)
{
	int size;
	
	struct ev_loop* loop = ev_default_loop(0);

	size = read(sock, buffer + buffer_index, HTTP_BUFFER_SIZE - buffer_index);
	
	if (size == 0) {
		http_parser_settings settings;
		memset(&settings, 0, sizeof(settings));
		settings.on_body = OnBodyCallback;
		http_parser* parser = (http_parser*)malloc(sizeof(http_parser));
		http_parser_init(parser, HTTP_RESPONSE);
		parser->data = this;
		size = http_parser_execute(parser, &settings, buffer, buffer_index);
		
		ev_io_stop(loop, &watcher);
		close(sock);
		
		delete this;
	} else if (size > 0) {
		buffer_index += size;
	}	
}

int JsHttpRequest::SendRequest(char* host, short port, char* data, jerry_api_object_t* function)
{
	struct sockaddr_in addr;
	struct hostent* h;
	int len = strlen(data);
	int n = 0, total = 0;
	
	callback = function;
	
	struct ev_loop* loop = ev_default_loop(0);
	
	h = gethostbyname(host);
	
	memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    memcpy(&addr.sin_addr.s_addr, h->h_addr, h->h_length);
	
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0) {
		printf("create socket error\n");
		return -errno;
	}
	
	if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		printf("connect to %s error\n", host);
		return -errno;
	}

	ev_io_init(&watcher, JsHttpReader, sock, EV_READ);
	
	watcher.priv = this;
	ev_io_start(loop, &watcher);
	
	do {
		n = write(sock, data + total, len - total);
		if (n < 0 && errno != EAGAIN)
			break;
		else if (n > 0)
			total += n;
	} while(total < len);
	
	return total;	
}

bool JsHttp::METHOD(Get)
{
	char url[MAX_URL_LENGTH] = {0};
	char host[MAX_URL_LENGTH] = {0};
	char path[MAX_URL_LENGTH] = {0};
	char req[MAX_URL_LENGTH] = {0};
	int port;
	
	if (args_cnt != 2 || !JVAL_IS_STRING(&args_p[0]) || !JVAL_IS_OBJECT(&args_p[1])) {
		printf("http_get: invalid arguments\n");
		return true;		
	}
	
	
	jerry_api_string_to_char_buffer(args_p[0].v_string, (jerry_api_char_t*)url, MAX_URL_LENGTH);
	
	JsHttpRequest::ParseUrl(url, host, &port, path);
	
	sprintf(req, "GET /%s HTTP/1.0\r\n\r\n", path);
	
	JsHttpRequest* jsr = new JsHttpRequest();
	jsr->SendRequest(host, port, req, jerry_api_acquire_object(args_p[1].v_object));

	return true;
}

void JsHttp::Register()
{
	JsHttp http;
	http.SetMethod("get", Get);
}