/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 10:23:59 by yfu               #+#    #+#             */
/*   Updated: 2021/01/08 15:24:37 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdio.h>

static void	ft_fill(char **line, t_lst *temp)
{
	int 	idx[2];
	t_str	*str;

	*line = (char*)malloc(((temp->len) - (temp->idx) + 1) * sizeof(char));
	idx[0] = temp->idx;
	idx[1] = 0;
	str = temp->str;
	while (idx[1] < (temp->len) - (temp->idx))
	{
		if (str->s[idx[0]] == '\0')
		{
			str = str->next;
			idx[0] = 0;
		}
		line[0][idx[1]++] = str->s[idx[0]++];
	}
	line[0][idx[1]] = '\0';
	ft_clean_lst(temp);
}

int	 ft_end(char **line, t_lst *temp, int res, char* buff)
{
	int	 idx[3];

	if (res == 0 && temp->len == 0)
		return (1);
	idx[0] = 0;
	if (res && *buff == '\n')
	{
		ft_fill(line, temp);
		ft_str_add(temp, buff + 1, res - 1);
		return (1);
	}
	while (idx[0] < res && buff[idx[0]] != '\n')
		idx[0]++;
	if (ft_str_add(temp, buff, idx[0]) == -1)
		return (-1);
	if (res != BUFFER_SIZE || idx[0] < res)
	{
		if (!(line[0] = (char*)malloc((temp->len - temp->idx + 1) * sizeof(char))))
			return (-1);
		ft_fill(line, temp);
		if (res == idx[0])
			return (2);
		if (ft_str_add(temp, ft_substr(buff, idx[0] + 1, res - idx[0] - 1), res - idx[0] - 1) == -1)
			return (-1);
		return (1);
	}
	return (0);
}

int	 ft_check(t_lst *temp, char **line)
{
	int ct;

	if (temp->len > temp->idx && temp->str->s[temp->idx] == '\n')
	{
		(temp->idx)++;
		*line = ft_substr("", 0, 0);
		return (1);
	}
	ct = -1;
	while (++ct + (temp->idx) < (temp->len))
	{
		if (temp->str->s[ct + temp->idx] == '\n')
			break ;
	}
	if (ct == 0)
	{
		ft_clean_lst(temp);
		return (0);
	}
	if (ct + temp->idx < temp->len)
	{
		line[0] = ft_substr(temp->str->s, temp->idx, ct);
		(temp->idx) += ct + 1;
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
	*line = 0;
	if (ft_check(temp, line))
		return (1);
	while (1)
	{
		res[0] = read(fd, buff, BUFFER_SIZE);
		if (res[0] == -1)
			return (-1);
		buff[res[0]] = '\0';
		//printf("buff : %sx", buff);
		res[1] = ft_end(line, temp, res[0], (char*)buff);
		if (res[1] == 2)
		{
			res[0] = 0;
			break ;
		}
		if (res[1] == -1)
		{
			ft_del_lst(temp, &save);
			return (-1);
		}
		//printf("len : %d\n", temp->len);
		if (res[0] == 0)
		{
			res[1] = 2;
			break ;
		}
		if (res[1] == 1)
			break ;
	}
	if (*line == 0)
	{
		*line = (char*)malloc(1 * sizeof(char));
		**line = '\0';
	}
	/*
	printf("res : %d len : %d\n", res[0], temp->len);
	printf("@%s@\n", temp->str->s);
	*/
	/*printf("len : %d\n", temp->len);
	if (temp->len)
	{
		printf("YES\n");
		printf("%s", temp->str->s);
		printf("E\n");
	}*/
	return (res[1] == 2 ? ft_del_lst(temp, &save) : 1);
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
/*
Remember to solve the free of stdin
*/