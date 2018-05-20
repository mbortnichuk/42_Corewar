/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mb_lexic1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbortnic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 06:42:38 by mbortnic          #+#    #+#             */
/*   Updated: 2018/05/18 06:42:39 by mbortnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_symbol	mb_symbol_update(t_symbol s, t_sample t, char c)
{
	unsigned int	id;

	s.type = t;
	id = ft_strlen(s.line);
	if (id < COMMENT_LENGTH)
		s.line[ft_strlen(s.line)] = c;
	return (s);
}

t_chr	mb_label_manager(t_symbol *s, t_chr c, int file_descr)
{
	*s = mb_symbol_update(*s, (t_sample{Label}, c.c));
	c = mb_checker(file_descr);
	while (ft_strchr(LABEL_CHARS, c.c))
	{
		*s = mb_symbol_update(*s, s.type, c.c);
		c = mb_checker(file_descr);
	}
	if (c.c == LABEL_CHAR)
		;
	else if (ft_is_key_word(s->line))
		s->type = (t_sample){Keyw};
	else if (ft_is_reg(s->line))
		s->type = (t_sample){Reg};
	else if (ft_str_isdigit(s->line))
		s->type = (t_sample){Numb};
	return (c);
}

int		mb_start_manage_lable(int inp, t_symbol *s, int *val)
{
	if (mb_add_label(s->type, *val))
		return (1);
	if ((*s = mb_lexic(inp)).type != (t_sample){Symbol} || \
		*(s->line) != LABEL_CHAR)
		return (2);
	*s = mb_lexic(inp);
	return (0);
}

t_argum	mb_lookin_arguments(int inp, t_symbol *s, int opcode)
{
	t_argum	ar;

	ar = (t_argum){-1, -1, -1};
	while (s->type == (t_sample){WHTPSC})
		*s = mb_lexic(inp);
	if (s->type == (t_sample){Symbol})
	{
		if (*(s->line) == DIRECT_CHAR)
			ar = mb_lookin_direct(inp, s, opcode, ar);
		else
			ar = mb_lookin_indir(inp, s, ar);
	}
	else if (s->type == (t_sample){Numb})
		ar = (t_argum){T_IND, ft_atoi(s->line), IND_SIZE};
	else if (s->type == (t_sample){Reg})
		ar = (t_argum){T_REG, ft_atoi(s_line + 1), 1};
	while ((*s = mb_lexic(inp)).type == (t_sample){WHTPSC})
		;
	return (ar);
}
