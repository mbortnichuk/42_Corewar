/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_check_lines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iosypenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 17:15:24 by iosypenk          #+#    #+#             */
/*   Updated: 2018/05/30 17:15:25 by iosypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			not_cmd(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]) && line[i] != '#' && line[i] != ';')
			return (1);
		if (line[i] == '#' || line[i] == ';')
			return (0);
		i++;
	}
	return (0);
}

void		check_new_line(t_assm *assm, char *line, int z)
{
	if (line == NULL || count_quote(line) > 1 ||
		(z == 1 && ft_strstr(line, COMMENT_CMD_STRING)) ||
		(z == 2 && ft_strstr(line, NAME_CMD_STRING)) ||
		((ft_strchr(line, '"') && line[ft_strlen(line) - 1] != '"')))
	{
		error(assm, 17);
	}
}

void		first_check(t_assm *assm, char *line, int z, int n)
{
	if ((n == 2 && line[ft_strlen(line) - 1] != '"') ||
		before_str(line, z))
	{
		error(assm, 17);
	}
}

int			before_str(char *line, int z)
{
	int		size;
	int		size2;
	int		i;

	size = 0;
	if (z == 1)
		size = ft_strlen(NAME_CMD_STRING) + (ft_strlen(line) -
			ft_strlen(ft_strstr(line, NAME_CMD_STRING)));
	if (z == 2)
		size = ft_strlen(COMMENT_CMD_STRING) + (ft_strlen(line) -
			ft_strlen(ft_strstr(line, COMMENT_CMD_STRING)));
	size2 = ft_strlen(line + size) - ft_strlen(ft_strchr(line + size, '"'));
	i = 0;
	while ((line + size)[i] && i < size2)
	{
		if (!ft_isspace((line + size)[i]))
			return (1);
		i++;
	}
	return (0);
}

int			before_cmd(char *line)
{
	char	*tmp;
	int		size;
	int		i;

	tmp = NULL;
	if (ft_strstr(line, NAME_CMD_STRING))
		tmp = NAME_CMD_STRING;
	else if (ft_strstr(line, COMMENT_CMD_STRING))
		tmp = COMMENT_CMD_STRING;
	if (!tmp)
		return (0);
	size = ft_strlen(line) - ft_strlen(ft_strstr(line, tmp));
	i = 0;
	while (line[i] && i < size)
	{
		if (!ft_isspace(line[i]))
			return (0);
		i++;
	}
	return (1);
}
