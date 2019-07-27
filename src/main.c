#include <stdio.h>
#include <stdlib.h>
#include "./command/command.h"
#include "./system/env.h"

int main(int argc, char* argv[], char** envp) {
    // while (*envp) {
    //     printf("%s\n", *envp++);
    // }
    char buf[] = "~/logfile.log";
    // TODO(#35): Once envp is processed, the next call of getHomeDir would not be the same
    //      Let's work on copy of envp
    setHomeDir(envp);
    printf("HOME is %s\n", homeDirBuffer);

    char * homeDirWithTildeReplaced = replaceTildeWithHomeDir(buf);    
    printf("LOGFILE is %s\n", homeDirWithTildeReplaced);
    free(homeDirWithTildeReplaced);
    
    parse_attache_command(argc, argv);

    (void)envp;

    return 42;
}
