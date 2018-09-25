/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iosypenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 12:40:20 by iosypenk          #+#    #+#             */
/*   Updated: 2018/05/08 12:40:22 by iosypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_vm.h"

static void			if_nbr(t_core *core, char **argv, int i)
{
	t_champ		*lst;
	int			nb;
	int			max_nb;

	max_nb = 2147483644;
	lst = core->champ;
	(!argv[i + 1]) ? show_usage() : 0;
	nb = ft_atoi(argv[i + 1]);
	if (argv[i + 1] && nb > 0 && nb <= max_nb)
	{
		while (lst)
		{
			lst->fileinfo.id == -nb ? err(1) : 0;
			lst = lst->next;
		}
		core->tmp = (-1) * nb;
		return ;
	}
	err(5);
}

static void			if_dump(t_core *core, char **argv, int i)
{
	int			nb;
	int			max_nb;

	max_nb = 2147483647;
	(!argv[i + 1]) ? err(2) : 0;
	nb = ft_atoi(argv[i + 1]);
	if (nb < 0 || nb > max_nb)
		return ;
	core->dump_stop = nb;
}

int					check_flags(t_core *core, char **argv, int i)
{
	if (!ft_strcmp(argv[i], "-n"))
	{
		if_nbr(core, argv, i);
		return (i + 2);
	}
	else if (!ft_strcmp(argv[i], "-dump"))
	{
		if (argv[i + 1] && (!ft_strcmp(argv[i + 1], "-vis") ||
			!ft_strcmp(argv[i + 1], "-n")))
			return (i + 1);
		core->vis_flag != 1 ? if_dump(core, argv, i) : 0;
		return (i + 2);
	}
	else if (!ft_strcmp(argv[i], "-vis") && !(core->a_flag = 0))
	{
		core->vis_flag = 1;
		core->dump_stop = -1;
		return (i + 1);
	}
	else if (!ft_strcmp(argv[i], "-a"))
	{
		core->vis_flag != 1 ? core->a_flag = 1 : 0;
		return (i + 1);
	}
	return (i);
}

static int			get_number(t_core *core)
{
	int			res;
	t_champ		*lst;

	lst = core->champ;
	res = --core->last;
	while (lst)
	{
		if (lst->fileinfo.id == res - 1)
		{
			res--;
		}
		lst = lst->next;
	}
	return (res);
}

/*
**	Call to init_champ is at parsing_champ.c
*/

void				init_champ(t_champ *champ, t_core *core)
{
	if (core->champ_count < MAX_PLAYERS)
	{
		champ->fileinfo.id = -((core->champ_count++) + 1);
		champ->fileinfo.id = (core->tmp != 0) ? core->tmp : get_number(core);
		core->last = champ->fileinfo.id;
		core->tmp = 0;
	}
	else
		err(3);
}
