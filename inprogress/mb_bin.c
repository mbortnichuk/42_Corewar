/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mb_bin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbortnic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 19:38:47 by mbortnic          #+#    #+#             */
/*   Updated: 2018/05/15 19:38:48 by mbortnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	*mb_filemove(int fc, char *f)
{
	if (fc == 1 || fc == 9 || fc == 12 || fc == 14)
		f = f + 4;
	else if (fc == 2 || fc == 3 || fc == 7)
		f = f + 2;
	else if (fc == 15)
		f = f + 5;
	else
		f = f + 3;
	while (*f && (*f == ' ' || *f == '\t'))
		f++;
	return (f);
}

int		mb_move_sepchar(char **f)
{
	while (**f && **f != SEPARATOR_CHAR && **f != '\n')
		(*f)++;
	if (**f == '\n')
		return (1);
	(*f)++;
	while (**f && (**f == ' ' || **f == '\t'))
		(*f)++;
	return (1);
}

int		mb_put_register(int file_descr, char **f)
{
	int i;

	i = 0;
	if (**f != 'r')
		return (0);
	i = ft_atoi(++(*f));
	write(file_descr, &i, T_REG);
	g_temporary = g_temporary + T_REG;
	mb_move_sepchar(f);
	return (1);
}

int		mb_put_indirect(int file_descr, t_lab *lab, char **f)
{
	int length;
	int i;

	length = 0;
	i = 0;
	if (**f == LABEL_CHAR && (*f)++)
		i = mb_calc_i(*f, lab);
	else
		i = ft_atoi(*f);
	i = mb_convert_endian2(i);
	write(file_descr, &i, T_IND);
	g_temporary = g_temporary + T_IND;
	mb_move_sepchar(f);
	return (1);
}

int		mb_put_directory(int file_descr, int sz, t_lab *lab, char **f)
{
	int length;
	int i;

	length = 0;
	if (!(i = 0) && **f !=DIRECT_CHAR)
		return (0);
	if (++(*f) && **f == LABEL_CHAR && (*f)++)
		i = mb_calc_i(*f, lab);
	else
		i = ft_atoi(*f);
	if (sz == 4)
		i = mb_convert_endian1(i);
	else
		i = mb_convert_endian2(i);
	write(file_descr, &i, sz);
	g_temporary = g_temporary + sz;
	mb_move_sepchar(f);
	return (1);
}
