/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ok.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbortnic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 14:03:46 by mbortnic          #+#    #+#             */
/*   Updated: 2018/05/15 14:03:48 by mbortnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			asm_move_my_i(int i, char *file)
{
	while (file[i] != ',')
		i++;
	i++;
	while (file[i] == '\t' || file[i] == ' ')
		i++;
	return (i);
}

int			asm_calculate_i(char *file, t_lab *lab)
{
	size_t	len;

	len = 0;
	while (ft_strchr(LABEL_CHARS, file[len]))
		len++;
	while (lab)
	{
		if (len >= ft_strlen(lab->name))
		{
			if (!ft_strncmp(file, lab->name, len))
				return (lab->position - g_position);
		}
		else if (!ft_strncmp(file, lab->name, ft_strlen(lab->name)))
			return (lab->position - g_position);
		lab = lab->next;
	}
	return (mb_error2(12));
}

void	asm_opcode_assign(int *octout, int i, int check, char *file)
{
	if (check == 1 && file[i] == 'r')
		*octout = 0x40;
	else if (check == 1 && file[i] == '%')
		*octout = 0x80;
	else if (check == 1)
		*octout = 0xC0;
	if (check == 2 && file[i] == 'r')
		*octout = 0x10;
	else if (check == 2 && file[i] == '%')
		*octout = 0x20;
	else if (check == 2)
		*octout = 0x30;
	if (check == 3 && file[i] == 'r')
		*octout = 0x4;
	else if (check == 3 && file[i] == '%')
		*octout = 0x8;
	else if (check == 3)
		*octout = 0xC;
}

int		asm_opcode(int fd, int arg, int i, char *file)
{
	int	octout;
	int	octin;

	octin = 0;
	octout = 0;
	asm_opcode_assign(&octout, i, 1, file);
	octin = (octin | octout);
	if (arg > 1)
	{
		i = asm_move_my_i(i, file);
		asm_opcode_assign(&octout, i, 2, file);
		octin = (octin | octout);
	}
	if (arg > 2)
	{
		i = asm_move_my_i(i, file);
		asm_opcode_assign(&octout, i, 3, file);
		octin = (octin | octout);
	}
	g_temporary++;
	write(fd, &octin, 1);
	return (1);
}

int		asm_write_dir(int fd, int size, t_lab *lab, char **file)
{
	int	i;
	int	len;

	len = 0;
	if (!(i = 0) && **file != DIRECT_CHAR)
		return (0);
	if (++(*file) && **file == LABEL_CHAR && (*file)++)
		i = asm_calculate_i(*file, lab);
	else
		i = ft_atoi(*file);
	if (size == 4)
		i = cw_invert_endian(i);
	else
		i = cw_invert_endian2(i);
	write(fd, &i, size);
	g_temporary = g_temporary + size;
	asm_move_separator(file);
	return (1);
}

int		asm_write_ind(int fd, t_lab *lab, char **file)
{
	int	i;
	int	len;

	len = 0;
	i = 0;
	if (**file == LABEL_CHAR && (*file)++)
		i = asm_calculate_i(*file, lab);
	else
		i = ft_atoi(*file);
	i = cw_invert_endian2(i);
	write(fd, &i, T_IND);
	g_temporary = g_temporary + T_IND;
	asm_move_separator(file);
	return (1);
}

int		asm_write_reg(int fd, char **file)
{
	int	i;

	i = 0;
	if (**file != 'r')
		return (0);
	i = ft_atoi(++(*file));
	write(fd, &i, T_REG);
	g_temporary = g_temporary + T_REG;
	asm_move_separator(file);
	return (1);
}

char	*asm_move_file(int fct, char *file)
{
	if (fct == 1 || fct == 9 || fct == 12 || fct == 14)
		file = file + 4;
	else if (fct == 2 || fct == 3 || fct == 7)
		file = file + 2;
	else if (fct == 15)
		file = file + 5;
	else
		file = file + 3;
	while (*file && (*file == ' ' || *file == '\t'))
		file++;
	return (file);
}

int		asm_move_separator(char **file)
{
	while (**file && **file != SEPARATOR_CHAR && **file != '\n')
		(*file)++;
	if (**file == '\n')
		return (1);
	(*file)++;
	while (**file && (**file == ' ' || **file == '\t'))
		(*file)++;
	return (1);
}

int		asm_call_good_function_sec(int fct, int fd, t_lab *lab, char **file)
{
	if ((fct == 6 || fct == 7 || fct == 8) && asm_opcode(fd, 3, 0, *file)
		&& ((asm_write_reg(fd, file) || asm_write_dir(fd, 4, lab, file) ||
		asm_write_ind(fd, lab, file)) &&
		((asm_write_reg(fd, file) || asm_write_dir(fd, 4, lab, file) ||
		asm_write_ind(fd, lab, file)))))
		return (asm_write_reg(fd, file));
	else if (fct == 9 || fct == 12 || fct == 15)
		return (asm_write_dir(fd, 2, lab, file));
	else if ((fct == 10 || fct == 14) && asm_opcode(fd, 3, 0, *file) &&
		(((asm_write_reg(fd, file) || asm_write_dir(fd, 2, lab, file) ||
		asm_write_ind(fd, lab, file)) &&
		(asm_write_reg(fd, file) || asm_write_dir(fd, 2, lab, file)))))
		return (asm_write_reg(fd, file));
	else if (fct == 11 && asm_opcode(fd, 3, 0, *file) &&
		((asm_write_reg(fd, file) && (asm_write_reg(fd, file) ||
		asm_write_dir(fd, 2, lab, file) || asm_write_ind(fd, lab, file)) &&
		(asm_write_reg(fd, file) || asm_write_dir(fd, 2, lab, file)))))
		return (1);
	else if (fct == 16 && write(fd, "@", 1) && ++g_temporary)
		return (asm_write_reg(fd, file));
	return (1);
}

int		asm_call_good_function(int fct, int fd, t_lab *lab, char **file)
{
	*file = asm_move_file(fct, *file);
	write(fd, &fct, 1);
	if (fct == 1)
		return (asm_write_dir(fd, 4, lab, file));
	else if ((fct == 2 || fct == 13) && asm_opcode(fd, 2, 0, *file) &&
		((asm_write_dir(fd, 4, lab, file) || asm_write_ind(fd, lab, file))))
		return (asm_write_reg(fd, file));
	else if (fct == 3 && asm_opcode(fd, 2, 0, *file) && asm_write_reg(fd, file)
		&& (asm_write_reg(fd, file) || asm_write_ind(fd, lab, file)))
		return (1);
	else if ((fct == 4 || fct == 5) && write(fd, "T", 1) && ++g_temporary &&
		asm_write_reg(fd, file) && asm_write_reg(fd, file) &&
		asm_write_reg(fd, file))
		return (1);
	return (asm_call_good_function_sec(fct, fd, lab, file));
}

int		asm_binary_creator(int fd, t_lab *lab, char *file)
{
	int fct;

	fct = 0;
	while (*file)
	{
		fct = mb_oper_name2(file);
		if (fct)
			g_temporary++;
		asm_call_good_function(fct, fd, lab, &file);
		while (*file && *file != '\n')
			file++;
		file++;
		g_position = g_position + g_temporary;
		g_temporary = 0;
	}
	return (1);
}

int		cw_invert_endian(int x)
{
	x = ((x >> 24) & 0xff) | ((x >> 8) & 0xff00) | ((x << 8) & 0xff0000) |
	((x << 24) & 0xff000000);
	return (x);
}

int		cw_invert_endian2(int x)
{
	x = ((x >> 8) & 0xff) | ((x << 8) & 0xff00);
	return (x);
}

int		asm_header_creator(int fd, t_header *header)
{
	int	i;

	i = 0;
	header->magic = cw_invert_endian(header->magic);
	write(fd, &header->magic, 4);
	while (header->prog_name[i])
		write(fd, &header->prog_name[i++], 1);
	while (i++ < PROG_NAME_LENGTH)
		write(fd, "\0", 1);
	g_position = cw_invert_endian(g_position);
	write(fd, "\0\0\0\0", 4);
	write(fd, &g_position, 4);
	i = 0;
	while (header->comment[i])
		write(fd, &header->comment[i++], 1);
	while (i++ < COMMENT_LENGTH + 4)
		write(fd, "\0", 1);
	return (1);
}

char	*asm_morph_cor(char *champ)
{
	char	*str;
	int		i;

	i = 0;
	str = malloc(sizeof(char*) * (ft_strlen(champ) + 3));
	while (champ[i])
	{
		str[i] = champ[i];
		i++;
	}
	str[i - 1] = 'c';
	str[i] = 'o';
	str[++i] = 'r';
	str[++i] = '\0';
	return (str);
}

int		mb_reader(t_lab *lab, t_header *header, char *champ, char *file)
{
	int		fd;
	char	*file_name;

	fd = 0;
	file_name = asm_morph_cor(champ);
	if ((fd = open(file_name, O_RDWR | O_CREAT | O_TRUNC |
		O_APPEND, 0777)) > -1)
	{
		asm_header_creator(fd, header);
		g_position = 0;
		asm_binary_creator(fd, lab, file);
	}
	ft_printf("Writing output program OK\n");
	free(file_name);
	close(fd);
	return (1);
}
