/* ---------------------------------------------- 	*
 *	File: json_utils.h
 *	------------------
 *	Common utilities for working with json
 *
 *
 *	----------------------------------------------	*/
#include "cpp_json/json.h"
#include "parameters.h"

/* UTIL: put_in_json
 * -----------------
 * puts given key/value pair into given json object;
 * puts in FLT_MIN (cfloat) if the value is NaN
 */
void put_in_json (json::object &object, const char *key, float value);

