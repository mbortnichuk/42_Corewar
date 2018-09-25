/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_champ.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iosypenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 15:05:29 by iosypenk          #+#    #+#             */
/*   Updated: 2018/05/07 15:05:33 by iosypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_vm.h"

static unsigned int		get_magic_size(unsigned int b, int slide)
{
	unsigned int size;

	size = 0;
	if (slide == 24)
		(size = b << slide);
	else if (slide == 16)
		(size = b << slide & 0x00ffffff);
	else if (slide == 8)
		(size = b << slide & 0x0000ffff);
	else if (slide == 0)
		(size = b & 0x000000ff);
	return (size);
}

static int				prog_len(t_champ *champ)
{
	int				buff;
	unsigned int	byte_count;

	buff = 0;
	byte_count = 0;
	((lseek(champ->fileinfo.fd, CODE_POS, SEEK_SET)) < 0) ? err(4) : 0;
	while (read(champ->fileinfo.fd, &buff, 1))
		byte_count++;
	if (byte_count == champ->header.prog_size)
		return (1);
	return (0);
}

static void				get_prog_size(int fd, t_champ *champ)
{
	int					i;
	int					slide;
	unsigned char		buff[4];
	unsigned int		b[4];

	((lseek(fd, CODE_SIZE_POS, SEEK_SET)) < 0) ? err(4) : 0;
	((read(fd, buff, 4)) < 0) ? err(4) : 0;
	slide = 24;
	i = 0;
	while (i < 4)
	{
		b[i] = get_magic_size(buff[i], slide);
		slide -= 8;
		i++;
	}
	champ->header.prog_size = b[0] | b[1] | b[2] | b[3];
	if (champ->header.prog_size > CHAMP_MAX_SIZE)
		err_arg(2, champ->fileinfo.filename);
	if (!prog_len(champ))
		err_arg(3, champ->fileinfo.filename);
}

static void				check_magic(int fd, t_champ *champ, t_core *core)
{
	int					i;
	int					slide;
	unsigned char		buff[4];
	unsigned int		b[4];

	((read(fd, buff, 4)) < 0) ? err_arg(1, champ->fileinfo.filename) : 0;
	slide = 24;
	i = 0;
	while (i < 4)
	{
		b[i] = get_magic_size(buff[i], slide);
		slide -= 8;
		i++;
	}
	champ->header.magic = b[0] | b[1] | b[2] | b[3];
	if (champ->header.magic != COREWAR_EXEC_MAGIC)
	{
		err_arg(4, champ->fileinfo.filename);
	}
	init_champ(champ, core);
}

void					parsing_champ(t_core *core, char *argv)
{
	int			fd;
	t_champ		*champ;

	champ = get_last_list(core->champ);
	((fd = open(argv, O_RDONLY)) < 0) ? err_arg(0, argv) : 0;
	check_magic(fd, champ, core);
	champ->fileinfo.fd = fd;
	champ->fileinfo.filename = ft_strdup(argv);
	if ((read(fd, champ->header.prog_name, PROG_NAME_LENGTH + 1)) < 0)
		err_arg(1, argv);
	!ft_strcmp(champ->header.prog_name, "") ? err_arg(5, argv) : 0;
	((lseek(fd, COMMENT_POS, SEEK_SET)) < 0) ? err(4) : 0;
	if ((read(fd, champ->header.comment, COMMENT_LENGTH + 1)) < 0)
		err_arg(1, argv);
	(!ft_strcmp(champ->header.comment, "")) ? err_arg(6, argv) : 0;
	get_prog_size(champ->fileinfo.fd, champ);
}
