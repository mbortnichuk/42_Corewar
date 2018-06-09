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

static char		*mb_create_cor(char *champion)
{
	int			i;
	char		*line;

	i = 0;
	line = ft_strnew((ft_strlen(champion) + 3));
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

static void		mb_reader(t_assm *assm, char *champion)
{
	char		*file_name;

	assm->esc == 1 ? exit(0) : 0;
	file_name = mb_create_cor(champion);
	assm->fd_cor = open(file_name, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
	if (assm->fd_cor > -1)
	{
		assm->args_count = 0;
		assembler(assm);
	}
	ft_printf(GRN"Writing output program to %s\n", file_name);
	ft_printf(BOLD"OK\n"RC);
	ft_strdel(&file_name);
	close(assm->fd_cor);
	close(assm->fd_s);
}

static int		mb_champion_check(t_assm *assm, char *champion)
{
	int		j;

	j = 0;
	while (champion[j])
		j++;
	if (j > 3 && champion[j - 1] == 's' && champion[j - 2] == '.')
		return (1);
	else
		return (error(assm, 14));
}

static int		mb_start_parse(t_assm *assm, char *champ)
{
	char	*buff;
	char	*line;
	char	*tmp;

	buff = NULL;
	tmp = NULL;
	mb_champion_check(assm, champ);
	if ((assm->fd_s = open(champ, O_RDONLY)) == -1)
		return (-1);
	io_save_header_info(assm, &buff);
	mb_parse_str(assm, &buff, &line, &tmp);
	mb_check_label_duplicate(assm, assm->lab_lst);
	if (mb_label_exist(assm, &buff) == 0)
		return (error(assm, 12));
	mb_reader(assm, champ);
	if (buff && buff[0])
		ft_strdel(&buff);
	return (0);
}

int				main(int argc, char **argv)
{
	t_assm		assm;

	if (argc > 1)
	{
		assm.count = 0;
		assm.args_count = 0;
		assm.lab_lst = NULL;
		assm.esc = 0;
		assm.push = 0;
		assm.header.magic = magic(COREWAR_EXEC_MAGIC);
		ft_memset(assm.header.prog_name, 0, PROG_NAME_LENGTH + 1);
		ft_memset(assm.header.comment, 0, COMMENT_LENGTH + 1);
		if (mb_start_parse(&assm, argv[1]) == -1)
			error(&assm, 16);
	}
	else
		ft_printf(YEL"Usage: ./asm filename.s\n"RC);
	return (0);
}
