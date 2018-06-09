/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_fill_champ_header.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iosypenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 12:57:38 by iosypenk          #+#    #+#             */
/*   Updated: 2018/05/28 12:57:40 by iosypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void			init_header(t_assm *assm)
{
	char	header[HEADER_SIZE];

	lseek(assm->fd_cor, 0, SEEK_SET) < 0 ? error(assm, 16) : 0;
	ft_memset(header, 0, HEADER_SIZE);
	write(assm->fd_cor, header, HEADER_SIZE);
}

static void			write_magic(t_assm *assm)
{
	lseek(assm->fd_cor, 0, SEEK_SET) < 0 ? error(assm, 16) : 0;
	write(assm->fd_cor, (char*)&assm->header.magic, 4);
}

static void			write_cmd_string(int fd_cor, char *smth, int buffsize)
{
	char	buff[buffsize];

	ft_memcpy(buff, smth, ft_strlen(smth));
	write(fd_cor, (char *)buff, ft_strlen(smth));
}

void				fill_champ_header(t_assm *assm)
{
	init_header(assm);
	write_magic(assm);
	write_cmd_string(assm->fd_cor, assm->header.prog_name, PROG_NAME_LENGTH);
	lseek(assm->fd_cor, COMMENT_POS, SEEK_SET) < 0 ? error(assm, 16) : 0;
	write_cmd_string(assm->fd_cor, assm->header.comment, COMMENT_LENGTH);
}
