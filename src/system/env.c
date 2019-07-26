#include <string.h>
#include <stdio.h>
#include "env.h"

// 1 - true
// 0 - false
int startsWith(char* prefix, char* text) {
    unsigned prefix_length = strlen(prefix);
    unsigned text_length = strlen(text);
    return (text_length < prefix_length) ? 0 : (0 == strncmp(prefix, text, prefix_length));
}

void getHomeDir(char* buffer, char** envp) {
    while (*envp) {
        if (startsWith("HOME=", *envp)) {
            // TODO: Replace magic number with length of prefix
            char *tmp = *envp + 5;
            sprintf(buffer, tmp);
            return;
        }
        char* tmp = *envp++;
        (void) tmp;
    }
}