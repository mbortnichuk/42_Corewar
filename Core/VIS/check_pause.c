/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pause.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkravets <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 13:00:43 by vkravets          #+#    #+#             */
/*   Updated: 2018/05/17 13:00:45 by vkravets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../corewar.h"

void		end_vis(t_core *core)
{
	attron(COLOR_PAIR(2) | A_BOLD);
	mvprintw(core->vis.y_b_menu + 14, 203 + 2,
			"Contestant %s has won!", get_winner(core));
	mvprintw(core->vis.y_b_menu + 16, 203 + 2, "Press q to exit");
	while (1)
	{
		core->vis.key = getch();
		if (core->vis.key == 113)
		{
			endwin();
			return ;
		}
	}
}

void		bold_off(t_core *core)
{
	t_make_dim *dim;

	dim = core->vis.dim;
	while (dim)
	{
		dim->cd = 0;
		dim = dim->next;
	}
	replace_field_dim(core);
	replace_field_dim(core);
	kill_old_dim(&core->vis.dim);
}

void		check_another_key(t_core *core)
{
	if (core->vis.key == 45 && core->vis.speed > 5)
		core->vis.speed -= 5;
	else if (core->vis.key == 43 && core->vis.speed < 1000)
		core->vis.speed += 5;
	else if (core->vis.key == 101 && core->vis.speed > 2)
	{
		core->vis.speed -= 100;
		core->vis.speed <= 0 ? core->vis.speed = 5 : 0;
	}
	else if (core->vis.key == 114 && core->vis.speed < 1000)
	{
		core->vis.speed += 100;
		core->vis.speed > 1000 ? core->vis.speed = 1000 : 0;
	}
	else if (core->vis.key == 98 && core->vis.bold == 0)
		core->vis.bold = 1;
	else if (core->vis.key == 98 && core->vis.bold == 1)
	{
		core->vis.bold = 0;
		bold_off(core);
	}
}

void		stop_cycles(t_core *core)
{
	core->vis.key = getch();
	if (core->vis.key == 32)
		core->vis.pause = 1;
	if (g_total_cycles == 1)
	{
		core->vis.pause = 0;
		refresh();
	}
	mvprintw(2, 203, "%s", (core->vis.pause == 1) ?
						"** PAUSED ** " : "** RUNNING **");
	while (core->vis.pause == 1)
	{
		core->vis.key = getch();
		if (core->vis.key == 42 || core->vis.key == 32)
		{
			core->vis.pause = core->vis.key == 42 ? 1 : 0;
			return ;
		}
		check_another_key(core);
		re_print_data(core);
	}
}

int			check_pause(t_core *core)
{
	halfdelay(0);
	timeout(1000 / core->vis.speed);
	check_another_key(core);
	re_print_data(core);
	core->vis.bold == 1 ? replace_field_dim(core) : 0;
	print_fork_proc(core);
	clean_carry(core);
	stop_cycles(core);
	return (0);
}
