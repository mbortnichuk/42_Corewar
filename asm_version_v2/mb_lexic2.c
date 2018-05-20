/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mb_lexic2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbortnic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 06:58:33 by mbortnic          #+#    #+#             */
/*   Updated: 2018/05/18 06:58:34 by mbortnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		mb_start_skip_whtspc(int inp, t_symbol *s)
{
	while (s->type == (t_sample){Whtspc} || s->type == (t_sample){Nl})
		*s = mb_lexic(inp);
	return (0);
}

int		mb_lookin_opcode(int inp, int *val, t_symbol *s, int opcode)
{
	t_argum	ar[3];
	int		i;
	int		k;

	i = -1;
	k = -1;
	*s = mb_lexic(inp);
	*val += 1;
	while (++i < g_tab[opcode].numb_of_arg)
	{
		if (i && s->type == (t_sample){Symbol} && *(s->line) == SEPARATOR_CHAR)
			*s = mb_lexic(inp);
		else if (i)
			return (2);
		if ((ar[i] = mb_lookin_arguments(inp, s, opcode)).size == -1)
			return (1);
		if (!(g_tab[opcode].arg[i] & ar[i].type))
			return (3);
	}
	if (g_tab[opcode].codage)
		*val += 1;
	while (++k < i)
		*val += ar[k].size;
	return (0);
}

int		mb_start_opcode_manager(int inp, t_symbol *s, int *val)
{
	if (mb_lookin_opcode(inp, val, s, mb_get_key_word(s->line)))
		return (1);
	while (s->type != (t_sample){Nl})
	{
		if (s->type != (t_sample){Whtspc})
			return (2);
		*s = mb_lexic(inp);
	}
	return (0);
}

t_symbol	mb_lexic(int file_descr)
{
	static t_chr	c = {-1, -1, -1};
	t_symbol		s;

	c = (c.c != -1) ? c : mb_checker(file_descr);
	s = (t_symbol){{0}, (c.c != -1) ? -1 : 0, 0, 0};
	s.column = c.column;
	s.str = c.str;
	ft_memset(s.line, 0, COMMENT_LENGTH + 1);
	if (ft_strchr(WHTSPACE, c.c) || c.c == COMMENT_CHAR || c.c == COMMENT_CHR2)
		c = mb_whtsp_manager(&s, c, file_descr);
	else if (ft_strchr(SYMBOL_CHR, c.c))
	{
		s = mb_symbol_update(s, (t_sample){Symbol}, c.c);
		c = mb_checker(file_descr);
	}
	else if (c.c == '"')
		c = mb_line_manager(&s, c, file_descr);
	else if (ft_strchr(LABEL_CHARS, c.c))
		c = mb_label_manager(&s, c, file_descr);
	return (s);
}
