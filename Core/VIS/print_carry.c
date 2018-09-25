/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_carry.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkravets <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 13:00:32 by vkravets          #+#    #+#             */
/*   Updated: 2018/05/17 13:00:33 by vkravets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../corewar.h"

void	swap_two_col(int pair, int position, t_core *core)
{
	wattron(core->vis.big, COLOR_PAIR(pair + 20) | A_BOLD);
	wprintw(core->vis.big, "%02x", core->map[position]);
	wattroff(core->vis.big, A_BOLD);
}

void	change_color(int color, int position, t_core *core)
{
	wattron(core->vis.big, COLOR_PAIR(color));
	wprintw(core->vis.big, "%02x", core->map[position]);
}

void	print_first_carry(int position, t_core *core)
{
	if (core->vis.field_carry[position] == 0)
	{
		core->vis.x = COORD_X(position);
		core->vis.y = COORD_Y(position);
		core->vis.ret = mvwinch(core->vis.big, core->vis.y,
								core->vis.x) & A_COLOR;
		if (core->vis.ret == COLOR_PAIR(1))
			swap_two_col(1, position, core);
		else if (core->vis.ret == COLOR_PAIR(2))
			swap_two_col(2, position, core);
		else if (core->vis.ret == COLOR_PAIR(3))
			swap_two_col(3, position, core);
		else if (core->vis.ret == COLOR_PAIR(4))
			swap_two_col(4, position, core);
		else if (core->vis.ret == COLOR_PAIR(14))
			change_color(41, position, core);
		core->vis.field_carry[position] = 1;
	}
}

void	print_carry(t_core *core)
{
	t_proc *proc;

	if (core->champ_count >= 1)
		print_first_carry(core->proc->pc, core);
	if (core->champ_count >= 2)
		print_first_carry(core->proc->next->pc, core);
	if (core->champ_count >= 3)
	{
		proc = core->proc->next->next;
		print_first_carry(proc->pc, core);
	}
	if (core->champ_count >= 4)
	{
		proc = core->proc->next->next;
		print_first_carry(proc->next->pc, core);
	}
}

void	return_color_carry(t_proc *proc, t_core *core)
{
	int position;

	position = proc->prev_pc;
	if (core->vis.field_carry[position] == 1)
	{
		core->vis.x = COORD_X(position);
		core->vis.y = COORD_Y(position);
		core->vis.ret = mvwinch(core->vis.big,
								core->vis.y, core->vis.x) & A_COLOR;
		if (core->vis.ret == COLOR_PAIR(21))
			change_color(1, position, core);
		else if (core->vis.ret == COLOR_PAIR(22))
			change_color(2, position, core);
		else if (core->vis.ret == COLOR_PAIR(23))
			change_color(3, position, core);
		else if (core->vis.ret == COLOR_PAIR(24))
			change_color(4, position, core);
		else if (core->vis.ret == COLOR_PAIR(41))
			change_color(14, position, core);
		wrefresh(core->vis.big);
		core->vis.field_carry[position] = 0;
	}
}
