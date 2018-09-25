/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_window.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkravets <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 16:26:46 by vkravets          #+#    #+#             */
/*   Updated: 2018/05/23 16:26:48 by vkravets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../corewar.h"

void	print_info_proc(t_vis vis)
{
	int		i;
	int		j;

	i = 0;
	j = 1;
	if (vis.proc == NULL)
		return ;
	attron(COLOR_PAIR(14) | A_BOLD);
	mvprintw(51, 207, "%s %d", "Register info owned by player #", vis.proc->id);
	while (++i <= REG_NUMBER)
	{
		if (i < 9)
		{
			vis.proc->reg[i] != 0 ? attron(COLOR_PAIR(5) | A_BOLD) : 0;
			mvprintw(53 + i, 207, "%d ", i);
			mvprintw(53 + i, 210, ":  %.8x", vis.proc->reg[i]);
		}
		else if (i >= 9)
		{
			vis.proc->reg[i] != 0 ? attron(COLOR_PAIR(5) | A_BOLD) : 0;
			mvprintw(53 + j, 228, "%d ", i);
			mvprintw(53 + j++, 231, ":  %.8x", vis.proc->reg[i]);
		}
		attron(COLOR_PAIR(14));
	}
}

void	print_kind_instr(t_vis vis, t_core *core)
{
	attron(COLOR_PAIR(5) | A_BOLD);
	if (vis.proc == NULL)
		return ;
	mvprintw(52, 207, "%s", "Instruction :      ");
	if (core->map[vis.proc->pc] >= 1 && core->map[vis.proc->pc] <= 16)
		mvprintw(52, 221, "%s", g_tab[core->map[vis.proc->pc]].name);
	mvprintw(63, 207, "%s % d", "Carry : ", vis.proc->carry);
	refresh();
}

void	re_print_registr(t_core *core)
{
	int		i;
	t_proc	*proc;

	i = 0;
	if ((getmouse(&core->vis.mouse)) == OK)
	{
		proc = core->proc;
		while (proc)
		{
			if ((int)proc->pc == (((core->vis.mouse.y - 2) * 64)
								+ (core->vis.mouse.x / 3)) - 1)
			{
				core->vis.proc = proc;
				core->vis.mouse.x = 10000;
				core->vis.mouse.y = 10000;
				break ;
			}
			proc = proc->next;
		}
	}
	if (core->vis.mouse.x == 10000)
	{
		print_kind_instr(core->vis, core);
		print_info_proc(core->vis);
	}
}

void	function_print_small(void)
{
	attron(COLOR_PAIR(14) | A_BOLD);
	mvprintw(49, 207, "%s", "Click on carriage to look the info");
	attroff(COLOR_PAIR(14) | A_BOLD);
}
