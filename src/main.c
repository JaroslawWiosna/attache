#include <stdio.h>
#include "./command/command.h"
#include "./system/env.h"

int main(int argc, char* argv[], char** envp) {
    // while (*envp) {
    //     printf("%s\n", *envp++);
    // }
    char buf[100];
    getHomeDir(buf, envp);
    printf("HOME is %s\n", buf);
    parse_attache_command(argc, argv);

    (void)envp;

    return 42;
}
