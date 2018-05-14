/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mb_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbortnic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 11:24:15 by mbortnic          #+#    #+#             */
/*   Updated: 2018/05/14 11:24:16 by mbortnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int main(int ac, char const **av)
{
	int		id;
	int		ch;
	t_header	*head;

	id = 1;
	ch = 0;
	head = NULL;
	mb_globalvar_initiation();
	if (ac > 1)
	{
		if (av[id][0] == '-' && av[id][1] == 'b' && ++id)
			ch = mb_check_arguments(ac);
		while (id < ac)
		{
			head = mb_asmheader_initiation();
			// if (mb_asm_parse(av[id++], head, ch) == -1)
			// 	ft_putstr("Please insert one valid champ.\n");
			id++;
			free(head);
			head = NULL;
		}
	}
	else
		ft_putstr("You need to put one champ please.\n");
	return (0);
}
