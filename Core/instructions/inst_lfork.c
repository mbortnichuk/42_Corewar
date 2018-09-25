/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst_lfork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrybak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/13 15:29:22 by mrybak            #+#    #+#             */
/*   Updated: 2018/05/13 15:29:24 by mrybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../corewar.h"

void		lfork_inst(t_core *core, t_proc *proc, int inst)
{
	int			dist;
	t_proc		*new;
	int			i;

	if (!(add_cd_check_valid(core, proc, inst)))
		return ;
	dist = two_byte(core->map, proc->pc + 1);
	new = new_proc(proc->id, pc_pos(dist + proc->pc));
	new->carry = proc->carry;
	new->colour_nbr = proc->colour_nbr;
	new->live = proc->live;
	i = 0;
	while (++i != (REG_NUMBER + 1))
		new->reg[i] = proc->reg[i];
	add_proc(&core->proc, new);
	proc->prev_pc = proc->pc;
	proc->pc = pc_pos(proc->pc + 3);
}
