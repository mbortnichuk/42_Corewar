/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mb_lable1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbortnic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 06:06:56 by mbortnic          #+#    #+#             */
/*   Updated: 2018/05/18 06:06:58 by mbortnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_lab	*mb_get_lable_use(void)
{
	static t_lab	l = (t_lab){NULL, 0};

	if (l.labels == NULL)
		l.labels = ft_lstnew(NULL, 0);
	return (&l);
}

t_lab	*mb_get_lable(void)
{
	static t_lab	l = (t_lab){NULL, 0};

	if (l.labels == NULL)
		l.labels = ft_lstnew(NULL, 0);
	return (&l);
}

int		mb_add_label(char *lab, int val)
{
	t_list	*labels;
	t_list	*new;

	if (lab)
	{
		if (mb_label_id(lab) != -1)
			return (1);
		new = ft_lstnew(lab, ft_strlen(lab) + 1);
	}
	else
		new = ft_lstnew(NULL, 0);
	new->content_size = val;
	labels = mb_get_lable()->labels;
	ft_lstaddback(&labels, new);
	return (0);
}

int		mb_label(int inp, int *val)
{
	t_symbol	s;

	*val = 0;
	if (mb_header_skip(inp, &s))
		return (mb_lexic_err(s, 1));
	while (s.type != (t_sample){Nothing})
	{
		mb_start_skip_whtspc(inp, &s);
		if (s.type == (t_sample){Label})
		{
			if (mb_start_manage_lable(inp, &s, val))
				return (mb_lexic_err(s, 2));
		}
		else if (s.type == (t_sample){Keyw})
		{
			if (mb_start_opcode_manager(inp, &s, val))
				return (mb_lexic_err(s, 3));
		}
		else if (s.type != (t_sample){Nothing})
			return (mb_lexic_err(s, 4));
	}
	if (mb_start_checklable())
		return (5);
	lseek(inp, 0, SEEK_SET);
	return (0);
}
