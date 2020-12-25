#ifndef BUFFER_SIZE
    #define BUFFER_SIZE 1
    #endif
#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>


int main()
{

    int fd1,fd2 = 0;
    char buff[256] = {0};
    size_t ct;
    fd1 = open("test.txt", O_RDWR);
    fd2 = open("test2.txt", O_RDWR);
    char **ans1 = (char**)malloc(1 * sizeof(char*));
    char **ans2 = (char**)malloc(1 * sizeof(char*));
    while (get_next_line(fd1, ans1) && get_next_line(fd2, ans2))
    {
        printf("%s\n",ans1[0]);
        printf("%s\n", ans2[0]);
    }
//    printf("%s\n",ans[0]);
    close(fd1);
    close(fd2);
}

