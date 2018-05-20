/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mb_header1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbortnic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 09:29:26 by mbortnic          #+#    #+#             */
/*   Updated: 2018/05/18 09:29:27 by mbortnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		mb_parse_head_arg(int inp, t_symbol *s, int i)
{
	*s = mb_lexic(inp);
	while (s->type == (t_sample){Whtspc} || s->type == (t_sample){Nl})
		*s = mb_lexic(inp);
	if (s->type != (t_sample){Symbol} || *(s->line) != '.')
		return (1);
	*s = mb_lexic(inp);
	if (s->type != (t_sample){Label} || ft_strcmp(s->line, (i == 0) ? "name" : "comment"))
		return (2);
	return (0);
}

int		mb_parse_head(int inp, int outp, t_symbol *s, int *val)
{
	unsigned int	i;

	i = COREWAR_EXEC_MAGIC;
	mb_fix_write(outp, &i, sizeof(i));
	while (i < 2)
	{
		if (mb_parse_head_arg(inp, s, i))
			return (1);
		while ((*s = mb_lexic(inp)).type == (t_sample){Whtspc})
			;
		if (s->type != (t_sample){Str})
			return (3);
		if (!i && ft_strlen(s->line) > PROG_NAME_LENGTH)
			return (4);
		else if (i)
			mb_fix_write(outp, val, sizeof(i));
		write(outp, s->line, i == 0 ? PROG_NAME_LENGTH + 4 : COMMENT_LENGTH + 4);
		while ((*s = mb_lexic(inp)).type != (t_sample){Nl})
			if (s->type != (t_sample){Whtspc})
				return (4);
		i++;
	}
	return (0);
}

int		mb_header_skip(int inp, t_symbol *s)
{
	unsigned int	i;

	i = 0;
	while (i < 2)
	{
		*s = mb_lexic(inp);
		while (s->type == (t_sample){Whtspc} || s->type == (t_sample){Nl})
			*s = mb_lexic(inp);
		if (s->type != (t_sample){Symbol} || *(s->line) != '.')
			return (1);
		*s = mb_lexic(inp);
		if (s->type != (t_sample){Label} || ft_strcmp(s->line, \
			(i == 0) ? "name" : "comment"))
			return (2);
		while ((*s = mb_lexic(inp)).type == (t_sample){Whtspc})
			;
		if (s->type != (t_sample){Str})
			return (3);
		while ((*s = mb_lexic(inp)).type != (t_sample){Whtspc})
			if (s->type != (t_sample){Whtspc})
				return (4);
		i++;
	}
	return (0);
}
