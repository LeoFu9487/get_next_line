/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   get_next_line.c									:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: yfu <marvin@42.fr>						 +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2021/01/08 10:23:59 by yfu			   #+#	#+#			 */
/*   Updated: 2021/01/08 15:24:37 by yfu			  ###   ########lyon.fr   */
/*																			*/
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	ft_fill(char **line, t_lst *temp)
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
		return (ft_str_add(temp, buff + 1, res - 1));
	}
	while (idx[0] < res && buff[idx[0]] != '\n')
		idx[0]++;
	if (ft_str_add(temp, buff, idx[0]) == -1)
		return (-1);
	if (res != BUFFER_SIZE || idx[0] < res)
	{
		if (!(line[0] =
		(char*)malloc((temp->len - temp->idx + 1) * sizeof(char))))
			return (-1);
		ft_fill(line, temp);
		if (res == idx[0])
			return (2);
		return (ft_str_add(temp, ft_substr(buff, idx[0] + 1, res - idx[0] - 1), res - idx[0] - 1));
	}
	return (0);
}

int	 ft_check(t_lst *temp, char **line, t_lst *save)
{
	int ct[3];

	if (temp->len > temp->idx && temp->str->s[temp->idx] == '\n')
	{
		(temp->idx)++;
		*line = ft_substr("", 0, 0);
		return (1);
	}
	ct[0] = -1;
	ct[1] = 0;
	while (++ct[0] + (temp->idx) < (temp->len))
		if (temp->str->s[ct[0] + temp->idx] == '\n')
			break ;
	if (ct[0] == 0)
		return (ft_clean_lst(temp));
	if (ct[0] + temp->idx < temp->len)
	{
		line[0] = ft_substr(temp->str->s, temp->idx, ct[0]);
		(temp->idx) += ct[0] + 1;
		if (temp->len == temp->idx)
			ft_del_lst(temp, &save, (int*)ct);
		return (1);
	}
	return (0);
}

void	ft_gnl(int *res, char *buff, char **line, t_lst *temp)
{
	res[0] = read(res[2], buff, BUFFER_SIZE);
	if (res[0] == -1)
	{
		res[1] = -1;
		return ;
	}
	buff[res[0]] = '\0';
	res[1] = ft_end(line, temp, res[0], (char*)buff);
	if (res[1] == 1 || res[1] == 2 || res[0] == 0)
		if (*line == 0)
			*line = ft_substr("", 0, 0);
}

int	 get_next_line(int fd, char **line)
{
	char				buff[BUFFER_SIZE + 1];
	static t_lst		*save;
	t_lst				*temp;
	int					res[3];

	if  (fd < 0 || BUFFER_SIZE < 1 || !line)
		return(-1);
	temp = save;
	while (temp && temp->fd != fd)
		temp = temp->next;
	if (!temp && !(temp = ft_lst_add(&save, fd)))
		return (-1);
	*line = 0;
	if (ft_check(temp, line, save))
		return (1);
	res[2] =  fd;
	while (1)
	{
		ft_gnl((int*)res, buff, line, temp);
		if (res[0] == -1 || res[1] == -1)
			return (ft_del_lst(temp, &save, (int*)res));
		if (res[1] == 1 || res[1] == 2 || res[0] == 0)
			break ;
	}
	return (ft_del_lst(temp, &save, (int*)res));
}
