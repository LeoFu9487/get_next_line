#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>


int main()
{

    int fd1,fd2 = 0, fd3 = 0;
    char buff[256] = {0};
    size_t ct;
    fd1 = open("test.txt", O_RDWR);
    fd2 = open("test2.txt", O_RDWR);
    char **ans1 = (char**)malloc(1 * sizeof(char*));
    char **ans2 = (char**)malloc(1 * sizeof(char*));
    char **ans3 = (char**)malloc(1 * sizeof(char*));
    int flag = 1;
    /*if (get_next_line(fd3, ans3))
        printf("%s\n", *ans3);
    else printf("NO\n");*/
    printf("BUFFER_SIZE : %d\n", BUFFER_SIZE);
    while (flag)
    {
        flag = 0;
        int n;
        if (n = get_next_line(fd1, ans1))
        {
            flag = 1;
            printf("gnl return value of fd1 : %d\nfd1 : %s\n",n, *ans1);
        }
        if (n = get_next_line(fd2, ans2))
        {
            flag = 1;
            printf("gnl return value of fd2 : %d\nfd2 : %s\n",n, *ans2);
        }

    }
    close(fd1);
    close(fd2);
}

