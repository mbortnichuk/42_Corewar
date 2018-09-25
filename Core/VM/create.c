/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iosypenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 14:30:43 by iosypenk          #+#    #+#             */
/*   Updated: 2018/05/15 14:30:52 by iosypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_vm.h"

void			create_map(t_core *core)
{
	core->i = 0;
	while (core->i < MEM_SIZE)
	{
		core->map[core->i] = 0;
		core->i++;
	}
}

void			create_champ(t_core *core)
{
	t_champ		*new;
	t_champ		*last;

	if (!(new = malloc(sizeof(t_champ))))
		err(0);
	new->next = NULL;
	new->last_live = 0;
	new->lives_in_per = 0;
	new->fileinfo.filename = NULL;
	if ((last = get_last_list(core->champ)))
		last->next = new;
	else
		core->champ = new;
}

void			create_proc(t_proc **head, int id, int pc, int col_nbr)
{
	t_proc	*new_proc;
	int		i;

	i = 0;
	if (!(new_proc = (t_proc*)malloc(sizeof(t_proc))))
		err(0);
	while (++i < REG_NUMBER + 1)
		new_proc->reg[i] = 0;
	new_proc->id = id;
	new_proc->reg[1] = id;
	new_proc->prev_pc = -1;
	new_proc->carry = 0;
	new_proc->live = 0;
	new_proc->cd = -1;
	new_proc->pc = pc;
	new_proc->next = NULL;
	new_proc->colour_nbr = col_nbr;
	add_proc(head, new_proc);
}

t_proc			*new_proc(int id, int pc)
{
	t_proc	*new_proc;
	int		i;

	i = 0;
	if (!(new_proc = (t_proc*)malloc(sizeof(t_proc))))
		err(0);
	while (++i < REG_NUMBER + 1)
		new_proc->reg[i] = 0;
	new_proc->id = id;
	new_proc->prev_pc = 0;
	new_proc->carry = 0;
	new_proc->live = 0;
	new_proc->cd = -1;
	new_proc->pc = pc;
	new_proc->next = NULL;
	return (new_proc);
}
