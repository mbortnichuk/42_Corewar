/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbortnic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 14:37:04 by mbortnic          #+#    #+#             */
/*   Updated: 2018/05/25 03:00:03 by mbortnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		main(int argc, char **argv)
{
	int			position; //index
	t_header	*header;

	position = 1;
	header = NULL;
	mb_init_glob();
	if (argc > 1)
	{
		while (position < argc)
		{
			header = mb_init_header();
			if (mb_start_parse(header, argv[position++]) == -1)
				ft_printf("Put here one valid champ, please!\n");
			free(header);
			header = NULL;
			mb_init_glob();
		}
	}
	else
		ft_printf("Put here one champ, please!\n");
	// system("leaks asm");
	return (0);
}
