/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrybak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/12 17:57:24 by mrybak            #+#    #+#             */
/*   Updated: 2018/05/12 17:58:31 by mrybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../corewar.h"

void		fork_inst(t_core *core, t_proc *proc, int inst)
{
	int			dist;
	t_proc		*new;
	int			i;

	if (!(add_cd_check_valid(core, proc, inst)))
		return ;
	dist = pc_pos(two_byte(core->map, proc->pc + 1) + proc->pc);
	new = new_proc(proc->id, dist);
	new->carry = proc->carry;
	new->live = proc->live;
	new->colour_nbr = proc->colour_nbr;
	i = 0;
	while (++i != (REG_NUMBER + 1))
		new->reg[i] = proc->reg[i];
	add_proc(&core->proc, new);
	proc->prev_pc = proc->pc;
	proc->pc = (proc->pc + 3) % MEM_SIZE;
}
