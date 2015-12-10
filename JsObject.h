#ifndef _JS_OBJECT_H_
#define _JS_OBJECT_H_

#include "jerry.h"
#include "jrt/jrt.h"

#define JVAL_IS_NULL(val_p) \
    ((val_p)->type == JERRY_API_DATA_TYPE_NULL)

#define JVAL_IS_UNDEFINED(val_p) \
    ((val_p)->type == JERRY_API_DATA_TYPE_UNDEFINED)

#define JVAL_IS_STRING(val_p) \
    ((val_p)->type == JERRY_API_DATA_TYPE_STRING)

#define JVAL_IS_OBJECT(val_p) \
    ((val_p)->type == JERRY_API_DATA_TYPE_OBJECT)

#define JVAL_IS_FUNCTION(val_p) \
    (JVAL_IS_OBJECT(val_p) && jerry_api_is_function((val_p)->v_object))

#define JVAL_IS_BOOLEAN(val_p) \
    ((val_p)->type == JERRY_API_DATA_TYPE_BOOLEAN)

#define JVAL_IS_NUMBER(val_p) \
    (((val_p)->type == JERRY_API_DATA_TYPE_FLOAT32) || \
     ((val_p)->type == JERRY_API_DATA_TYPE_FLOAT64) || \
     ((val_p)->type == JERRY_API_DATA_TYPE_UINT32))

#define METHOD(name) name(const jerry_api_object_t * function_obj_p, const jerry_api_value_t * this_p, jerry_api_value_t * ret_val_p, const jerry_api_value_t args_p[], const jerry_api_length_t args_cnt)

#define MAX_PATH 260


#define JERRY_BUFFER_SIZE (1048576)


class JsObject {
private:
	static uint8_t jerry_buffer[JERRY_BUFFER_SIZE];
	
public:
	jerry_api_object_t* this_obj;
	
	JsObject(char* this_name);
	JsObject(jerry_api_object_t* obj) {
		this_obj = obj;
	}
	~JsObject();	
	void SetMethod(const char* name, jerry_external_handler_t handler);
	void SetProperty(const char* name, jerry_api_value_t val);
	void SetInt32(const char* name, uint32_t val);
	uint32_t GetInt32(const char* name);
	
	static int EvalJsFile(const char* name);
	static uint32_t GetInt32(jerry_api_object_t*, const char* name);
};

#endif