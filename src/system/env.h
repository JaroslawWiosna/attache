#ifndef ENV_H
#define ENV_H

extern char* homeDirBuffer;

int startsWith(char* prefix, char* text);
void setHomeDir(char** envp);
char* replaceTildeWithHomeDir(char* buffer);

#endif // ENV_H