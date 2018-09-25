/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_vis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkravets <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 22:22:02 by vkravets          #+#    #+#             */
/*   Updated: 2018/05/15 22:22:04 by vkravets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../corewar.h"

void	init_struct(t_core *core)
{
	core->vis.height = 70;
	core->vis.width = 256;
	core->vis.pause = 0;
	core->vis.key = 0;
	core->vis.speed = 50;
	core->vis.bold = 0;
	core->vis.field_carry = (int*)ft_memalloc(MEM_SIZE);
	core->vis.dim = NULL;
	core->vis.proc = NULL;
	if (core->vis.field_carry == NULL)
	{
		ft_printf("Malloc error, Sorry");
		exit(0);
	}
}

void	func_print_pause(t_core *core)
{
	attron(COLOR_PAIR(14) | A_BOLD);
	if (core->vis.pause == 0)
		core->vis.pause = 1;
	else if (core->vis.pause == 1)
		core->vis.pause = 0;
	if (core->vis.pause == 0)
		mvprintw(2, 203, "%s", "** PAUSED ** ");
	else if (core->vis.pause == 1)
		mvprintw(2, 203, "%s", "** RUNNING **");
	attroff(COLOR_PAIR(14) | A_BOLD);
}

void	ft_check_initscr(t_core *core)
{
	if (COLS < 256 || LINES < 69)
	{
		endwin();
		ft_printf("%s\n", "Too small window");
		free(core->vis.field_carry);
		exit(0);
	}
}

void	function_for_vis(t_core *core)
{
	init_struct(core);
	initscr();
	noecho();
	ft_check_initscr(core);
	function_paint_content(core);
	mousemask(ALL_MOUSE_EVENTS, NULL);
	while (core->vis.key != 32)
	{
		core->vis.key = wgetch(core->vis.big);
		re_print_data(core);
	}
	func_print_pause(core);
}
