/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst_ldi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrybak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 19:03:08 by mrybak            #+#    #+#             */
/*   Updated: 2018/05/11 19:03:11 by mrybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../corewar.h"

void		ldi_inst(t_core *core, t_proc *proc, int inst)
{
	unsigned char	codage;
	int				arg1;
	int				arg2;

	if (!(add_cd_check_valid(core, proc, inst)))
		return ;
	codage = core->map[(proc->pc + 1) % MEM_SIZE];
	arg1 = what_arg(codage, 1) == 1 ?
			proc->reg[fit_reg(read_arg(core->map, proc->pc, inst, 1))]
			: read_arg(core->map, proc->pc, inst, 1);
	arg2 = what_arg(codage, 2) == 1 ?
			proc->reg[fit_reg(read_arg(core->map, proc->pc, inst, 2))]
			: read_arg(core->map, proc->pc, inst, 2);
	arg1 = four_byte(core->map, pc_pos((arg1 + arg2) % IDX_MOD + proc->pc));
	write_to_reg(arg1, read_arg(core->map, proc->pc, inst, 3), proc);
	proc->prev_pc = proc->pc;
	proc->pc = (proc->pc + inst_size(inst, codage)) % MEM_SIZE;
	proc->cd = -1;
}
