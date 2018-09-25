/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrybak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 17:44:48 by mrybak            #+#    #+#             */
/*   Updated: 2018/05/31 17:44:50 by mrybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../corewar.h"

unsigned int		inst_size(int inst, unsigned char codage)
{
	unsigned int	res;
	int				arg_nb;

	arg_nb = 1;
	res = 1;
	if (g_tab[inst].numb_of_arg > 1)
	{
		res++;
		while (g_tab[inst].numb_of_arg >= arg_nb)
			res += arg_size(inst, codage, arg_nb++);
	}
	else if (g_tab[inst].numb_of_arg == 1)
	{
		g_tab->arg[0] == C_DIR && g_tab[inst].dir_size == 0
		? res = S_DIR_0 : 0;
		g_tab->arg[0] == C_DIR && g_tab[inst].dir_size == 1
		? res = S_DIR_1 : 0;
		g_tab->arg[0] == C_IND ? res = S_IND : 0;
		g_tab->arg[0] == C_REG ? res = S_REG : 0;
	}
	return (res);
}

unsigned int		read_arg(unsigned char *map, unsigned int pc,
										int inst, int arg_nb)
{
	unsigned int		res;
	int					ret;
	int					i;
	unsigned char		codage;

	codage = map[(pc + 1) % MEM_SIZE];
	res = inst_size(inst, codage);
	i = arg_nb;
	while (i < 4)
		res = res - arg_size(inst, codage, i++);
	if (arg_size(inst, codage, arg_nb) == S_REG)
		ret = map[(res + pc) % MEM_SIZE];
	if (arg_size(inst, codage, arg_nb) == S_IND)
	{
		ret = 0;
		arg_type(codage, arg_nb) == T_DIR ?
				ret = two_byte(map, pc_pos(res + pc)) : 0;
		arg_type(codage, arg_nb) == T_IND ? ret = four_byte(map,
					pc_pos(two_byte(map, pc_pos(res + pc)) % IDX_MOD + pc)) : 0;
		arg_type(codage, arg_nb) == T_IND && inst == 3 ?
				ret = two_byte(map, pc_pos(res + pc)) % IDX_MOD : 0;
	}
	if (arg_size(inst, codage, arg_nb) == S_DIR_0)
		ret = (four_byte(map, pc_pos(res + pc)));
	return (ret);
}

unsigned int		read_arg_no_idx(unsigned char *map, unsigned int pc,
											int inst, int arg_nb)
{
	unsigned int		res;
	int					ret;
	int					i;
	unsigned char		codage;

	codage = map[(pc + 1) % MEM_SIZE];
	res = inst_size(inst, codage);
	i = arg_nb;
	while (i < 4)
		res = res - arg_size(inst, codage, i++);
	if (arg_size(inst, codage, arg_nb) == S_REG)
		ret = map[(res + pc) % MEM_SIZE];
	if (arg_size(inst, codage, arg_nb) == S_IND)
	{
		ret = 0;
		arg_type(codage, arg_nb) == T_DIR ?
				ret = two_byte(map, pc_pos(res + pc)) : 0;
		arg_type(codage, arg_nb) == T_IND ? ret = four_byte(map,
						pc_pos(two_byte(map, pc_pos((res + pc))) + pc)) : 0;
		arg_type(codage, arg_nb) == T_IND && inst == 3 ?
				ret = two_byte(map, pc_pos(res + pc)) : 0;
	}
	if (arg_size(inst, codage, arg_nb) == S_DIR_0)
		ret = (four_byte(map, pc_pos(res + pc)));
	return (ret);
}

int					add_cd_check_valid(t_core *core, t_proc *proc, int inst)
{
	if (proc->cd < 0)
	{
		proc->cd = g_tab[inst].cycles - 1;
		return (0);
	}
	else if (!(if_inst_valid(core, proc, inst)))
	{
		proc->prev_pc = proc->pc;
		proc->pc = (proc->pc + 1) % MEM_SIZE;
		return (0);
	}
	return (1);
}

unsigned int		arg_type(unsigned char codage, int arg_nb)
{
	unsigned char	arg;
	unsigned int	res;

	res = 0;
	arg = what_arg(codage, arg_nb);
	arg == C_DIR ? res = T_DIR : 0;
	arg == C_IND ? res = T_IND : 0;
	arg == C_REG ? res = T_REG : 0;
	return (res);
}
