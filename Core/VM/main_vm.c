/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_vm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iosypenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 16:34:17 by iosypenk          #+#    #+#             */
/*   Updated: 2018/05/01 16:34:21 by iosypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_vm.h"

static void			init(t_core *core)
{
	create_map(core);
	core->champ = NULL;
	core->champ_count = 0;
	core->proc = NULL;
	core->cycles_to_die = CYCLE_TO_DIE;
	core->tmp = 0;
	core->last = 0;
	core->dump_stop = -1;
	core->vis_flag = 0;
	core->a_flag = 0;
}

static void			parsing_args(int argc, char **argv, t_core *core)
{
	int				i;

	i = 1;
	while (i < argc)
	{
		if ((i = check_flags(core, argv, i)) >= argc)
			break ;
		if (ft_strcmp(argv[i], "-dump") && ft_strcmp(argv[i], "-n") &&
			ft_strcmp(argv[i], "-vis") && ft_strcmp(argv[i], "-a"))
		{
			(!ft_strstr(argv[i], ".cor")) ? err_arg(4, argv[i]) : 0;
			create_champ(core);
			parsing_champ(core, argv[i]);
			i++;
		}
	}
	place_champs(core);
}

int					main(int argc, char **argv)
{
	t_core			core;

	if (argc == 1)
	{
		show_usage();
	}
	else if (argc > 1)
	{
		init(&core);
		parsing_args(argc, argv, &core);
		game_start(&core);
	}
	return (0);
}
