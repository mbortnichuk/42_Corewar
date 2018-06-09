/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_save_header_info.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iosypenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 12:58:17 by iosypenk          #+#    #+#             */
/*   Updated: 2018/05/28 12:58:20 by iosypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void		str_concat(char **buff, char *to_add)
{
	char	*tmp;

	tmp = *buff;
	*buff = ft_strjoin(*buff, to_add);
	ft_strdel(&tmp);
}

int				count_quote(char *line)
{
	int		i;
	int		count;

	count = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\"')
			count++;
		i++;
	}
	return (count);
}

static int		get_shift_size(char *line, int n)
{
	unsigned int	size;

	size = 0;
	if (n > 0)
		size = (ft_strlen(line) - ft_strlen((ft_strchr(line, '"') + 1)));
	return (size);
}

static void		get_bot_info(t_assm *assm, char **line, char **buff, int nb)
{
	int		n;

	(n = count_quote(*line)) > 2 ? error(assm, 17) : 0;
	first_check(assm, *line, nb, n);
	*buff = ft_strdup(*line + get_shift_size(*line, n));
	if (n == 2)
	{
		(*buff)[ft_strlen(*buff) - 1] = '\0';
		return ;
	}
	while (n > 0 && n != 2)
	{
		ft_strdel(line);
		get_next_line(assm->fd_s, line);
		assm->count++;
		check_new_line(assm, *line, nb);
		str_concat(buff, "\n");
		str_concat(buff, *line);
		if (ft_strstr(*line, "\""))
		{
			(*buff)[ft_strlen(*buff) - 1] = '\0';
			return ;
		}
	}
}

void			io_save_header_info(t_assm *assm, char **buff)
{
	while (get_next_line(assm->fd_s, &assm->line) > 0)
	{
		assm->count++;
		if (before_cmd(assm->line) && ft_strchr(assm->line, '"') &&
			ft_strstr(assm->line, NAME_CMD_STRING))
		{
			get_bot_info(assm, &assm->line, buff, 1);
			ft_memcpy(assm->header.prog_name, *buff, ft_strlen(*buff));
			assm->push += 2;
		}
		else if (before_cmd(assm->line) && ft_strchr(assm->line, '"') &&
			ft_strstr(assm->line, COMMENT_CMD_STRING))
		{
			get_bot_info(assm, &assm->line, buff, 2);
			ft_memcpy(assm->header.comment, *buff, ft_strlen(*buff));
			assm->push += 3;
		}
		else if (not_cmd(assm->line))
			error(assm, 17);
		ft_strdel(buff);
		ft_strdel(&assm->line);
		assm->line_nb = assm->count;
		if (assm->push == 5)
			return ;
	}
}
