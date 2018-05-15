/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mb_support_func2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbortnic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 10:02:26 by mbortnic          #+#    #+#             */
/*   Updated: 2018/05/15 10:02:27 by mbortnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** Function thar reallocate memory to retrieve the entire .s file.
*/

char	*mb_realloc(char *str, char *file, int i)
{
	char	*substr;
	char	*temp;
	int		length;

	substr = NULL;
	temp = NULL;
	length = 0;
	substr = ft_strsub(str, i, ft_strlen(str) - i);
	temp = malloc(sizeof(char) * (ft_strlen(file) + ft_strlen(substr) + 1));
	temp = ft_strcpy(temp, file);
	temp = ft_strcat(temp, substr);
	free(file);
	free(substr);
	file = NULL;
	substr = NULL;
	while (temp[length])
		length++;
	temp[length] = '\n';
	temp[length + 1] = '\0';
	file = ft_strdup(temp);
	free(temp);
	return (file);
}

char	*mb_freejoin(char *str, char *file)
{
	char	*substr;
	int i;
	int length;

	i = 0;
	substr = NULL;
	if (str[i])
	{
		if (!(length = 0) && !file)
		{
			substr = ft_strsub(str, i, ft_strlen(str - i));
			file = malloc(sizeof(char) * (ft_strlen(substr) + 1));
			file = ft_strcpy(file, substr);
			while (file[length])
				length++;
			file[length] = '\n';
			file[length + 1] = '\0';
			free(substr);
			substr = NULL;
		}
		else
			file = mb_realloc(str, file, i);
	}
	return (file);
}

int		mb_tab_free(char **table, int res)
{
	int i;

	i = 0;
	if (table)
	{
		while (table[i])
		{
			i++;
			free(table[i - 1]);
		}
		free(table);
	}
	return (res);
}

int		ft_strclen(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != c)
		i++;
	return (i);
}
