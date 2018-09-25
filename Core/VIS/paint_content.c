/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint_content.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkravets <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 22:22:57 by vkravets          #+#    #+#             */
/*   Updated: 2018/05/15 22:22:59 by vkravets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../corewar.h"

void	function_print_map(t_core *core)
{
	unsigned int		i;
	t_proc				*proc;
	int					nb;
	int					count;

	count = 1;
	i = -1;
	refresh();
	proc = core->proc;
	while (proc->next != NULL)
		proc = proc->next;
	while (++i < MEM_SIZE)
	{
		if (i == proc->pc)
		{
			color_player(proc, &i, core);
			count++;
			nb = core->champ_count - count;
			proc = core->proc;
			while (nb-- > 0)
				proc = proc->next;
		}
		wprintw(core->vis.big, " %02x", core->map[i]);
		i % 64 == 63 ? wprintw(core->vis.big, "\n") : 0;
	}
}

void	function_made_border(void)
{
	int x;
	int y;

	x = 0;
	y = 0;
	refresh();
	attron(COLOR_PAIR(18));
	while (x < 259)
	{
		mvaddch(0, x, '*');
		mvaddch(67, x, '*');
		x++;
	}
	while (y < 68)
	{
		mvaddch(y, 0, '*');
		mvaddch(y, 196, '*');
		mvaddch(y, 258, '*');
		y++;
	}
	x = 197;
	while (x < 259)
		mvaddch(45, x++, '*');
	attron(COLOR_PAIR(15));
}

void	set_color(void)
{
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(21, COLOR_BLACK, COLOR_GREEN);
	init_pair(31, COLOR_WHITE, COLOR_GREEN);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_pair(22, COLOR_BLACK, COLOR_RED);
	init_pair(32, COLOR_WHITE, COLOR_RED);
	init_pair(3, COLOR_CYAN, COLOR_BLACK);
	init_pair(23, COLOR_BLACK, COLOR_CYAN);
	init_pair(33, COLOR_WHITE, COLOR_CYAN);
	init_pair(4, COLOR_BLUE, COLOR_BLACK);
	init_pair(24, COLOR_BLACK, COLOR_BLUE);
	init_pair(34, COLOR_WHITE, COLOR_BLUE);
	init_pair(14, COLOR_WHITE + 1, COLOR_BLACK);
	init_pair(41, COLOR_BLACK, COLOR_WHITE);
	init_pair(15, COLOR_WHITE, COLOR_BLACK);
	init_pair(17, COLOR_BLACK, COLOR_BLACK);
	init_pair(18, COLOR_WHITE, COLOR_WHITE);
	init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
}

void	function_paint_content(t_core *core)
{
	start_color();
	keypad(stdscr, TRUE);
	nodelay(stdscr, FALSE);
	curs_set(0);
	set_color();
	core->vis.big = newwin(64, 194, 2, 2);
	keypad(core->vis.big, TRUE);
	nodelay(core->vis.big, TRUE);
	function_made_border();
	function_print_map(core);
	function_print_small();
	print_top_menu(core);
	print_middle_menu(core);
	print_bottom_menu(core);
	print_carry(core);
}
