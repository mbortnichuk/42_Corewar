/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mb_mainread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbortnic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 18:16:56 by mbortnic          #+#    #+#             */
/*   Updated: 2018/05/07 18:16:57 by mbortnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		mb_readfile(t_file *f)
{
	size_t	i;
	char	*line;

	i = 0;
	line = NULL;
	while ((f->ret_res = get_next_line(f->fds, &line)) > 0 || *line)
	{
		if (line && (!(*line) || mb_only_whtspace(line)))
		{
			free(line);
			continue ;
		}
		// if (mb_addline(f, line, &i, mb_haslabel(line)))  two function to be written in the future 
		// 	return (EXIT_FAILURE);
		free(line);
		++i;
	}
	if (f->ret_res == -1)
		RET_ERR("gnl went wrong.\n", EXIT_FAILURE);
	free(line);
	f->line_nbr = i;
	if (i == 0)
		RET_ERR("This file does not contain any instructions.\n", EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int		mb_addline(t_file *f, char *line, size_t *i, int haslabel)
{
	size_t	length;

	length = ft_strlen(line);
	if (haslabel)
	{
		line[haslabel + 1] = 0;
		if (mb_initline(f, line, *i, LABEL) == EXIT_FAILURE)
			RET_ERR("mb_initline went wrong.\n", EXIT_FAILURE);
		line[haslabel + 1] = ' ';
		(*i)++;
		if ((int)length != haslabel + 1 && mb_only_whtspace(&(line[haslabel + 2])))
			mb_initline(f, line + haslabel + 2, *i, 0);
	}
	else
	{
		if (mb_initline(f, line, *i, UNKNWN) == EXIT_FAILURE)
			RET_ERR("mb_initline went wrong.\n", EXIT_FAILURE);
	}
	return (EXIT_FAILURE);
}
