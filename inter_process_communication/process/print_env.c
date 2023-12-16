#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[], char *envp[]) {

    printf("Command line arguments are:\n");
    printf("argc is %d\n", argc);

    while(*argv != 0) {
        printf(" argv is %s\n", *argv++);
    }

    while(*envp != 0) {
        printf("envp is %s\n", *envp++);
    }

    return 0;
}