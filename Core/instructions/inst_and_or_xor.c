/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst_and_or_xor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrybak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 19:30:37 by mrybak            #+#    #+#             */
/*   Updated: 2018/05/10 19:30:42 by mrybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../corewar.h"

void		and_inst(t_core *core, t_proc *proc, int inst)
{
	unsigned char	codage;
	unsigned int	arg1;
	unsigned int	arg2;

	if (!(add_cd_check_valid(core, proc, inst)))
		return ;
	codage = core->map[(proc->pc + 1) % MEM_SIZE];
	arg1 = what_arg(codage, 1) == 1 ?
			proc->reg[fit_reg(read_arg(core->map, proc->pc, inst, 1))]
				: read_arg(core->map, proc->pc, inst, 1);
	arg2 = what_arg(codage, 2) == 1 ?
			proc->reg[fit_reg(read_arg(core->map, proc->pc, inst, 2))]
				: read_arg(core->map, proc->pc, inst, 2);
	write_to_reg(arg1 & arg2, read_arg(core->map, proc->pc, inst, 3), proc);
	proc->carry = (arg1 & arg2) == 0 ? 1 : 0;
	proc->prev_pc = proc->pc;
	proc->pc = (proc->pc + inst_size(inst, codage)) % MEM_SIZE;
	proc->cd = -1;
}

void		or_inst(t_core *core, t_proc *proc, int inst)
{
	unsigned char	codage;
	unsigned int	arg1;
	unsigned int	arg2;

	if (!(add_cd_check_valid(core, proc, inst)))
		return ;
	codage = core->map[(proc->pc + 1) % MEM_SIZE];
	arg1 = what_arg(codage, 1) == 1 ?
			proc->reg[fit_reg(read_arg(core->map, proc->pc, inst, 1))]
				: read_arg(core->map, proc->pc, inst, 1);
	arg2 = what_arg(codage, 2) == 1 ?
			proc->reg[fit_reg(read_arg(core->map, proc->pc, inst, 2))]
				: read_arg(core->map, proc->pc, inst, 2);
	write_to_reg(arg1 | arg2, read_arg(core->map, proc->pc, inst, 3), proc);
	proc->carry = (arg1 | arg2) == 0 ? 1 : 0;
	proc->prev_pc = proc->pc;
	proc->pc = (proc->pc + inst_size(inst, codage)) % MEM_SIZE;
	proc->cd = -1;
}

void		xor_inst(t_core *core, t_proc *proc, int inst)
{
	unsigned char	codage;
	unsigned int	arg1;
	unsigned int	arg2;

	if (!(add_cd_check_valid(core, proc, inst)))
		return ;
	codage = core->map[(proc->pc + 1) % MEM_SIZE];
	arg1 = what_arg(codage, 1) == 1 ?
			proc->reg[fit_reg(read_arg(core->map, proc->pc, inst, 1))]
				: read_arg(core->map, proc->pc, inst, 1);
	arg2 = what_arg(codage, 2) == 1 ?
			proc->reg[fit_reg(read_arg(core->map, proc->pc, inst, 2))]
				: read_arg(core->map, proc->pc, inst, 2);
	write_to_reg(arg1 ^ arg2, read_arg(core->map, proc->pc, inst, 3), proc);
	proc->carry = (arg1 ^ arg2) == 0 ? 1 : 0;
	proc->prev_pc = proc->pc;
	proc->pc = (proc->pc + inst_size(inst, codage)) % MEM_SIZE;
	proc->cd = -1;
}
