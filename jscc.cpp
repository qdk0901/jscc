#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>


#include "jerry.h"
#include "jrt/jrt.h"
#include "jerry-port.h"

#include "libev/ev.h"
#include "JsObject.h"
#include "JsUart.h"
#include "JsHttp.h"
#include "JsTimer.h"

int jerry_port_logmsg (FILE* stream, const char* format, ...)
{
	va_list args;
	int count;
	va_start (args, format);
	count = vfprintf (stream, format, args);
	va_end (args);
	return count;
}

int jerry_port_errormsg (const char* format, ...)
{
	va_list args;
	int count;
	va_start (args, format);
	count = vfprintf (stderr, format, args);
	va_end (args);
	return count;
}

int jerry_port_putchar (int c)
{
	return putchar (c);
}

int main(int argc, char **argv)
{
	struct ev_loop* loop = ev_default_loop(0);
	
	jerry_init (0);
	
	JsUart::Register();
	JsHttp::Register();
	JsTimer::Register();
	
	JsObject::EvalJsFile("jscc.js");
	
	jerry_run ();
	
	ev_loop(loop, 0);
	
	jerry_cleanup ();
	
	return 0;
}