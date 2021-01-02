#include "get_next_line.h"

int     ft_end(char **line, t_lst *temp, int res, char* buff)
{
    // if res == 0 || meet the '\n'
    int     idx[3];
    t_str   *str;

    if (temp->len == 0 && res == 0)
        return (1);
    idx[0] = -1;
    while (res && *buff == '\n')
    {
        buff++;
        res--;
    }
    while (++idx[0] < res)
        if (buff[idx[0]] == '\n')
            break ;
    if (idx[0] > 0)
        ft_str_add(temp, buff, idx[0]);
 //           printf("Check Point : 3\n");
 //   printf("res : %d\n",temp->len);
    if (res == 0 || idx[0] < res)
    {
        line[0] = (char*)malloc((temp->len + 1) * sizeof(char));
        idx[1] = -1;
        idx[2] = 0;
        str = temp->str;
        while (++idx[1] < temp->len)
        {
            if (!(str->s[idx[2]]))
            {
                idx[2] = 0; // need to free
                str = str->next;
            }
            line[0][idx[1]] = str->s[idx[2]++];
        }
        line[0][idx[1]] = '\0';
        //ft_free(temp);
        temp->str->s = ft_substr(buff, idx[0], res - idx[0]);
        temp->len = res - idx[0];
        return (1);
    }
    return (0);
}

int     ft_check(t_lst *temp, char **line)
{
    int ct;

    while (temp->len > 0 && *(temp->str->s) == '\n')
    {
        (temp->len)--;
        (temp->str->s)++;
    }
    ct = -1;
    while (++ct < temp->len)
    {
        if (temp->str->s[ct] == '\n')
            break ;
    }
    if (ct == 0)
    {
        temp->str = 0; // need to free
        return (0);
    }
    if (ct < temp->len) // otherwise we just leave the buffer
    {
        line[0] = ft_substr(temp->str->s, 0, ct);
        //ft_free(temp);

        (temp->str->s) += ct;
        (temp->len) -= ct;

        while (temp->len && *(temp->str->s) == '\n')
        {
            (temp->len)--;
            (temp->str->s)++;
        }
        if (temp->len == 0)
            temp->str->s = 0;
        //printf("%s\n", line[0]);
        return (1);
    }
    return (0);
}

int     get_next_line(int fd, char **line)
{
    char                buff[BUFFER_SIZE + 1];
    static  t_lst       *save;
    t_lst               *temp;
    int                 res;

    if  (fd < 0 || BUFFER_SIZE < 1 || !line)
        return(-1);
    temp = save;
    while (temp)
    {
        if (temp->fd == fd)
            break ;
        temp = temp->next;
    }
    if (!temp)
    {
        temp = ft_lst_add(&save, fd);
    }

    if (ft_check(temp, line))
    {
        return (1);
    }

//    printf("Check Point : 1\n");
    while (1)
    {
        res = read(fd, buff, BUFFER_SIZE);
        //printf("%s\n%d\n",buff,res);
        if (res == -1)
            return (-1);
        buff[res] = '\0';
        //printf("%s\n",buff);
//        printf("Check Point : 2\n");
        if (ft_end(line, temp, res, (char*)buff))
            break ;
    }
    if (res == 0 && temp->len == 0)
        return (0);
    //printf("%d\n", temp->len);
    return (1);
}
/*
need to have a function to free everything
*/

/*
protection for malloc
*/

/*
Do I need to put static for the functions?
*/

/*
think about one buffer, lots of '\n'
*/

/*
Is the moment that return 0 correct?
*/
/*
Deal with a file with only '\n'
*/
/*
Deal with an empty file
*/
