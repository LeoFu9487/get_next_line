#ifndef BONUS
#include "../mandatory/get_next_line.h"
#endif
#ifdef BONUS
#include "../bonus/get_next_line_bonus.h"
#endif
#include <stdio.h>
#include <fcntl.h>


int main()
{
    int fd1 = open("test.txt", O_RDWR);
    int fd2 = open("test2.txt", O_RDWR);
    int n1, n2;
    do{
		//scanf("%d", &n1);
		char **ans1 = malloc(1 * sizeof(char*));
		n1 = get_next_line(fd1, ans1);
		printf("return value and result of fd1 : %d %s\n", n1, *ans1);
		free(*ans1);
		free(ans1);
		//scanf("%d", &n2);
        char **ans2 = malloc(1 * sizeof(char*));
		n2 = get_next_line(fd2, ans2);
        printf("return value and result of fd2 : %d %s\n", n2, *ans2);
        free(*ans2);
		free(ans2);
    }while (n1 || n2);
    close(fd1);
    close(fd2);
	while (1)
	{
		char **ans = malloc(1 * sizeof(char*));
		int n1 = get_next_line(0, ans);
		printf("return value and result of stdin : %d %s\n", n1, *ans);
		free(*ans);
		free(ans);
	}
}

