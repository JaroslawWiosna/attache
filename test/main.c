#include <stdio.h>
#include "./token_test.h"
#include "./log_test.h"

int main (int argc, char *argv[], char **envp) { 

    (void) argc;
    (void) argv;
    (void) envp;

    token_test_01();
    // token_test_02();
    // token_test_03();
    log_test_01();
    return 0; 
}