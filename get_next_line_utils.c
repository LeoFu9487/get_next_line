#include "get_next_line.h"
/*
char			*ft_strdup(const char *source)
{
	char	*ans;
	int		len;
	int		i;

	while ()
	if (!(ans = (char*)malloc((len + 1) * sizeof(char))))
		return (NULL);
	i = -1;
	while (++i < len)
		ans[i] = source[i];
	ans[i] = '\0';
	return (ans);
}
*/
char			*ft_substr(char const *s, int start, int len)
{
	char	*ans;
	int     ct;

	ans = (char*)malloc((len + 1) * sizeof(char)); // should I +1?
	ct = -1;
	while (++ct < len)
        ans[ct] = s[start + ct];
    ans[ct] = '\0';
	return (ans);
}

void   *ft_str_add(t_lst *dst, char *s, int len)
{
    t_str   *str;
    t_str   *temp;
    int     idx;

    idx = -1;
    str = (t_str*)malloc(1 * sizeof(t_str));
    str->next = 0;
    str->s = (char*)malloc((len + 1) * sizeof(char));
    while (++idx < len)
        str->s[idx] = s[idx];
    str->s[idx] = '\0';
    temp = dst->str;
//        printf("Check Point : 4\n");

    if (!temp)
    {
        dst->str = str;
        dst->len = len;
        return ;
    }
    while (temp->next)
    {
 //       printf("%p\n",temp);
        temp = temp->next;
    }

//            printf("Check Point : 5\n");

    temp->next = str;
    dst->len += len;
}


t_lst    *ft_lst_add(t_lst **dst, int fd)
{
    t_lst    *temp;

    temp = (t_lst*)malloc(1 * sizeof(t_lst));
    temp->str = 0;
    temp->len = 0;
    temp->fd = fd;
    temp->next = 0;
    if (*dst == 0)
        *dst = temp;
    else
    {
        temp->next = *dst;
        *dst = temp;
    }
    return (temp);
}
