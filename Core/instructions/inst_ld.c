/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst_ld.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrybak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 11:27:47 by mrybak            #+#    #+#             */
/*   Updated: 2018/05/05 11:27:49 by mrybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../corewar.h"

void		ld_inst(t_core *core, t_proc *proc, int inst)
{
	int	value;

	if (!(add_cd_check_valid(core, proc, inst)))
		return ;
	value = read_arg(core->map, proc->pc, inst, 1);
	write_to_reg(value, read_arg(core->map, proc->pc, inst, 2), proc);
	proc->carry = value == 0 ? 1 : 0;
	proc->cd = -1;
	proc->prev_pc = proc->pc;
	proc->pc = (proc->pc + inst_size(inst, core->map[proc->pc + 1])) % MEM_SIZE;
}
