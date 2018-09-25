/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supp_to_inst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrybak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 12:54:13 by mrybak            #+#    #+#             */
/*   Updated: 2018/05/08 12:54:18 by mrybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../corewar.h"

void				write_to_reg(int value, unsigned int reg_num, t_proc *proc)
{
	if (reg_num <= REG_NUMBER && reg_num != 0)
		proc->reg[reg_num] = value;
}

unsigned int		pc_pos(unsigned int dist)
{
	return ((dist % MEM_SIZE + MEM_SIZE) % MEM_SIZE);
}

unsigned int		fit_reg(unsigned int nb)
{
	if (nb <= REG_NUMBER && nb != 0)
		return (nb);
	else
		return (0);
}

unsigned char		what_arg(unsigned char codage, int arg_nb)
{
	unsigned char	arg;

	arg = 0;
	arg_nb == 1 ? arg = codage >> 6 : 0;
	arg_nb == 2 ? arg = (codage & 48) >> 4 : 0;
	arg_nb == 3 ? arg = (codage & 12) >> 2 : 0;
	return (arg);
}

unsigned int		arg_size(int inst, unsigned char codage, int arg_nb)
{
	unsigned char	arg;
	unsigned int	res;

	res = 0;
	arg = what_arg(codage, arg_nb);
	arg == C_DIR && g_tab[inst].dir_size == 0 ? res = S_DIR_0 : 0;
	arg == C_DIR && g_tab[inst].dir_size == 1 ? res = S_DIR_1 : 0;
	arg == C_IND ? res = S_IND : 0;
	arg == C_REG ? res = S_REG : 0;
	return (res);
}
