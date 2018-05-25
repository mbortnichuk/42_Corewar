/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_writer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbortnic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/13 14:21:45 by mbortnic          #+#    #+#             */
/*   Updated: 2018/05/25 03:00:34 by mbortnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		mb_convert_endian(int b)
{
	b = ((b >> 24) & 0xff) | ((b >> 8) & 0xff00) | ((b << 8) & 0xff0000) |
	((b << 24) & 0xff000000);
	return (b);
}

int		mb_convert_endian2(int b)
{
	b = ((b >> 8) & 0xff) | ((b << 8) & 0xff00);
	return (b);
}

int		mb_create_header(int file_descr, t_header *head)
{
	int	i;

	i = 0;
	head->magic = mb_convert_endian(head->magic);
	write(file_descr, &head->magic, 4);
	while (head->prog_name[i])
		write(file_descr, &head->prog_name[i++], 1);
	while (i++ < PROG_NAME_LENGTH)
		write(file_descr, "\0", 1);
	g_indx = mb_convert_endian(g_indx);
	write(file_descr, "\0\0\0\0", 4);
	write(file_descr, &g_indx, 4);
	i = 0;
	while (head->comment[i])
		write(file_descr, &head->comment[i++], 1);
	while (i++ < COMMENT_LENGTH + 4)
		write(file_descr, "\0", 1);
	return (1);
}

static char	*mb_create_cor(char *champion)
{
	int		i;
	char	*line;

	i = 0;
	line = malloc(sizeof(char*) * (ft_strlen(champion) + 3));
	while (champion[i])
	{
		line[i] = champion[i];
		i++;
	}
	line[i - 1] = 'c';
	line[i] = 'o';
	line[++i] = 'r';
	line[++i] = '\0';
	return (line);
}

int		mb_reader(t_lab *lab, t_header *head, char *champion, char *inp_file)
{
	char	*name_of_file;
	int		file_descr;
	
	inp_file = NULL;
	lab = NULL;
	head = NULL;
	file_descr = 0;
	name_of_file = mb_create_cor(champion);
	if ((file_descr = open(name_of_file, O_RDWR | O_CREAT | O_TRUNC |
		O_APPEND, 0777)) > -1)
	{
		// mb_create_header(file_descr, head);
		g_indx = 0;
		// mb_create_bin(file_descr, lab, inp_file);
	}
	ft_printf(GRN"Writing output program to %s\n"RC, name_of_file);
	ft_printf(GRN BOLD"OK\n"RC);
	free(name_of_file);
	close(file_descr);
	return (1);
}
