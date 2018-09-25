/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst_live.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrybak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 20:18:01 by mrybak            #+#    #+#             */
/*   Updated: 2018/05/01 20:18:03 by mrybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../corewar.h"

void		give_live_champ(t_core *core, int pos)
{
	t_champ	*tmp_champ;
	int		value;

	value = four_byte(core->map, pc_pos(pos + 1));
	tmp_champ = core->champ;
	while (tmp_champ)
	{
		if (tmp_champ->fileinfo.id == value)
		{
			tmp_champ->last_live = g_total_cycles;
			tmp_champ->lives_in_per++;
		}
		tmp_champ = tmp_champ->next;
	}
}

void		live_inst(t_core *core, t_proc *proc, int inst)
{
	if (proc->cd < 0)
		proc->cd = g_tab[inst].cycles - 1;
	else
	{
		proc->live = 1;
		give_live_champ(core, proc->pc);
		proc->prev_pc = proc->pc;
		proc->pc = pc_pos(proc->pc + 5);
		proc->cd = -1;
	}
}
