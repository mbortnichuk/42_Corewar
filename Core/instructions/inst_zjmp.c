/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst_zjmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrybak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 15:58:11 by mrybak            #+#    #+#             */
/*   Updated: 2018/05/11 15:58:13 by mrybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../corewar.h"

void		zjmp_inst(t_core *core, t_proc *proc, int inst)
{
	if (proc->cd < 0)
		proc->cd = g_tab[inst].cycles - 1;
	else
	{
		if (proc->carry == 0)
		{
			proc->prev_pc = proc->pc;
			proc->pc = (proc->pc + 3) % MEM_SIZE;
			return ;
		}
		proc->prev_pc = proc->pc;
		proc->pc = pc_pos(proc->pc + two_byte(core->map, pc_pos(proc->pc + 1))
									% IDX_MOD);
	}
}
