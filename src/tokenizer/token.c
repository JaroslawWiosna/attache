#include "token.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

Token * prev_token(Token * token) {
    return token->prev;
}

Token * next_token(Token * token) {
    return token->next;
}

Token * create_next_token(Token * token) {
    printf("[LOG] create_next_token\n");
    // printf("Len of %s is %u\n", token->value, (unsigned int)strlen(token->value));
    char * text = malloc(strlen(token->the_rest_of_text) * sizeof(char));
    strncpy(text, token->the_rest_of_text, strlen(token->the_rest_of_text));

    printf("Len of %s is %u\n", text, (unsigned int)strlen(text));
    if (!text || 0 == strcmp(text, "")) {
        if (text) {
            free(text);
        }       
        return NULL;
    }

    Token * result = malloc(sizeof(Token));

    for (int i=0; i<strlen(text); ++i) {
        if (' ' == *(text+i)) {
            result->value = malloc((i+1) * sizeof(char));
            strncpy(result->value, text, i);
            result->value[i] = '\0';

            result->the_rest_of_text = malloc((strlen(text) + 1 - i) * sizeof(char));
            memcpy(result->the_rest_of_text, &text[i+1], (strlen(text) + 1 - i - 1));
            result->the_rest_of_text[(strlen(text) - i - 1)] = '\0';
            
            result->prev = token;

            if (text) {
                free(text);
            }

            result->next = create_next_token(result);
            return result;
        }
    }
    result->value = malloc((strlen(text)) * sizeof(char));
    printf("[LOG] text is %s\n", text);
    printf("[LOG] result->value is %s\n", result->value);
    strncpy(result->value, text, strlen(text));
    printf("[LOG] result->value is %s\n", result->value);

    result->the_rest_of_text = NULL;
    result->next = NULL;
    result->prev = token;
    if (text) {
        free(text);
    } 
    return result;    
}

Token * create_token_list(const char * text) {
    printf("[LOG] create_token_list\n");
    if (!text || 0 == strcmp(text, "")) {
        return NULL;
    }

    Token * result = malloc(sizeof(Token));

    for (int i=0; i<strlen(text); ++i) {
        if (' ' == *(text+i)) {
            result->value = malloc((i+1) * sizeof(char));
            strncpy(result->value, text, i);
            result->value[i] = '\0';

            result->the_rest_of_text = malloc((strlen(text) + 1 - i) * sizeof(char));
            memcpy(result->the_rest_of_text, &text[i+1], (strlen(text) + 1 - i - 1));
            result->the_rest_of_text[(strlen(text) - i - 1)] = '\0';
            result->prev = NULL;
            result->next = create_next_token(result);
            printf("[DEBUG] addr of result is %p\n", result);

            return result;
        }
    }
    result->value = malloc((strlen(text) + 1) * sizeof(char));
    strncpy(result->value, text, strlen(text));

    result->the_rest_of_text = malloc(1 * sizeof(char));
    strncpy(result->value, "", strlen(""));

    printf("value is %s\n", result->value);
    result->next = create_next_token(result);

    return result;
}

void dctor_token_list(Token * token) {
    Token * ptr = NULL;
    while (NULL != token->next) {
        ptr = token->next;
        while (NULL != ptr->next) {
            ptr = next_token(ptr);
        }
        Token * tmp = prev_token(ptr);
        tmp->next=NULL;
        dctor_token(ptr);
        ptr = NULL;
    }

    while (NULL != token->prev) {
        ptr = token->prev;
        while (NULL != ptr->prev) {
            ptr = prev_token(ptr);
        }
        Token * tmp = next_token(ptr);
        tmp->prev=NULL;
        dctor_token(ptr);
        ptr = NULL;
    }
    dctor_token(token);
    return;
}

// TODO(#10): make dctor_token static, so it won't be visible outside of translation unit
//      Only dctor_token_list should be used.
void dctor_token(Token * token) {
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
