/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkravets <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 22:43:05 by vkravets          #+#    #+#             */
/*   Updated: 2018/05/15 22:43:07 by vkravets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../corewar.h"

void	color_player(t_proc *proc, unsigned int *i, t_core *core)
{
	t_champ *champ;

	champ = core->champ;
	while (champ)
	{
		if (champ->fileinfo.id == proc->id)
			break ;
		champ = champ->next;
	}
	wattron(core->vis.big, COLOR_PAIR(champ->fileinfo.colour_nbr));
	while (*i < proc->pc + champ->header.prog_size)
	{
		wprintw(core->vis.big, " %02x", core->map[*i]);
		if (*i % 64 == 63)
			wprintw(core->vis.big, "\n");
		(*i)++;
	}
	wattron(core->vis.big, COLOR_PAIR(14));
}

void	clean_carry(t_core *core)
{
	t_proc *proc;

	proc = core->proc;
	while (proc)
	{
		return_color_carry(proc, core);
		proc = proc->next;
	}
}
