#include "JsObject.h"
#include "jerry.h"
#include "jrt/jrt.h"

JsObject::JsObject(char* this_name) 
{
	jerry_api_value_t val;
	jerry_api_object_t* global_obj = jerry_api_get_global();
	
	bool is_ok = jerry_api_get_object_field_value (global_obj, (jerry_api_char_t*)this_name, &val);
	
	if (is_ok && val.type == JERRY_API_DATA_TYPE_OBJECT) {
		this_obj = val.v_object;
	} else {
		this_obj = jerry_api_create_object();
		
		jerry_api_value_t val;
		val.type = JERRY_API_DATA_TYPE_OBJECT;
		val.v_object = this_obj;
		jerry_api_set_object_field_value (global_obj, (jerry_api_char_t*)this_name, &val);
	}
	
	jerry_api_release_object(global_obj);
}

JsObject::~JsObject()
{
	jerry_api_release_object(this_obj);
}

void JsObject::SetMethod(const char* name, jerry_external_handler_t handler)
{
	jerry_api_object_t* obj_p = jerry_api_create_external_function(handler);
	jerry_api_value_t val;
	val.type = JERRY_API_DATA_TYPE_OBJECT;
	val.v_object = obj_p;
	
	jerry_api_set_object_field_value (this_obj, (jerry_api_char_t*)name, &val);
	jerry_api_release_object (obj_p);
}

void JsObject::SetInt32(const char* name, uint32_t value)
{
	jerry_api_value_t val;
	val.type = JERRY_API_DATA_TYPE_UINT32;
	val.v_uint32 = value;
	
	jerry_api_set_object_field_value (this_obj, (jerry_api_char_t*)name, &val);
}

uint32_t JsObject::GetInt32(jerry_api_object_t* obj, const char* name)
{
	jerry_api_value_t val;
	bool ok = jerry_api_get_object_field_value (obj, (jerry_api_char_t*)name, &val);
	
	if (val.type == JERRY_API_DATA_TYPE_FLOAT32)
		return static_cast<double>(val.v_float32);
	else if (val.type == JERRY_API_DATA_TYPE_FLOAT64)
		return static_cast<double>(val.v_float64);
	else
		return val.v_uint32;	
}

uint32_t JsObject::GetInt32(const char* name)
{
	return JsObject::GetInt32(this_obj, name);
}



uint8_t JsObject::jerry_buffer[JERRY_BUFFER_SIZE];

int JsObject::EvalJsFile(const char* name)
{
	FILE *file = fopen (name, "r");
	
	if (file == NULL) {
		printf("cannot open file %s\n", name);
		return -1;
    }

    size_t n = fread (jerry_buffer, 1, JERRY_BUFFER_SIZE, file);
    if (n < 0) {
		printf("read file %s error\n", name);
    } else {
		jerry_parse (jerry_buffer, JERRY_BUFFER_SIZE);
	}
	
	fclose (file);
	
	return 0;	
}