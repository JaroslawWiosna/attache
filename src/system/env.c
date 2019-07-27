#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "env.h"
#include "../log.h"

char* homeDirBuffer;

// 1 - true
// 0 - false
int startsWith(char* prefix, char* text) {
    unsigned prefix_length = strlen(prefix);
    unsigned text_length = strlen(text);
    return (text_length < prefix_length) ? 0 : (0 == strncmp(prefix, text, prefix_length));
}

void setHomeDir(char** envp) {
    while (*envp) {
        if (startsWith("HOME=", *envp)) {
            // TODO(#36): Replace magic number with length of prefix
            char *tmp = *envp + 5;
            int tmp_len = strlen(tmp);
            homeDirBuffer = malloc(tmp_len + 1);
            strncpy(homeDirBuffer, tmp, tmp_len);
            homeDirBuffer[tmp_len] = '\0'; 
            return;
        }
        char* tmp = *envp++;
        (void) tmp;
    }
}

char* replaceTildeWithHomeDir(char* buffer) {
    char* text = NULL;

    char* ptr_to_tilde = strchr(buffer, '~');

    // The first and last tilde should be the same char.
    assert(strchr(buffer, '~') == strrchr(buffer, '~'));

    if (NULL == ptr_to_tilde) {
        text = malloc(strlen(buffer) + 1);
        strncpy(text, buffer, strlen(buffer) + 1);
        text[strlen(buffer) + 1] = '\0';
        return text;
    } else {
        int text_len = strlen(buffer) - 1 + strlen(homeDirBuffer);
        SLOGD("strlen(homeDirBuffer) = %u", (unsigned)strlen(homeDirBuffer));
        SLOGD("text_len = %2.d", text_len);
        text = malloc(text_len + 1);
        for (int i = 0, j = 0; j < text_len + 1; ++i, ++j) {
            SLOGD("i=%2.d, j=%2.d text=%s",i,j,text);
            if ((buffer + i) == ptr_to_tilde) {                
                for (unsigned k = 0; k < strlen(homeDirBuffer); ++k, ++j) {
                    // *(text + j) = *(buffer + k);
                    text[j] = homeDirBuffer[k];
                    SLOGD("i=%2.d, j=%2.d, homeDirBuffer[k]=%c, text[j] = %c, text=%s",i, j, homeDirBuffer[k], text[j], text);
                }
                --j;
            } else {
                // *(text + j) = *(buffer + i);
                text[j] = buffer[i];
                SLOGD("text[j] = %c", text[j]);
            }
        }
        text[text_len + 1] = '\0';
        return text;
    }

}
