#ifndef COMMAND_H
#define COMMAND_H

void hello_foo();
void hello_bar();

typedef enum {
    NO_SUCH_COMMAND = 0,
    HELLO_FOO,
    HELLO_BAR,
    WHOAMI_COMMAND,
    VERSION_COMMAND,

    COMMAND_HASH_SIZE
} CommandHash;

CommandHash getCommandHash(const char * text);

void parse_attache_command(int c, char *v[]);

#endif // COMMAND_H