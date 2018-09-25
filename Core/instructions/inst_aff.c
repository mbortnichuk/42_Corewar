/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst_aff.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrybak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/13 15:50:15 by mrybak            #+#    #+#             */
/*   Updated: 2018/05/13 15:50:16 by mrybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../corewar.h"

void		aff_inst(t_core *core, t_proc *proc, int inst)
{
	if (!(add_cd_check_valid(core, proc, inst)))
		return ;
	if (core->a_flag == 1)
		ft_printf("Aff: %c\n",
				proc->reg[core->map[(proc->pc + 2) % MEM_SIZE]] % 256);
	proc->prev_pc = proc->pc;
	proc->pc = (proc->pc + 3) % MEM_SIZE;
}
