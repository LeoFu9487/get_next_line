#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>

#   ifndef BUFFER_SIZE
#   define BUFFER_SIZE 42
#   endif

typedef struct	s_str
{
	char			*s;
	struct s_str	*next;
}				t_str;

typedef struct  s_lst
{
    t_str              *str;
    int                len;
    int                fd;
    struct  s_lst      *next;
}               t_lst;

int         ft_check(t_lst *temp, char **linew);
int         get_next_line(int fd, char **line);
t_lst       *ft_lst_add(t_lst **dst, int fd);
void        *ft_str_add(t_lst *dst, char *s, int len);
char		*ft_substr(char const *s, int start, int len);

#endif
