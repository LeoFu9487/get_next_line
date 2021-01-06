#include "get_next_line.h"

int	 ft_end(char **line, t_lst *temp, int res, char* buff)
{
	int	 idx[3];
	t_str   *str;

	if (temp->len == 0 && res == 0)
		return (1);
	idx[0] = -1;
	while (res && *buff == '\n')
	{
		buff++;
		res--;
	}
	while (idx[0] < res && buff[idx[0]] != '\n')
		idx[0]++;
	if (res == 0 && temp->len == 0)
		return (0);
	if (ft_str_add(temp, buff, idx[0]) == -1)
		return (-1);
	if ((temp->len > 0 && res != BUFFER_SIZE)|| idx[0] < res)
	{
		if (!(line[0] = (char*)malloc((temp->len - temp->idx + 1) * sizeof(char))))
			return (-1);
		idx[1] = -1;
		idx[2] = temp->idx;
		str = temp->str;
		while (++idx[1] < temp->len - temp->idx)
		{
			if (!(str->s[idx[2]]))
			{
				idx[2] = 0;
				str = str->next;
			}
			line[0][idx[1]] = str->s[idx[2]++];
		}
		line[0][idx[1]] = '\0';
		ft_clean_lst(temp);
		if (ft_str_add(temp, ft_substr(buff, idx[0], res - idx[0]), res - idx[0]) == -1)
			return (-1);
		return (1);
	}
	return (0);
}

int	 ft_check(t_lst *temp, char **line)
{
	int ct;

	while (temp->len > 0 && temp->str->s[temp->idx] == '\n')
		(temp->idx)++;
	ct = -1;
	while (++ct + (temp->idx) < (temp->len))
	{
		if (temp->str->s[ct + temp->idx] == '\n')
			break ;
	}
	if (ct == 0)
	{
		ft_clean_lst(temp); // need to free
		return (0);
	}
	if (ct + temp->idx < temp->len) // otherwise we just leave the buffer
	{
		line[0] = ft_substr(temp->str->s, temp->idx, ct);
		while ((temp->idx) < (temp->len) && temp->str->s[temp->idx] == '\n')
			(temp->idx)++;
		if (temp->len == temp->idx)
			ft_clean_lst(temp);
		return (1);
	}
	return (0);
}

int	 get_next_line(int fd, char **line)
{
	char				buff[BUFFER_SIZE + 1];
	static t_lst		*save;
	t_lst				*temp;
	int					res[2];

	if  (fd < 0 || BUFFER_SIZE < 1 || !line)
		return(-1);
	temp = save;
	while (temp)
	{
		if (temp->fd == fd)
			break ;
		temp = temp->next;
	}
	if (!temp && !(temp = ft_lst_add(&save, fd)))
		return (-1);

	if (ft_check(temp, line))
		return (1);
	*line = 0;
	while (1)
	{
		res[0] = read(fd, buff, BUFFER_SIZE);
		if (res[0] == -1)
			return (-1);
		buff[res[0]] = '\0';
		res[1] = ft_end(line, temp, res[0], (char*)buff);
		if (res[1] == -1)
			return (-1);
		if (res[1] == 1)
			break ;
	}
	return (*line != 0 ? 1 : ft_del_lst(temp, &save));
}
/*
Do I need to put static for the functions?
*/
/*
Make every space become tab
*/
/*
When Do i need to return 0?
*/
/*
Check if the buffer size is correct
*/
/*
norm
*/
/*
How can I free save ?
(check)
*/
/*
Do I need ifndef?
*/
