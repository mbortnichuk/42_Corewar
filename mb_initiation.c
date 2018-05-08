/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mb_initiation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbortnic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 16:35:56 by mbortnic          #+#    #+#             */
/*   Updated: 2018/05/08 16:35:57 by mbortnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	mb_initfile(t_file *f)
{
	f->header.magic = COREWAR_EXEC_MAGIC;
	ft_bzero(f->header.prog_name, PROG_NAME_LENGTH + 1);
	f->header.prog_size = 0;
	ft_bzero(f->header.comment, COMMENT_LENGTH + 1);
	f->strs = NULL;
	f->s_name = NULL;
	f->cor_name = NULL;
	f->line_nbr = 0;
	f->hasname = 0;
	f->ret_res = 0;
	f->fds = -1;
	f->fdcor = -1;
	f->opt = 0;
}

int		mb_initline(t_file *f, char *line, size_t i, int linetype)
{
	char	*last_comment;
	t_str	*str;

	if (!(str = (t_str*)malloc(sizeof(t_str))))
		RET_ERR("Memory allocation went wrong.\n", EXIT_FAILURE);
	str->symbols = NULL;
	str->id = i;
	str->code_size = 0;
	if ((last_comment = ft_strchr(line, LAST_COMMENT_CHR)))
		*last_comment = '\0';
	str->line = ft_strtrim(line);
	str->param_nbr = 0;
	str->type = linetype;
	ft_bzero(str->bytec, 14);
	str->codep = -1;
	if (str->line && *(str->line))
		ft_lstaddback(&(f->strs), ft_lstnew((void*)str, sizeof(t_str)));
	free(str);
	return (EXIT_SUCCESS);
}
