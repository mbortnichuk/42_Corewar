/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carry_fork_proc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkravets <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 16:05:11 by vkravets          #+#    #+#             */
/*   Updated: 2018/05/19 16:05:12 by vkravets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../corewar.h"

void	print_fork_proc(t_core *core)
{
	t_proc *proc;

	proc = core->proc;
	while (proc)
	{
		print_first_carry(proc->pc, core);
		proc = proc->next;
	}
}

int		if_dim_exists(t_make_dim *dim, unsigned int adr, int color)
{
	t_make_dim *tmp;

	tmp = dim;
	while (dim)
	{
		if (dim->adr == adr)
		{
			dim->cd = 10;
			dim->color = color;
			return (1);
		}
		dim = dim->next;
	}
	return (0);
}

void	get_position(unsigned int position, int color, t_core *core)
{
	core->vis.x = (position % 64) * 3;
	core->vis.y = COORD_Y(position);
	wmove(core->vis.big, core->vis.y, core->vis.x);
	if (core->vis.bold == 1)
		wattron(core->vis.big, COLOR_PAIR(color) | A_BOLD);
	else
		wattron(core->vis.big, COLOR_PAIR(color));
	wprintw(core->vis.big, " %02x", core->map[position]);
	if (core->vis.bold == 1)
		wattron(core->vis.big, COLOR_PAIR(color) | A_BOLD);
	else
		wattron(core->vis.big, COLOR_PAIR(color));
}

void	replace_field(int position, int color, t_core *core)
{
	int i;

	if (!(if_dim_exists(core->vis.dim, position, color)))
		add_dim(&core->vis.dim, new_dim(position, color));
	i = 4;
	while (i > 0)
	{
		i--;
		get_position((position + i) % MEM_SIZE, color, core);
	}
}
