#include "get_next_line.h"

char			*ft_substr(char const *s, int start, int len)
{
	char	*ans;
	int	 ct;

	if (!(ans = (char*)malloc((len + 1) * sizeof(char))))
		return (NULL);
	ct = 0;
	while (ct < len && s[ct] != '\0')
	{
		ans[ct] = s[start + ct];
		ct++;
	}
	ans[ct] = '\0';
	return (ans);
}

int   ft_str_add(t_lst *dst, char *s, int len)
{
	t_str   *str;
	t_str   *temp;
	int	 idx;

	if (len < 0)
		return (-1);
	if (!s || !(str = (t_str*)malloc(1 * sizeof(t_str))))
		return (-1);
	idx = -1;
	str->next = 0;
	if (!(str->s = (char*)malloc((len + 1) * sizeof(char))))
		return (-1);
	while (++idx < len)
		str->s[idx] = s[idx];
	str->s[idx] = '\0';
	temp = dst->str;
//		printf("Check Point : 4\n");

	if (!temp)
	{
		dst->str = str;
		dst->len = len;
		return (0);
	}
	while (temp->next)
	{
 //	   printf("%p\n",temp);
		temp = temp->next;
	}

//			printf("Check Point : 5\n");

	temp->next = str;
	dst->len += len;
	return (0);
}


t_lst	*ft_lst_add(t_lst **dst, int fd)
{
	t_lst	*temp;

	if (!(temp = (t_lst*)malloc(1 * sizeof(t_lst))))
		return (NULL);
	temp->str = 0;
	temp->len = 0;
	temp->fd = fd;
	temp->idx = 0;
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

void	ft_clean_lst(t_lst *lst)
{
	t_str   *temp;

	lst->idx = 0;
	lst->len = 0;
	while (lst->str)
	{
		temp = lst->str;
		lst->str = lst->str->next;
		free(temp->s);
	}
	lst->str = 0;
}

int	 ft_del_lst(t_lst *target, t_lst **head)
{
	t_lst   *temp;

	if (target == *head)
	{   if (target->str)
			free(target->str);
		if (target->next)
			*head = target->next;
		else
			*head = 0;
		free(target);
		return (0);
	}
	temp = *head;
	while (temp->next != target)
		temp = temp->next;
	temp->next = target->next;
	if (target->str)
		free(target->str);
	free(target);
	return (0);
}
