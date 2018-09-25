/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrybak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 17:43:30 by mrybak            #+#    #+#             */
/*   Updated: 2018/05/01 17:44:45 by mrybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../corewar.h"

void		time_to_die(t_core *core)
{
	static int i;

	if (live_in_period(core->champ) >= 21)
	{
		core->cycles_to_die -= CYCLE_DELTA;
		i = 0;
	}
	else if (i == MAX_CHECKS)
	{
		core->cycles_to_die -= CYCLE_DELTA;
		i = 0;
	}
	kill_them(&core->proc, core);
	reset_lives(core->champ, core->proc);
	i++;
}

void		chose_command(t_core *core, t_proc *proc)
{
	if (core->map[proc->pc] <= 16 && core->map[proc->pc] >= 1)
		g_func[core->map[proc->pc]].func(core, proc, core->map[proc->pc]);
	else
	{
		proc->prev_pc = proc->pc;
		proc->pc = (proc->pc + 1) % MEM_SIZE;
	}
}

void		apply_commands(t_core *core)
{
	t_proc	*tmp_proc;

	if (!core->proc)
		return ;
	tmp_proc = core->proc;
	while (tmp_proc)
	{
		if (tmp_proc->cd == 0 || tmp_proc->cd < 0)
			chose_command(core, tmp_proc);
		tmp_proc->cd--;
		tmp_proc = tmp_proc->next;
	}
}

void		game_start(t_core *core)
{
	int		i;

	if (core->vis_flag == 1)
		function_for_vis(core);
	while (core->cycles_to_die > 0)
	{
		i = 0;
		while (i++ < core->cycles_to_die)
		{
			dump_stop(core);
			g_total_cycles++;
			apply_commands(core);
			core->vis_flag == 1 ? check_pause(core) : 0;
		}
		time_to_die(core);
	}
	core->vis_flag == 1 ? end_vis(core) : get_winner(core);
}
