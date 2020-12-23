#include "get_next_line.h"

int     ft_strlen(char *s)
{
    int len;

    if (!s)
        return (-1);
    len = 0;
    while (s[len] && s[len] != '\n')
        len++;
    return (len);
}

#include <stdio.h>
int main()
{
    char s[] = "1230";
    printf("%d\n",ft_strlen(s));
}
