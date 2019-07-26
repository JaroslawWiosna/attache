#include "token.h"
#include "../log.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static void dctor_token(Token* token);

Token* prev_token(Token* token) {
    return token->prev;
}

Token* next_token(Token* token) {
    return token->next;
}

Token* create_next_token(Token* token) {
    LOGD("Enter function");
    // printf("Len of %s is %u\n", token->value, (unsigned
    // int)strlen(token->value));
    char* text = malloc(strlen(token->the_rest_of_text) + 1);
    strncpy(text, token->the_rest_of_text, strlen(token->the_rest_of_text) + 1);
    text[strlen(token->the_rest_of_text)] = '\0';

    printf("Len of %s is %u\n", text, (unsigned int)strlen(text));
    if (!text || 0 == strcmp(text, "")) {
        if (text) {
            free(text);
        }
        return NULL;
    }

    Token* result = malloc(sizeof(Token));

    for (unsigned i = 0; i < strlen(text); ++i) {
        if (' ' == *(text + i)) {
            result->value = malloc(i + 1);
            strncpy(result->value, text, i + 1);
            result->value[i] = '\0';

            result->the_rest_of_text = malloc(strlen(text) + 1 - i);
            memcpy(result->the_rest_of_text, &text[i + 1],
                   (strlen(text) + 1 - i - 1));
            result->the_rest_of_text[(strlen(text) - i - 1)] = '\0';

            result->prev = token;

            if (text) {
                free(text);
            }

            result->next = create_next_token(result);
            return result;
        }
    }
    result->value = malloc(strlen(text) + 1);
    // printf("[LOG] text is %s\n", text);
    // printf("[LOG] result->value is %s\n", result->value);
    strncpy(result->value, text, strlen(text) + 1);
    result->value[strlen(text)] = '\0';
    // printf("[LOG] result->value is %s\n", result->value);

    result->the_rest_of_text = NULL;
    result->next = NULL;
    result->prev = token;
    if (text) {
        free(text);
    }
    return result;
}

Token* create_token_list(const char* text) {
    printf("[LOG] create_token_list\n");
    if (!text || 0 == strcmp(text, "")) {
        return NULL;
    }

    Token* result = malloc(sizeof(Token));

    for (unsigned i = 0; i < strlen(text); ++i) {
        if (' ' == *(text + i)) {
            result->value = malloc(i + 1);
            strncpy(result->value, text, i);
            result->value[i] = '\0';

            result->the_rest_of_text = malloc(strlen(text) + 1 - i);
            memcpy(result->the_rest_of_text, &text[i + 1],
                   (strlen(text) + 1 - i));
            result->the_rest_of_text[(strlen(text) - i)] = '\0';
            result->prev = NULL;
            result->next = create_next_token(result);
            printf("[DEBUG] addr of result is %p\n", (void*)result);

            return result;
        }
    }
    result->value = malloc(strlen(text) + 1);
    strncpy(result->value, text, strlen(text) + 1);
    result->value[strlen(text)] = '\0';

    result->the_rest_of_text = malloc(1);
    strncpy(result->the_rest_of_text, "", strlen(""));
    result->the_rest_of_text[0] = '\0';

    printf("value is %s\n", result->value);
    result->next = create_next_token(result);

    return result;
}

void dctor_token_list(Token* token) {
    Token* ptr = NULL;
    while (NULL != token->next) {
        ptr = token->next;
        while (NULL != ptr->next) {
            ptr = next_token(ptr);
        }
        Token* tmp = prev_token(ptr);
        tmp->next = NULL;
        dctor_token(ptr);
        ptr = NULL;
    }

    while (NULL != token->prev) {
        ptr = token->prev;
        while (NULL != ptr->prev) {
            ptr = prev_token(ptr);
        }
        Token* tmp = next_token(ptr);
        tmp->prev = NULL;
        dctor_token(ptr);
        ptr = NULL;
    }
    dctor_token(token);
    return;
}

static void dctor_token(Token* token) {
    if (NULL != token->value) {
        free(token->value);
    }
    if (NULL != token->the_rest_of_text) {
        free(token->the_rest_of_text);
    }
    if (NULL != token) {
        free(token);
    }
    return;
}
