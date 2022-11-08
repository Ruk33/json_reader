#include <assert.h>
#include <stdio.h>
#include "json_read.h"

struct user {
    char name[8];
    char pass[32];
};

int main(void)
{
    char *json =
        "{"
        "  \"bar\"    :           42,"
        "  \"baz\": \"do you even \\\"bro\\\"?\","
        "  \"foo\": 42.4423,"
        "  \"some_key\": true,"
        "  \"users\": ["
        "       {\"name\": \"user_a\", \"pass\": \"1234\"},"
        "       {\"name\": \"user_b\", \"pass\": \"4321\"},"
        "       {\"name\": \"user_with_longer_name\", \"pass\": \"4321\"},"
        "  ],"
        "  \"not_an_array\": 32,"
        "}"
        ;
    
    int bar = 0;
    char baz[32] = {0};
    double foo = 0;
    int some_key = 0;
    struct user users[4] = {0};
    
    json_read_int(&bar, json, "bar");
    json_read_str(baz, json, "baz", sizeof(baz));
    json_read_dbl(&foo, json, "foo");
    json_read_bool(&some_key, json, "some_key");
    
    printf("json = '%s'\n", json);
    printf("bar  = '%d'\n", bar);
    printf("baz  = '%s'\n", baz);
    printf("foo  = '%f'\n", foo);
    printf("some_key = '%s'\n", some_key ? "true" : "false");
    
    // read array of users (up to 4)
    char *user_cursor = json_read_find_arr(json, "users");
    size_t found_users = 0;
    for (size_t i = 0; i < 4; i += 1) {
        if (!user_cursor)
            break;
        user_cursor = json_read_str_arr(users[i].name, user_cursor, "name");
        user_cursor = json_read_str_arr(users[i].pass, user_cursor, "pass");
        if (!user_cursor)
            break;
        found_users += 1;
        printf("users[%d].name = '%s'\n", i, users[i].name);
        printf("users[%d].pass = '%s'\n", i, users[i].pass);
    }
    printf("found users: %d.\n", found_users);

    assert(json_read_find_value(json, "not_an_array"));
    assert(json_read_find_arr(json, "not_an_array") == 0);
    
    return 0;
}