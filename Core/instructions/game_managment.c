/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_managment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrybak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 17:35:21 by mrybak            #+#    #+#             */
/*   Updated: 2018/05/18 17:35:25 by mrybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../corewar.h"

int			live_in_period(t_champ *champ)
{
	t_champ		*tmp;
	int			res;

	res = 0;
	tmp = champ;
	while (tmp)
	{
		res += tmp->lives_in_per;
		tmp = tmp->next;
	}
	return (res);
}

void		reset_lives(t_champ *champ, t_proc *proc)
{
	t_champ		*list;
	t_proc		*list2;

	list = champ;
	while (list)
	{
		list->lives_in_per = 0;
		list = list->next;
	}
	list2 = proc;
	while (list2)
	{
		list2->live = 0;
		list2 = list2->next;
	}
}

void		kill_them(t_proc **head, t_core *core)
{
	t_proc	*list;
	t_proc	*parent;
	t_proc	*tmp;

	list = *head;
	parent = NULL;
	while (list)
	{
		tmp = list;
		if (list->live == 0)
		{
			if (parent)
				parent->next = list->next;
			else
				*head = list->next;
			list->prev_pc = list->pc;
			core->vis_flag == 1 ? return_color_carry(list, core) : 0;
			free(list);
		}
		else
			parent = list;
		list = tmp->next;
	}
}

char		*get_winner(t_core *core)
{
	t_champ		*list;
	int			i;
	char		*res;
	int			id;

	list = core->champ;
	i = list->last_live;
	res = list->header.prog_name;
	id = list->fileinfo.id;
	while (list)
	{
		if (list->last_live >= i)
		{
			i = list->last_live;
			res = list->header.prog_name;
			id = list->fileinfo.id;
		}
		list = list->next;
	}
	core->vis_flag == 0 ?
	ft_printf(RED"Contestant %d, \"%s\", has won !\n"RC, id * -1, res) : 0;
	return (res);
}
