#include "token.h"
#include <string.h>
#include <stdlib.h>

struct Token * next_token(const char * text) {
    struct Token * result = malloc(sizeof(struct Token));

    for (int i=0; i<strlen(text); ++i) {
        if (' ' == *(text+i)) {
            result->value = malloc((i+1) * sizeof(char));
            strncpy(result->value, text, i);
            result->value[i] = '\0';

            result->the_rest_of_text = malloc((strlen(text) + 1 - i) * sizeof(char));
            memcpy(result->the_rest_of_text, &text[i+1], (strlen(text) + 1 - i - 1));
            result->the_rest_of_text[(strlen(text) - i)] = '\0';
            return result;
        }
    }
    result->value = malloc((strlen(text) + 1) * sizeof(char));
    strncpy(result->value, text, strlen(text));

    result->the_rest_of_text = malloc(1 * sizeof(char));
    strncpy(result->value, "", strlen(""));
    return result;
}
