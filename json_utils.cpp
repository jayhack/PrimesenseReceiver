#include <cfloat>
#include "json_utils.h"

/* UTIL: put_in_json
 * -----------------
 * puts given key/value pair into given json object;
 * puts in FLT_MIN (cfloat) if the value is NaN
 */
void put_in_json (json::object &object, const char *key, float value) {
	if (isnan(value)) value = JSON_NAN_SUBSTITUTE;
	object.insert(key, value);
}
