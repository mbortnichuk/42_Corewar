/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst_lldi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrybak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/13 15:19:02 by mrybak            #+#    #+#             */
/*   Updated: 2018/05/13 15:19:03 by mrybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../corewar.h"

void		lldi_inst(t_core *core, t_proc *proc, int inst)
{
	unsigned char	codage;
	int				arg1;
	int				arg2;
	unsigned int	value;

	if (!(add_cd_check_valid(core, proc, inst)))
		return ;
	codage = core->map[(proc->pc + 1) % MEM_SIZE];
	arg1 = what_arg(codage, 1) == 1 ?
			proc->reg[fit_reg(read_arg(core->map, proc->pc, inst, 1))]
							: read_arg(core->map, proc->pc, inst, 1);
	what_arg(codage, 1) == C_IND ?
			arg1 = four_byte(core->map, pc_pos(arg1 + proc->pc)) : 0;
	arg2 = what_arg(codage, 2) == 1 ?
			proc->reg[fit_reg(read_arg(core->map, proc->pc, inst, 2))]
							: read_arg(core->map, proc->pc, inst, 2);
	value = four_byte(core->map, pc_pos(arg1 + arg2 + proc->pc));
	write_to_reg(value, read_arg(core->map, proc->pc, inst, 3), proc);
	proc->carry = value == 0 ? 1 : 0;
	proc->cd = -1;
	proc->prev_pc = proc->pc;
	proc->pc = (proc->pc + inst_size(inst, codage)) % MEM_SIZE;
}
