/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_parse_champ_code.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iosypenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 12:57:57 by iosypenk          #+#    #+#             */
/*   Updated: 2018/05/28 12:58:00 by iosypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void			split_del(char **tmp)
{
	int		i;

	i = 0;
	while (tmp[i] != 0)
	{
		ft_strdel(&(tmp[i]));
		i++;
	}
	free(tmp);
}

static void			split_line(t_assm *assm, char *line, int s)
{
	int		i;
	char	**tmp;

	s++;
	s == 1 ? tmp = ft_strsplit(line, '\t') : 0;
	s == 2 ? tmp = ft_strsplit(line, ' ') : 0;
	s == 3 ? tmp = ft_strsplit(line, SEPARATOR_CHAR) : 0;
	i = 0;
	while (tmp[i] != 0)
	{
		if (tmp[i][0] != COMMENT_CHAR && tmp[i][0] != ';' && s != 3)
			split_line(assm, tmp[i], s);
		if (tmp[i][0] != COMMENT_CHAR && tmp[i][0] != ';' && s == 3)
			io_create_lab_lst(&assm->line_lst, ft_strdup(tmp[i]));
		i++;
	}
	split_del(tmp);
}

static char			*skip_comment(char *line)
{
	char	*res;
	int		len;

	len = 0;
	while (line[len] && line[len] != '#' && line[len] != ';')
		len++;
	res = ft_strsub(line, 0, len);
	ft_strdel(&line);
	return (res);
}

void				parse_champ_code(t_assm *assm)
{
	char	*line;
	int		i;

	lseek(assm->fd_s, 0, SEEK_SET) < 0 ? error(assm, 16) : 0;
	i = 0;
	while (get_next_line(assm->fd_s, &line) > 0)
	{
		if (i >= assm->line_nb)
		{
			line = skip_comment(line);
			split_line(assm, line, 0);
		}
		ft_strdel(&line);
		i++;
	}
}
