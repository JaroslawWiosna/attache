#include <stdio.h>
#include "./command/command.h"

int main(int argc, char* argv[], char** envp) {

    parse_attache_command(argc, argv);

    (void)envp;

    return 42;
}
