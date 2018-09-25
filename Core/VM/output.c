/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iosypenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 14:31:44 by iosypenk          #+#    #+#             */
/*   Updated: 2018/05/15 14:31:53 by iosypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_vm.h"

void			show_usage(void)
{
	ft_printf(YEL"Usage: ./corewar	[-dump nbr_cycles] [-n number] [-vis] "
		"[-a] <player1.cor> <...> <player.cor>\n"RC
		"	-a : Prints output from \"aff\" (It is hidden by default)\n"
		MAG"	-n nbr : Sets the number of the next player\n"RC
		CYN"	-dump nbr : Dumps memory after nbr cycles then exits\n"RC
		GRN"	-vis : Ncurses output mode\n"RC);
	exit(1);
}

void			err(int nb)
{
	ft_printf(RED"Error: "RC);
	nb == 0 ? ft_printf("\n") : 0;
	nb == 1 ? ft_printf("Player number already exists.\n") : 0;
	nb == 2 ? ft_printf("Can not read source file \"-dump\"\n") : 0;
	nb == 3 ? ft_printf("Too many players\n") : 0;
	nb == 4 ? ft_printf("Can not read source file\n") : 0;
	if (nb == 5)
	{
		ft_printf("Please set number in such limits: "
			"0 < number < 2147483645\n");
		show_usage();
	}
	nb == 6 ? ft_printf("AFSFASFASFAS\n") : 0;
	exit(2);
}

void			err_arg(int nb, char *arg)
{
	ft_printf(RED"Error: "RC);
	nb == 0 ? ft_printf("Can not open source file "RED"%s"RC"\n", arg) : 0;
	nb == 1 ? ft_printf("Can not read source file "RED"%s"RC"\n", arg) : 0;
	nb == 2 ? ft_printf("File "RED"%s"RC" has too big code size\n", arg) : 0;
	nb == 3 ? ft_printf("File "RED"%s"RC" has a code size "
		"that differ from what its header says\n", arg) : 0;
	nb == 4 ? ft_printf("File "RED"%s"RC" has wrong magic number "
		"or is not a \".core\" file\n", arg) : 0;
	nb == 5 ? ft_printf("File "RED"%s"RC" has empty name\n", arg) : 0;
	nb == 6 ? ft_printf("File "RED"%s"RC" has empty comment\n", arg) : 0;
	exit(3);
}

void			introduce(t_champ *champ, int nb)
{
	int			id;

	id = (-1) * champ->fileinfo.id;
	(nb == 1) ? ft_printf("Introducing contestants...\n") : 0;
	(nb == 1) ? ft_printf(GRN"* Player %d"RC", weighing %d bytes, \""
		GRN"%s"RC"\" (\"%s\") !\n"RC, id, champ->header.prog_size,
			champ->header.prog_name, champ->header.comment) : 0;
	(nb == 2) ? ft_printf(BLU"* Player %d"RC", weighing %d bytes, \""
		BLU"%s"RC"\" (\"%s\") !\n"RC, id, champ->header.prog_size,
			champ->header.prog_name, champ->header.comment) : 0;
	(nb == 3) ? ft_printf(RED"* Player %d"RC", weighing %d bytes, \""
		RED"%s"RC"\" (\"%s\") !\n"RC, id, champ->header.prog_size,
			champ->header.prog_name, champ->header.comment) : 0;
	(nb == 4) ? ft_printf(CYN"* Player %d"RC", weighing %d bytes, \""
		CYN"%s"RC"\" (\"%s\") !\n"RC, id, champ->header.prog_size,
			champ->header.prog_name, champ->header.comment) : 0;
}

void			print_dump(t_core core)
{
	int		i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (i == 0)
		{
			ft_printf(CYN"0x0000 : "RC);
		}
		else if (i % 64 == 0 && i != 0)
		{
			ft_printf(CYN"\n%#.4x : "RC, i);
		}
		if (core.map[i] != 0)
			ft_printf(BLU);
		if (core.map[i] < 16)
			ft_printf("0");
		ft_printf("%x "RC, core.map[i]);
		i++;
	}
	ft_printf("\n");
}
