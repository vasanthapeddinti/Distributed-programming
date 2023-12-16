#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>

struct text_message {
    long mtype;
    char mtext[100];
};

int main(int argc, char *argv[]){
    int msid, v;
    struct text_message mess;

    if (argc != 4) {
        printf("usage: msgsnd <key> <type> <text>\n");
        //exit(1);
    }

    msid = msgget ((key_t)atoi(argv[1]), IPC_CREAT|0666);
    if (msid == -1) {
        printf("Can't get message queue\n");
        //exit(1);
    }

    mess.mtype = atoi (argv[2]);
    strcpy(mess.mtext, argv[3]);

    v = msgsnd(msid, &mess, strlen(argv[3])+1, 0);
    if (v<0) {
        printf("error writing to queue..");
    }

    return 0;
}
