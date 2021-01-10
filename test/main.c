#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>


int main()
{
    int fd1 = open("test.txt", O_RDWR);
    int fd2 = open("test2.txt", O_RDWR);
    int n1, n2;
    char **ans1 = malloc(1 * sizeof(char*)), **ans2 = malloc(1 * sizeof(char*));
    do{
        n1 = get_next_line(fd1, ans1);
        n2 = get_next_line(fd2, ans2);
        printf("return value ans output of fd1 : %d %s\n", n1, *ans1);
        printf("return value ans output of fd2 : %d %s\n", n2, *ans2);
        free(*ans1);
        free(*ans2);
    }while (n1 || n2);
    close(fd1);
    close(fd2);
}

