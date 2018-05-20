/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mb_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbortnic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 01:20:37 by mbortnic          #+#    #+#             */
/*   Updated: 2018/05/18 01:20:39 by mbortnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	*mb_checkfile(char *file)
{
	char	*print;
	char	*ext;

	print = NULL;
	ext = ft_strrchr(file, '.');
	if (!ext)
		return (NULL);
	if (ft_strcmp(ext, ".s"))
		return (NULL);
	print = ft_strnew(ext - file + 4);
	ft_strncpy(print, file, ext - file + 1);
	ft_strncpy(ft_strrchr(print, '.') + 1, "cor", 3);
	return (print);
}

int		mb_start_checklable(void)
{
	t_list	*l;

	l = mb_get_lable_use()->labels;
	while (l)
	{
		if (l->content)
			if (mb_label_id(l->content) == -1)
				return (mb_label_err(l->content, 1));
		l = l->next;
	}
	return (0);
}
