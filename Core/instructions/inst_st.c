/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst_st.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrybak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 11:19:30 by mrybak            #+#    #+#             */
/*   Updated: 2018/05/09 11:40:09 by mrybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../corewar.h"

void		st_inst(t_core *core, t_proc *proc, int inst)
{
	unsigned char	arg;
	unsigned char	codage;
	unsigned int	adr;
	unsigned int	reg_nb;

	if (!(add_cd_check_valid(core, proc, inst)))
		return ;
	codage = core->map[(proc->pc + 1) % MEM_SIZE];
	reg_nb = fit_reg(read_arg(core->map, proc->pc, inst, 1));
	arg = what_arg(codage, 2);
	if (arg == C_IND)
	{
		adr = pc_pos(proc->pc + read_arg(core->map, proc->pc, inst, 2));
		write_to_map(core->map, proc->reg[reg_nb], adr);
		core->vis_flag == 1 ? replace_field(adr, proc->colour_nbr, core) : 0;
	}
	else if (arg == C_REG)
		write_to_reg(proc->reg[reg_nb],
					read_arg(core->map, proc->pc, inst, 2), proc);
	proc->prev_pc = proc->pc;
	proc->pc = pc_pos(proc->pc + inst_size(inst, codage));
	proc->cd = -1;
}
