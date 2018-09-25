/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_player_menu.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkravets <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 22:50:04 by vkravets          #+#    #+#             */
/*   Updated: 2018/05/15 22:50:05 by vkravets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../corewar.h"

int		digit_count(int num)
{
	int i;

	i = 0;
	num = -num;
	while (num)
	{
		i++;
		num /= 10;
	}
	return (i);
}

void	one_player(t_core *core)
{
	attron(COLOR_PAIR(15) | A_BOLD);
	mvprintw(13, 203, "%s %d %s", "Player", core->champ->fileinfo.id, ":");
	attron(COLOR_PAIR(core->champ->fileinfo.colour_nbr));
	mvprintw(13, 215 + digit_count(core->champ->fileinfo.id), "%s",
			core->champ->header.prog_name);
	attron(COLOR_PAIR(14));
	mvprintw(14, 203, "%s", "Last live : ");
	mvprintw(14, 230, "%d", core->champ->last_live);
	mvprintw(15, 203, "%s %d", "Lives in current period : ",
			core->champ->lives_in_per);
	core->vis.y_b_menu = 15;
	attroff(COLOR_PAIR(14) | A_BOLD);
}

void	two_player(t_core *core)
{
	t_champ *temp;

	temp = core->champ->next;
	attron(COLOR_PAIR(15) | A_BOLD);
	mvprintw(17, 203, "%s %d %s", "Player", temp->fileinfo.id, ":");
	attron(COLOR_PAIR(temp->fileinfo.colour_nbr));
	mvprintw(17, 215 + digit_count(temp->fileinfo.id), "%s",
			temp->header.prog_name);
	attron(COLOR_PAIR(14));
	mvprintw(18, 203, "%s ", "Last live : ");
	mvprintw(18, 230, "%d", temp->last_live);
	mvprintw(19, 203, "%s %d", "Lives in current period : ",
			temp->lives_in_per);
	core->vis.y_b_menu = 19;
	attroff(COLOR_PAIR(14) | A_BOLD);
}

void	three_player(t_core *core)
{
	t_champ *temp;

	temp = core->champ->next;
	attron(COLOR_PAIR(15) | A_BOLD);
	mvprintw(21, 203, "%s %d %s", "Player", temp->next->fileinfo.id, ":");
	attron(COLOR_PAIR(temp->next->fileinfo.colour_nbr));
	mvprintw(21, 215 + digit_count(temp->next->fileinfo.id), "%s",
			temp->next->header.prog_name);
	attron(COLOR_PAIR(14));
	mvprintw(22, 203, "%s", "Last live : ");
	mvprintw(22, 230, "%d", temp->next->last_live);
	mvprintw(23, 203, "%s %d", "Lives in current period : ",
			temp->next->lives_in_per);
	core->vis.y_b_menu = 23;
	attroff(COLOR_PAIR(14) | A_BOLD);
}

void	four_player(t_core *core)
{
	t_champ *temp;

	temp = core->champ->next->next;
	attron(COLOR_PAIR(15) | A_BOLD);
	mvprintw(25, 203, "%s %d %s", "Player", temp->next->fileinfo.id, ":");
	attron(COLOR_PAIR(temp->next->fileinfo.colour_nbr));
	mvprintw(25, 215 + digit_count(temp->next->fileinfo.id), "%s",
			temp->next->header.prog_name);
	attron(COLOR_PAIR(14));
	mvprintw(26, 203, "%s", "Last live : ");
	mvprintw(26, 230, "%d", temp->next->last_live);
	mvprintw(27, 203, "%s %d", "Lives in current period : ",
			temp->next->lives_in_per);
	core->vis.y_b_menu = 27;
	attroff(COLOR_PAIR(14) | A_BOLD);
}
