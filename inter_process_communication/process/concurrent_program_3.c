/*
            Display Device
                    |
                    |
                   Port
                    |
                    |
                Keyboard input


Some helpful references

ssize_t read(int fd, void buf[.count], size_t count);

read system call attempts to read up to count bytes from file descriptor fd
into the buffer starting at buf.


Before begining to write the program, check the console you want to output
Execute tty. Output may be either of below
/dev/tty is used for bash terminal
/dev/pts is used for psuedo terminal when you do remote login like ssh

*/

#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include <stdlib.h>



int main() {

    int fd, count;
    char buffer [BUFSIZ];

    fd = open("/dev/pts/1", O_RDWR);
    if (fd == -1)
    {
        fprintf(stderr, "cannot open device type pts\n");
        exit(1);
    }

    if (fork())         /* Parent: copy port to stdout */
    {
        while (1)
        {
            // fd 1 represents stdout or Display Device
            count = read(fd, buffer, BUFSIZ);
            write(1, buffer, count);
        }
    }
    else
    {                   /* Child: copy stdin to port */
        while (1)
        {
            // fd 0 represents stdin or Keyboard
            count = read(0, buffer, BUFSIZ);
            write(0, buffer, count);
        }
    }

    return 0;
}