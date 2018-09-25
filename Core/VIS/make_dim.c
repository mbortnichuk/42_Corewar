/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_dim.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrybak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 12:44:06 by mrybak            #+#    #+#             */
/*   Updated: 2018/05/31 12:44:11 by mrybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../corewar.h"

void				make_it_dim(unsigned int position, int color, t_core *core)
{
	core->vis.x = (position % 64) * 3;
	core->vis.y = COORD_Y(position);
	wmove(core->vis.big, core->vis.y, core->vis.x);
	wattron(core->vis.big, COLOR_PAIR(color) | A_DIM);
	wprintw(core->vis.big, " %02x", core->map[position]);
	wattroff(core->vis.big, COLOR_PAIR(color) | A_DIM);
	wrefresh(core->vis.big);
}

void				kill_old_dim(t_make_dim **head)
{
	t_make_dim	*list;
	t_make_dim	*parent;
	t_make_dim	*tmp;

	list = *head;
	parent = NULL;
	while (list)
	{
		tmp = list;
		if (list->cd == -1)
		{
			if (parent)
				parent->next = list->next;
			else
				*head = list->next;
			free(list);
		}
		else
			parent = list;
		list = tmp->next;
	}
}

void				replace_field_dim(t_core *core)
{
	int			i;
	t_make_dim	*tmp;

	kill_old_dim(&core->vis.dim);
	tmp = core->vis.dim;
	while (tmp)
	{
		if (tmp->cd == 0)
		{
			i = 4;
			while (i > 0)
			{
				i--;
				make_it_dim((tmp->adr + i) % MEM_SIZE, tmp->color, core);
			}
		}
		else
			tmp->cd--;
		tmp = tmp->next;
	}
}

void				add_dim(t_make_dim **alst, t_make_dim *new)
{
	if (new != NULL || (*alst) != NULL)
	{
		new->next = *alst;
		*alst = new;
	}
}

t_make_dim			*new_dim(unsigned int adr, int color)
{
	t_make_dim *new_dim;

	if (!(new_dim = (t_make_dim*)malloc(sizeof(t_make_dim))))
		err(0);
	new_dim->adr = adr;
	new_dim->color = color;
	new_dim->cd = 10;
	new_dim->next = NULL;
	return (new_dim);
}
