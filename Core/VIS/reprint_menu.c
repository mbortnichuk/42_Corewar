/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reprint_menu.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrybak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 15:19:35 by mrybak            #+#    #+#             */
/*   Updated: 2018/05/31 15:19:38 by mrybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../corewar.h"

void	re_print_middle_menu(t_core *core)
{
	if (core->champ_count >= 1)
	{
		mvprintw(14, 230, "%6d", core->champ->last_live);
		mvprintw(15, 230, "%6d", core->champ->lives_in_per);
	}
	if (core->champ_count >= 2)
	{
		mvprintw(18, 230, "%6d", core->champ->next->last_live);
		mvprintw(19, 230, "%6d", core->champ->next->lives_in_per);
	}
	if (core->champ_count >= 3)
	{
		mvprintw(22, 230, "%6d", core->champ->next->next->last_live);
		mvprintw(23, 230, "%6d", core->champ->next->next->lives_in_per);
	}
	if (core->champ_count == 4)
	{
		mvprintw(26, 230, "%6d", core->champ->next->next->next->last_live);
		mvprintw(27, 230, "%6d", core->champ->next->next->next->lives_in_per);
	}
}

void	re_print_bottom_menu(t_core *core)
{
	mvprintw(core->vis.y_b_menu + 2, 203 + 16, "%d   ", core->cycles_to_die);
	mvprintw(core->vis.y_b_menu + 3, 203 + 15, "%d   ", CYCLE_DELTA);
	mvprintw(core->vis.y_b_menu + 4, 203 + 12, "%d   ", NBR_LIVE);
	mvprintw(core->vis.y_b_menu + 5, 203 + 14, "%d   ", MAX_CHECKS);
	attron(COLOR_PAIR(15) | A_BOLD);
	mvprintw(core->vis.y_b_menu + 7, 203, "Press space to pause/resume.");
	mvprintw(core->vis.y_b_menu + 8, 203, "'*' to move one cycle forward");
	mvprintw(core->vis.y_b_menu + 9, 203, "Increase speed 'r' and '+'");
	mvprintw(core->vis.y_b_menu + 10, 203, "Decrease 'e' and '-'");
	mvprintw(core->vis.y_b_menu + 11, 203,
			"To turn off/on RaveParty mode press 'b'");
	if (core->vis.bold == 1)
	{
		attron(COLOR_PAIR(1) | A_BOLD);
		mvprintw(core->vis.y_b_menu + 12, 203, "RaveParty mode  on");
	}
	else
		mvprintw(core->vis.y_b_menu + 12, 203, "RaveParty mode off");
	attron(COLOR_PAIR(14) | A_BOLD);
}

void	re_print_top_menu(t_core *core)
{
	attron(COLOR_PAIR(15) | A_BOLD);
	mvprintw(9, 203 + 9, "%d    ", g_total_cycles);
	mvprintw(11, 203 + 14, "%d   ", count_procs(core->proc));
	mvprintw(7, 203 + 9, "%d   ", core->vis.speed);
	attron(COLOR_PAIR(14) | A_BOLD);
}

void	re_print_data(t_core *core)
{
	attron(COLOR_PAIR(14) | A_BOLD);
	re_print_top_menu(core);
	re_print_middle_menu(core);
	re_print_bottom_menu(core);
	re_print_registr(core);
	refresh();
	wrefresh(core->vis.big);
}
