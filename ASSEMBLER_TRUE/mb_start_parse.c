/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mb_start_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbortnic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 10:02:26 by mbortnic          #+#    #+#             */
/*   Updated: 2018/05/25 04:26:30 by mbortnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** Check is the file ends with .s
*/

static int			mb_champion_check(char *champion)
{
	int j;

	j = 0;
	while (champion[j])
		j++;
	if (j > 3 && champion[j - 1] == 's' && champion[j - 2] == '.')
		return (1);
	else
		return (mb_error(14));
}

/*
** Put the valid line in array.
*/

static char		*mb_putline_infile(char *str, char *inp_file, int i)
{
	while (str[i] == '\t' || str[i] == ' ')
		i++;
	if (str[i] && str[i] != COMMENT_CHAR && str[i] != ';' &&
	mb_valid_line_check(&str[i]))
		inp_file = mb_join_free(inp_file, &str[i]);
	free(str);
	str = NULL;
	return (inp_file);
}

/*
** Retrieve the name of the label, position in a chained list.
*/

static t_lab		*mb_parse_str(char **inp_file, int file_descr)
{
	int		i;
	char	*str;
	t_lab	*lab;

	lab = NULL;
	str = NULL;
	while (!(i = 0) && get_next_line(file_descr, &str) > 0)
	{
		// ft_printf(MAG"chort! | %s |\n"RC, line);
		// ft_printf(CYN"fd -> %d\n"RC, fd);
		// i = 0;
		g_str++;
		while (str[i] == '\t' || str[i] == ' ')
		{
			// ft_printf(YEL"chto tut,a? %s\n"RC, line);
			// ft_printf(CYN"1 i = %d\n"RC, i);

			i++;
		}
		// ft_printf(CYN"2 i = %d\n"RC, i);
		if (str[i] && str[i] != COMMENT_CHAR && str[i] != ';' &&
			mb_check_valid_label(str) >= 1)
		{
			ft_printf(BLU"AAAA\n");
			// ft_printf(CYN"%s\n"RC, lab->name);
			lab = mb_init_lab(str, lab);
			// ft_printf(CYN"4 i = %d\n"RC, i);
			ft_printf(YEL"AAAA\n"RC);

			while (str[i] != LABEL_CHAR)
				i++;
			i++;
		}
		// ft_printf(CYN"3 i = %d\n"RC, i);
		// while (lab)
		// {
		// 	ft_printf(MAG"lab: | %s |\n"RC, lab->name);
		// 	lab = lab->next;
		// }
		// ft_printf("str -> | %s |\n", str);
		*inp_file = mb_putline_infile(str, *inp_file, i);
		// ft_printf("str -> | %s |\n", str);
	}
	// free(str);
	return (lab);
}

/*
** Start of parsing.
*/

int			mb_start_parse(t_header *header, char *champ)
{
	int			id;
	t_lab		*lab;
	int			file_descr;
	char		*inp_file;

	lab = NULL;
	id = 0;
	inp_file = NULL;
	mb_champion_check(champ);
	if ((file_descr = open(champ, O_RDONLY, 0555)) == -1)
		return (-1);
	mb_handle_name_comm(header, file_descr);
	ft_printf(MAG"ZASHLO?\n"RC);
	lab = mb_parse_str(&inp_file, file_descr);
	ft_printf(MAG"VUJSHLO?\n"RC);
	// ft_printf("HZ -> | %s |\n", lab->name);
	// ft_printf(RED"ggggg %s\n"RC, inp_file);
	mb_check_label_duplicate(lab);
	if (mb_label_exist(inp_file, lab) == 0)
		return (mb_error(12));
	mb_reader(lab, header, champ, inp_file);
	if (inp_file && inp_file[0])
		free(inp_file);
	if (lab)
		mb_free_label_lst(lab);
	return (0);
}
