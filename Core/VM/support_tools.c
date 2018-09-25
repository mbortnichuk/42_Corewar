/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iosypenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 15:22:03 by iosypenk          #+#    #+#             */
/*   Updated: 2018/05/07 15:22:07 by iosypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_vm.h"

t_champ			*get_last_list(t_champ *head)
{
	t_champ		*list;

	list = NULL;
	if (head)
	{
		list = head;
		while (list->next)
			list = list->next;
	}
	return (list);
}

void			add_proc(t_proc **alst, t_proc *new)
{
	if (new != NULL || (*alst) != NULL)
	{
		new->next = *alst;
		*alst = new;
	}
}

void			dump_stop(t_core *core)
{
	if (core->dump_stop != -1 &&
			g_total_cycles == (unsigned int)core->dump_stop)
	{
		print_dump(*core);
		exit(4);
	}
}
