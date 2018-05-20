/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mb_support_func2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbortnic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 05:54:00 by mbortnic          #+#    #+#             */
/*   Updated: 2018/05/18 05:54:01 by mbortnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		mb_is_reg(char *w)
{
	if (*w != 'r')
		return (0);
	if (!ft_str_isdigit(w + 1))
		return (0);
	if (*(w + 3))
		return (0);
	return (1);
}

int		mb_is_key_word(char *w)
{
	int		i;

	i = 0;
	while (g_tab[i].name)
	{
		if (!(ft_strcmp(g_tab[i].name, w)))
			return (1);
		i++;
	}
	return (0);
}

int		mb_get_key_word(char *w)
{
	int i;

	i = 0;
	while (g_tab.[i].name)
	{
		if (!(ft_strcmp(g_tab[i].name, w)))
			return (i);
		i++;
	}
	return (-1);
}

t_chr	mb_line_manager(t_symbol *s, t_chr c, int file_descr)
{
	s->type = (t_sample){Str};
	c = mb_checker(file_descr);
	while (c.c != '"')
	{
		if (c.c == 0)
			return ((t_chr){0, 0, 0});
		*s = mb_symbol_update(*s, s->type, c.c);
		c = mb_checker(file_descr);
	}
	c = mb_checker(file_descr);
	return (c);
}

t_chr	mb_whtsp_manager(t_symbol *s, t_chr c, int file_descr)
{
	while (ft_strchr(Whtspc, c.c) || c.c == COMMENT_CHAR || c.c == COMMENT_CHR2)
	{
		while (ft_strchr(Whtspc, c.c))
		{
			s->type = (t_sample){Whtspc};
			while (ft_strchr(Whtspc, c.c))
			{
				if (c.c == '\n')
					s->type = (t_sample){Nl};
				c = mb_checker(file_descr);
			}
		}
		while (c.c == COMMENT_CHAR || c.c == COMMENT_CHR2)
		{
			s->type = (t_sample){Comm};
			while (c.c != '\n')
			{
				if (c.c == 0)
					return ((t_chr){0, 0, 0});
				c = mb_checker(file_descr);
			}
		}
	}
	return (c);
}
