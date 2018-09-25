/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_inst_valid.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrybak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 11:54:20 by mrybak            #+#    #+#             */
/*   Updated: 2018/05/11 11:54:23 by mrybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../corewar.h"

int			if_inst_valid(t_core *core, t_proc *proc, int inst)
{
	unsigned char codage;

	if (g_tab[inst].codage == 1)
	{
		codage = core->map[(proc->pc + 1) % MEM_SIZE];
		if (codage == 0)
			return (0);
		if ((arg_type(codage, 1) & g_tab[inst].arg[0]) != arg_type(codage, 1))
			return (0);
		if ((arg_type(codage, 2) & g_tab[inst].arg[1]) != arg_type(codage, 2))
			return (0);
		if ((arg_type(codage, 3) & g_tab[inst].arg[2]) != arg_type(codage, 3))
			return (0);
		return (1);
	}
	return (1);
}
