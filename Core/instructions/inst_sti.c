/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst_sti.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrybak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/12 14:56:12 by mrybak            #+#    #+#             */
/*   Updated: 2018/05/12 14:56:14 by mrybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../corewar.h"

void		sti_inst(t_core *core, t_proc *proc, int inst)
{
	int				arg1;
	int				arg2;
	unsigned char	codage;

	if (!(add_cd_check_valid(core, proc, inst)))
		return ;
	codage = core->map[(proc->pc + 1) % MEM_SIZE];
	arg1 = what_arg(codage, 2) == 1 ?
		proc->reg[fit_reg(read_arg(core->map, proc->pc, inst, 2))]
			: read_arg(core->map, proc->pc, inst, 2);
	if (arg_type(codage, 2) == C_IND)
		arg1 = four_byte(core->map, read_arg(core->map, proc->pc, inst, 3)
									% IDX_MOD);
	arg2 = what_arg(codage, 3) == 1 ?
			proc->reg[fit_reg(read_arg(core->map, proc->pc, inst, 3))]
			: read_arg(core->map, proc->pc, inst, 3);
	write_to_map(core->map,
				proc->reg[fit_reg(read_arg(core->map, proc->pc, inst, 1))],
				pc_pos((arg1 + arg2) % IDX_MOD + proc->pc));
	core->vis_flag == 1 ? replace_field(pc_pos(proc->pc + (arg1 + arg2)),
										proc->colour_nbr, core) : 0;
	proc->prev_pc = proc->pc;
	proc->pc = (proc->pc + inst_size(inst, codage)) % MEM_SIZE;
	proc->cd = -1;
}
