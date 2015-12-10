#ifndef _JS_TIMER_H_
#define _JS_TIMER_H_

#include "libev/ev.h"
#include "JsObject.h"

class JsTimer : public JsObject 
{
	struct ev_timer timer;
public:
	JsTimer() : JsObject("Timer") {
		callback = NULL;
	}
	
	~JsTimer();
	
	bool is_repeat;
	jerry_api_object_t* callback;
	
	void StartTimer(double after, double repeat, jerry_api_object_t* function);
	void OnTimer(int revents);
	
	static void TimerCallback(struct ev_loop *loop, struct ev_timer *w, int revents);
	
	static bool METHOD(Once);
	static bool METHOD(Repeat);
	static void Register();
};
#endif