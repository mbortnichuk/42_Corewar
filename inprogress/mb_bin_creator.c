/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mb_bin_creator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbortnic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 15:31:16 by mbortnic          #+#    #+#             */
/*   Updated: 2018/05/15 15:31:17 by mbortnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	*mb_create_cor(char	*champion)
{
	int		i;
	char	*cor;

	i = 0;
	if (!(cor = malloc(sizeof(char *) * (ft_strlen(champion) + 3))))
		return (NULL);
	while (champion[i])
	{
		cor[i] = champion[i];
		i++;
	}
	cor[i - 1] = 'c';
	cor[i] = 'o';
	cor[++i] = 'r';
	cor[++i] = '\0';
	return (cor);
}

int		mb_create_header(int file_descr, t_header *head)
{
	int i;

	i = 0;
	head->magic = mb_convert_endian1(head->magic);
	write(file_descr, &head->magic, 4);
	while (head->prog_name[i])
		write(file_descr, &head->prog_name[i++], 1);
	while (i++ < PROG_NAME_LENGTH)
		write(file_descr, "\0", 1);
	g_position = mb_convert_endian1(g_position);
	// write(file_descr, "\0\0\0\0", 4);
	ft_putstr_fd("\0\0\0\0", file_descr);
	write(file_descr, &g_position, 4);
	i = 0;
	while (head->comment[i])
		write(file_descr, &head->comment[i++], 1);
	while (i++ < COMMENT_LENGTH + 4)
		write(file_descr, "\0", 1);
	return (1);
}

int		mb_opcode(int file_descr, int argument, int i, char *f)
{
	int		oct_out;
	int		oct_in;

	oct_in = 0;
	oct_out = 0;
	mb_set_opcode(&oct_out, i, 1, f);
	oct_in = (oct_in | oct_out);
	if (argument > 1)
	{
		i = mb_move_i(i, f);
		mb_set_opcode(&oct_out, i, 1, f);
		oct_in = (oct_in | oct_out);
	}
	if (argument > 2)
	{
		i = mb_move_i(i, f);
		mb_set_opcode(&oct_out, i, 3, f);
		oct_in = (oct_in | oct_out);
	}
	g_temporary++;
	write(file_descr, &oct_in, 1);
	return (1);
}

int		mb_bin_create(int file_descr, t_lab *lab, char *f)
{
	int	fc;

	fc = 0;
	while (*f)
	{
		fc = mb_oper_name2(f);
		if (fc)
			g_temporary++;
		mb_scary_func_name2(fc, file_descr, lab, &f);
		while (*f && *f != '\n')
			f++;
		f++;
		g_position = g_position + g_temporary;
		g_temporary = 0;
	}
	return (1);
}

int		mb_creator(t_lab *lab, t_header *head, char *champion, char *f)
{
	char	*name;
	int		file_descr;

	file_descr = 0;
	name = mb_create_cor(champion);
	if ((file_descr = open(name, O_RDWR | O_CREAT | O_TRUNC | O_APPEND, 0777)) > -1)
	{
		mb_create_header(file_descr, head); // it's supposed to be written soon enough
		g_position = 0;
		mb_bin_create(file_descr, lab, f);
	}
	ft_printf("Writing output program to %s\n", name);
	free(name);
	close(file_descr);
	return (1);
}
