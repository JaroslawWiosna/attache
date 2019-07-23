#include "../src/tokenizer/token.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// TODO(#9): make compare function return meaningful value
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

    struct Token *token = create_token_list(text);
    compare(token->value, "foo");
    compare(token->the_rest_of_text, "bar");

    token = next_token(token);
    compare(token->value, "bar");

    if (token->the_rest_of_text == NULL)
        compare("true", "true");
    else
        compare("true", "false");

    dctor_token_list(token);

    return 0;
}

int token_test_02() {
    const char * text = "foo bar baz";

    struct Token *token = create_token_list(text);
    compare(token->value, "foo");
    compare(token->the_rest_of_text, "bar baz");

    token = next_token(token);

    compare(token->value, "bar");
    compare(token->the_rest_of_text, "baz");

    dctor_token_list(token);

    return 0;
}

int token_test_03() {
    const char * text = "This is test string. We want to split on spaces";

    struct Token *token = create_token_list(text);
    compare(token->value, "This");
    compare(token->the_rest_of_text, "is test string. We want to split on spaces");

    token = next_token(token);
    compare(token->value, "is");
    compare(token->the_rest_of_text, "test string. We want to split on spaces");

    dctor_token_list(token);

    return 0;
}

