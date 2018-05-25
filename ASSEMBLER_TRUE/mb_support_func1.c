/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mb_support_func1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbortnic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 11:44:27 by mbortnic          #+#    #+#             */
/*   Updated: 2018/05/25 04:26:47 by mbortnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** Free label list.
*/

int			mb_free_label_lst(t_lab *lab)
{
	t_lab	*next;

	next = lab->next;
	while (next)
	{
		lab->next = NULL;
		free(lab->name);
		free(lab);
		lab = next;
		next = lab->next;
	}
	free(lab->name);
	free(lab);
	return (1);
}

/*
** Return 1 if header is ok, if not ok - 0 and then error.
*/

int			mb_return_header(char *str, t_header *header)
{
	if (header->comment[0] && header->prog_name[0])
	{
		if (ft_strrchr(str, '"') != ft_strchr(str, '"'))
		{
			free(str);
			str = NULL;
			return (1);
		}
		return (mb_error(13));
	}
	return (0);
}

char		*mb_realloc(char *inp_file, char *str, int i)
{
	char	*sub_str;
	char	*temporary;
	int		length;

	length = 0;
	temporary = NULL;
	sub_str = NULL;
	sub_str = ft_strsub(str, i, ft_strlen(str) - i);
	temporary = malloc(sizeof(char) * (ft_strlen(inp_file) + ft_strlen(sub_str) + 1));
	temporary = ft_strcpy(temporary, inp_file);
	temporary = ft_strcat(temporary, sub_str);
	free(inp_file);
	free(sub_str);
	inp_file = NULL;
	sub_str = NULL;
	while (temporary[length])
		length++;
	temporary[length] = '\n';
	temporary[length + 1] = '\0';
	inp_file = ft_strdup(temporary);
	free(temporary);
	return (inp_file);
}

/*
** Free table.
*/

/*int			mb_free_table(char **tab, int ret)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			i++;
			free(tab[i - 1]);
		}
		free(tab);
	}
	return (ret);
}*/

int			mb_calc_i(t_lab *lab, char *inp_file)
{
	size_t	length;

	length = 0;
	while (ft_strchr(LABEL_CHARS, inp_file[length]))
		length++;
	while (lab)
	{
		if (length >= ft_strlen(lab->name))
		{
			if (!ft_strncmp(inp_file, lab->name, length))
				return (lab->index - g_indx);
		}
		else if (!ft_strncmp(inp_file, lab->name, ft_strlen(lab->name)))
			return (lab->index - g_indx);
		lab = lab->next;
	}
	return (mb_error(12));
}

/*
** Function that realloc to retrieve the entire .s file.
*/

char		*mb_join_free(char *inp_file, char *str)
{
	char	*sub_str;
	int		length;
	int		i;

	i = 0;
	sub_str = NULL;
	if (str[i])
	{
		if (!(length = 0) && !inp_file)
		{
			sub_str = ft_strsub(str, i, ft_strlen(str) - i);
			inp_file = malloc(sizeof(char) * (ft_strlen(sub_str) + 1));
			inp_file = ft_strcpy(inp_file, sub_str);
			while (inp_file[length])
				length++;
			inp_file[length] = '\n';
			inp_file[length + 1] = '\0';
			free(sub_str);
			sub_str = NULL;
		}
		else
			inp_file = mb_realloc(inp_file, str, i);
	}
	return (inp_file);
}
