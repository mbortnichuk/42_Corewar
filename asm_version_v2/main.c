/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbortnic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 00:02:38 by mbortnic          #+#    #+#             */
/*   Updated: 2018/05/18 00:02:39 by mbortnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		main(int ac, char **av)
{
	char	*print;
	int		res;

	if (ac < 2 || ac > 3)
		return (mb_err("You need to put one champion, please.\nUsage: ./asm [filename.s]", 1));
	if (!(print = mb_checkfile(av[1])))
		return (mb_err("Sorry, cannot read source file as program argument.", 1));
	if ((res = mb_creator(av[1], print)))
		return (mb_del(res));
	ft_printf("Writing output program to ", print);
	ft_strdel(&print);
	return (mb_del(0));
	return (0);
}
