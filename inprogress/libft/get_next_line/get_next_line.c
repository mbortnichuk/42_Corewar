/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iosypenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 14:20:22 by iosypenk          #+#    #+#             */
/*   Updated: 2017/11/25 14:20:25 by iosypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static	int			where_is_n(char *res)
{
	int	i;

	i = 0;
	if (!res)
		return (-1);
	while (res[i])
	{
		if (res[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

static	int			save_line(char **res, char **line, char **buff)
{
	char	*tmp;
	int		tut_n;

	if (*res == NULL)
		*res = ft_strnew(0);
	tmp = *res;
	*res = ft_strjoin(tmp, *buff);
	ft_strdel(&tmp);
	ft_strclr(*buff);
	if ((tut_n = where_is_n(*res)) > -1)
	{
		*line = ft_strsub(*res, 0, tut_n);
		*res = ft_strcpy(*res, *res + tut_n + 1);
		ft_strdel(buff);
		return (1);
	}
	return (0);
}

static char			**ft_check_fd(const int fd, t_string **head)
{
	t_string	*tmp;

	tmp = *head;
	while (tmp)
	{
		if (tmp->fd == fd)
			return (&(tmp->s));
		tmp = tmp->next;
	}
	tmp = (t_string *)malloc(sizeof(t_string));
	tmp->fd = fd;
	tmp->s = ft_strnew(0);
	tmp->next = (*head);
	(*head) = tmp;
	return (&(tmp->s));
}

int					get_next_line(const int fd, char **line)
{
	static t_string		*head;
	char				**res;
	char				*buff;

	if (fd < 0 || BUFF_SIZE <= 0 || read(fd, "", 0) < 0 ||
		!(buff = ft_strnew(BUFF_SIZE)))
		return (-1);
	res = ft_check_fd(fd, &head);
	while ((read(fd, buff, BUFF_SIZE)) > 0)
		if (save_line(res, line, &buff) == 1)
			return (1);
	if ((where_is_n(*res) > -1) && read(fd, buff, BUFF_SIZE) == 0)
	{
		save_line(res, line, &buff);
		return (1);
	}
	if (*res && ft_strlen(*res) != 0)
	{
		*line = ft_strdup(*res);
		ft_strdel(res);
		ft_strdel(&buff);
		return (1);
	}
	ft_strdel(&buff);
	return (0);
}
