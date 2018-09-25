/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst_add_sub.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrybak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 19:25:04 by mrybak            #+#    #+#             */
/*   Updated: 2018/05/09 19:25:09 by mrybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../corewar.h"

void		add_inst(t_core *core, t_proc *proc, int inst)
{
	unsigned int	value;

	if (!(add_cd_check_valid(core, proc, inst)))
		return ;
	value = proc->reg[fit_reg(read_arg(core->map, proc->pc, inst, 1))]
			+ proc->reg[fit_reg(read_arg(core->map, proc->pc, inst, 2))];
	write_to_reg(value, read_arg(core->map, proc->pc, inst, 3), proc);
	proc->carry = value == 0 ? 1 : 0;
	proc->prev_pc = proc->pc;
	proc->pc = (proc->pc + inst_size(inst, core->map[proc->pc + 1])) % MEM_SIZE;
	proc->cd = -1;
}

void		sub_inst(t_core *core, t_proc *proc, int inst)
{
	unsigned int	value;

	if (!(add_cd_check_valid(core, proc, inst)))
		return ;
	value = proc->reg[fit_reg(read_arg(core->map, proc->pc, inst, 1))]
				- proc->reg[fit_reg(read_arg(core->map, proc->pc, inst, 2))];
	write_to_reg(value, read_arg(core->map, proc->pc, inst, 3), proc);
	proc->prev_pc = proc->pc;
	proc->carry = value == 0 ? 1 : 0;
	proc->pc = (proc->pc + inst_size(inst, core->map[proc->pc + 1])) % MEM_SIZE;
	proc->cd = -1;
}
