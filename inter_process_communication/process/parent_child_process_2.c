/*
    Parent and child execute the same program
*/

#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int main() {

    int i, ret;

    ret = fork();


    if (ret) {
        for (i=0; i<100; i++)
            printf("\t\t\tPARENT %d\n", i);
    }
    else {
        for (i=0; i<100; i++)
            printf("CHILD %d\n", i);
    }
    return 0;
}