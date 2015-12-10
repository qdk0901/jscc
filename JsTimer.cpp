#include "JsTimer.h"

JsTimer::~JsTimer()
{
	if (callback != NULL) {
		jerry_api_release_object(callback);
	}
}

void JsTimer::OnTimer(int revents)
{
	jerry_api_value_t res;
	
	jerry_api_call_function(callback, NULL, &res, NULL, 0);
	
	if (!is_repeat) {
		delete this;
	}
}

void JsTimer::TimerCallback(struct ev_loop *loop, struct ev_timer *w, int revents)
{
	JsTimer* timer = (JsTimer*)w->priv;
	timer->OnTimer(revents);
}

void JsTimer::StartTimer(double after, double repeat, jerry_api_object_t* function)
{
	struct ev_loop* loop = ev_default_loop(0);
	ev_timer_init(&timer, TimerCallback, after, repeat);
	
	if (repeat != 0.0)
		is_repeat = true;
	else
		is_repeat = false;
	
	callback = function;
	timer.priv = this;
	ev_timer_start(loop, &timer);
}

bool JsTimer::METHOD(Once)
{
	if (args_cnt != 2 || !JVAL_IS_NUMBER(&args_p[0]) || !JVAL_IS_OBJECT(&args_p[1])) {
		printf("http_get: invalid arguments\n");
		return true;		
	}
	
	double time = args_p[0].v_float64;
	jerry_api_object_t* function = jerry_api_acquire_object(args_p[1].v_object);
	
	JsTimer* timer = new JsTimer();
	
	timer->StartTimer(time, 0.0, function);
	return true;
}

bool JsTimer::METHOD(Repeat)
{
	if (args_cnt != 2 || !JVAL_IS_NUMBER(&args_p[0]) || !JVAL_IS_OBJECT(&args_p[1])) {
		printf("http_get: invalid arguments\n");
		return true;		
	}

	double time = args_p[0].v_float64;
	jerry_api_object_t* function = jerry_api_acquire_object(args_p[1].v_object);
	
	JsTimer* timer = new JsTimer();
	
	timer->StartTimer(0.0, time, function);
	return true;
}

void JsTimer::Register()
{
	JsTimer timer;
	timer.SetMethod("once", Once);
	timer.SetMethod("repeat", Repeat);
}