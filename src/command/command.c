#include "command.h"
#include "../log.h"
#include "../whoami/whoami.h"
#include <stdio.h>

void hello_foo() {
    LOGI("foo!");
}

void hello_bar() {
    LOGI("bar!");
}

CommandHash getCommandHash(const char * text) {
    if (0 == strcmp(text, "hello-foo")) {
        return HELLO_FOO;
    } else if (0 == strcmp(text, "hello-bar")) {
        return HELLO_BAR;
    } else if (0 == strcmp(text, "whoami")) {
        return WHOAMI_COMMAND;
    } else if (0 == strcmp(text, "who-am-i")) {
        return WHOAMI_COMMAND;
    } else if (0 == strcmp(text, "version")) {
        return VERSION_COMMAND;
    }

    SLOGE("No such command: '%s'", text);
    return NO_SUCH_COMMAND;
}

void parse_attache_command(int c, char *v[]) {
    LOGI("Enter function");
    if (c < 1) {
        LOGE("No option provided");
    } else {
        SLOGI("attache option is: '%s'", v[1]);
        switch(getCommandHash(v[1])) {
            case HELLO_FOO: {
                LOGI("FOO FOOO FOOOOO!");                
                break;
            }
            case HELLO_BAR: {
                LOGI("BAR!");
                break;
            }
            case WHOAMI_COMMAND: {
                LOGD("WHOAMI_COMMAND recognized");
                whoami(c, v);
                break;
            }
            case VERSION_COMMAND: {
                printf("attache version 0.0.0\n");
                return;
            }
            case NO_SUCH_COMMAND:
            case COMMAND_HASH_SIZE:
            default:
                LOGE("!!");
                break;
        }
    }
}
