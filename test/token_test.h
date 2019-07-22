#include "../src/tokenizer/token.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// TODO: make compare function return meaningful value
// In fact this is just to test snitch tool
void compare(char * a, char * b) {
    if (0 == strcmp(a, b)) {
        printf("[ OK ]\n"); 
    } else {
        printf("[ ERROR ] \t '%s', '%s'\n", a, b); 
    }
}

int token_test_01() {
    const char * text = "foo bar";

    struct Token *token = next_token(text);
    compare(token->value, "foo");
    compare(token->the_rest_of_text, "bar");

    struct Token *token02 = next_token(token->the_rest_of_text);
    compare(token02->value, "bar");
    compare(token02->the_rest_of_text, "");

    free(token02->value);
    free(token02->the_rest_of_text);
    free(token02);
    free(token->value);
    free(token->the_rest_of_text);
    free(token);

    return 0;
}

int token_test_02() {
    const char * text = "foo bar baz";

    struct Token *token = next_token(text);
    compare(token->value, "foo");
    compare(token->the_rest_of_text, "bar baz");

    struct Token *token02 = next_token(token->the_rest_of_text);
    compare(token02->value, "bar");
    compare(token02->the_rest_of_text, "baz");

    free(token02->value);
    free(token02->the_rest_of_text);
    free(token02);
    free(token->value);
    free(token->the_rest_of_text);
    free(token);

    return 0;
}

int token_test_03() {
    const char * text = "This is test string. We want to split on spaces";

    struct Token *token = next_token(text);
    compare(token->value, "This");
    compare(token->the_rest_of_text, "is test string. We want to split on spaces");

    struct Token *token02 = next_token(token->the_rest_of_text);
    compare(token02->value, "is");
    compare(token02->the_rest_of_text, "test string. We want to split on spaces");

    free(token02->value);
    free(token02->the_rest_of_text);
    free(token02);
    free(token->value);
    free(token->the_rest_of_text);
    free(token);

    return 0;
}

