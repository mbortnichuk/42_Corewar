/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mb_lookin1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbortnic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 14:18:01 by mbortnic          #+#    #+#             */
/*   Updated: 2018/05/18 14:18:02 by mbortnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_argum	mb_lookin_direct(int inp, t_symbol *s, int c, t_argum ar)
{
	int		state;

	*s = mb_lexic(inp);
	if (s->type == (t_sample){Symbol})
	{
		if (*(s->line) == '+' || *(s->line) == '-')
		{
			state = (*(s->line) == '+') ? 1 : -1;
			*s = mb_lexic(inp);
			if (s->type == (t_sample){Numb})
				ar = (t_argum){T_DIR, state * ft_atoi(s->line), (g_tab[c].dir_size) ? DIR_SIZE / 2 : DIR_SIZE};
		}
		else if (*(s->line) == LABEL_CHAR)
		{
			*s = mb_lexic(inp);
			ar = (t_argum){T_DIR, 0, OPP(c).dir_size ? DIR_SIZE / 2 : DIR_SIZE};
			ft_lstaddback(&(mb_get_lable_use()->labels), ft_lstnew(s->line, ft_strlen(s->line) + 1));
		}
	}
	else if (s->type == (t_sample){Numb})
		ar = (t_argum){T_DIR, ft_atoi(s->line), (g_tab[c].dir_size) ? DIR_SIZE / 2 : DIR_SIZE};
	return (ar);
}

t_argum	mb_lookin_indir(int inp, t_symbol *s, t_argum ar)
{
	int state;

	if (*(s->line) == '+' || *(s->line) == '-')
	{
		state = (*(s->line) == '+') ? 1 : -1;
		*s = mb_lexic(inp);
		if (s->type == (t_sample){Numb})
			ar = (t_argum){T_DIR, state * ft_atoi(s->line), IND_SIZE};
	}
	else if (*(s->line) == LABEL_CHAR)
	{
		*s = mb_lexic(inp);
		ar = (t_argum){T_IND, 0, IND_SIZE};
		ft_lstaddback(&(mb_get_lable_use()->labels), ft_lstnew(s->line, ft_strlen(s->line) + 1));
	}
	return (ar);
}
