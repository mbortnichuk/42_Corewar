/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_menu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkravets <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 22:46:42 by vkravets          #+#    #+#             */
/*   Updated: 2018/05/15 22:46:47 by vkravets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../corewar.h"

int		count_procs(t_proc *proc)
{
	t_proc	*list;
	int		i;

	i = 0;
	list = proc;
	while (list)
	{
		i++;
		list = list->next;
	}
	return (i);
}

void	print_top_menu(void)
{
	attron(COLOR_PAIR(15) | A_BOLD);
	mvprintw(2, 203, "%s", "** PAUSED **");
	mvprintw(9, 203, "%s   ", "Cycle : ");
	mvprintw(11, 203, "%s    ", "Processes : ");
	mvprintw(7, 203, "%s   ", "Speed : ");
	attroff(COLOR_PAIR(14) | A_BOLD);
}

void	print_middle_menu(t_core *core)
{
	if (core->champ_count >= 1)
		one_player(core);
	if (core->champ_count >= 2)
		two_player(core);
	if (core->champ_count >= 3)
		three_player(core);
	if (core->champ_count == 4)
		four_player(core);
}

void	print_bottom_menu(t_core *core)
{
	attron(COLOR_PAIR(14) | A_BOLD);
	mvprintw(core->vis.y_b_menu + 2, 203, "%s %d", "CYCLE_TO_DIE : ",
													CYCLE_TO_DIE);
	mvprintw(core->vis.y_b_menu + 3, 203, "%s %d", "CYCLE_DELTA : ",
													CYCLE_DELTA);
	mvprintw(core->vis.y_b_menu + 4, 203, "%s %d", "NBR_LIVE : ", NBR_LIVE);
	mvprintw(core->vis.y_b_menu + 5, 203, "%s %d", "MAX_CHECKS : ", MAX_CHECKS);
	attroff(COLOR_PAIR(14) | A_BOLD);
}
