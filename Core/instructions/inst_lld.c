/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst_lld.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrybak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/13 15:13:01 by mrybak            #+#    #+#             */
/*   Updated: 2018/05/13 15:13:04 by mrybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../corewar.h"

void		lld_inst(t_core *core, t_proc *proc, int inst)
{
	unsigned char	arg;
	int				value;

	value = 0;
	if (!(add_cd_check_valid(core, proc, inst)))
		return ;
	arg = what_arg(core->map[proc->pc + 1], 1);
	if (arg == C_DIR)
		value = read_direct(core, pc_pos(proc->pc + 2), g_tab[inst].dir_size);
	else if (arg == C_IND)
		value = four_byte(core->map, pc_pos(proc->pc +
						read_arg_no_idx(core->map, proc->pc, inst, 1)));
	write_to_reg(value, read_arg(core->map, proc->pc, inst, 2), proc);
	proc->carry = value == 0 ? 1 : 0;
	proc->cd = -1;
	proc->prev_pc = proc->pc;
	proc->pc = (proc->pc + inst_size(inst, core->map[proc->pc + 1])) % MEM_SIZE;
}
