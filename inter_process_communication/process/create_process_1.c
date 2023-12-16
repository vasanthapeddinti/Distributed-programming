#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int main() {
    int ret;

    ret = fork();

    printf("return value is %d\n", ret);

    return 0;
}