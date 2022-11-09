#ifndef JSON_READ_H
#define JSON_READ_H

// quick lib to read values from json.
// won't parse the json, just try to read
// values from it.
// 
// notes
// - no memory is allocated.
// - NULL can be safely used for all parameters.
// - strings MUST be NULL terminated.
// - not meant to be used with primitive arrays, ie, [1,2,3]
//   but instead, objects and array of objects.
// - no validations are done when reading.
//   if a number can't be read, 0 will be stored.
//   if a bool can't be read, 0 will be stored.
//   if a string isn't a string, no bytes will be copied and
//   the first byte will be set to 0 (empty string)

#include <stddef.h> // size_t

#define json_read_str_arr(dest, json, key) \
    json_read_str((dest), (json), (key), sizeof(dest))

// find the start of the value from key.
// - on failure (key wasn't found), NULL is returned.
// - on success, a pointer to the start of the value is returned.
// 
// example:
// json_read_find_value("{ "foo": 1234 }", "foo")
//   -> 12... (pointer to start of the value)
char *json_read_find_value(char *json, char *key);
// find the beginning of an array.
// - on failure (key was not found or is not an array), NULL is returned.
// - on success, a pointer to the start of the array is returned.
char *json_read_find_arr(char *json, char *key);
// check if a cursor is still inside of an array.
// 
// example:
// char *arr = json_read_find_arr("{
//  my_array: [{foo: 42}, {foo: 43}], 
//  foo: 44, ---> should not be found if iterating in my_array
// }", "my_array");
// char *arr_cursor = arr;
// int found = 0;
// while (...) {
//  arr_cursor = json_read_int(0, arr_cursor, "foo");
//  if (!json_read_is_inside_of_arr(arr, arr_cursor))
//      break;
//  found++;
// }
// found = 2 (NOT 3)
int json_read_is_inside_of_arr(char *start_of_array, char *cursor);

// read values from key into dest.
// - on failure, NULL is returned.
// - on success, a pointer past the key will be returned
//   to keep reading from that point.
// 
// example:
// cursor = "{ "foo", 1234, "bar", 32 }";
// cursor = json_read_int(..., cursor, "foo");
// cursor = json_read_int(..., cursor, "bar");
// on the second call, instead of searching from
// the beginning of the json string, we can
// use the cursor, skiping past "foo". this can be 
// useful for arrays.
char *json_read_int(int *dest, char *json, char *key);
char *json_read_dbl(double *dest, char *json, char *key);
char *json_read_bool(int *dest, char *json, char *key);
// read up to n bytes. dest will be NULL terminated.
char *json_read_str(char *dest, char *json, char *key, size_t n);

#endif //JSON_READ_H
