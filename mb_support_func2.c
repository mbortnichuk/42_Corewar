/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mb_support_func2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbortnic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 16:49:45 by mbortnic          #+#    #+#             */
/*   Updated: 2018/05/10 16:49:46 by mbortnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		mb_hasname(t_file *f)
{
	if (!(f->hasname))
		return (0);
	return (1);
}

int		mb_only_whtspace(char *str) // return here to ++i; if in process some troubles will occur
{
	register size_t i;
	/* 'register' suggests to store a size_t variable "i" 
	in a CPU register or another fast location, when 'default size_t i' 
	will store  this variable in RAM, register or other location
	as compiler sees fit and based on how variable is used */

	i = -1; // i = 0;
	while (str[++i] != '\0') //remove ++i;
	{
		if (!ft_isspace(str[i]))
			return (0);
		// add here ++i;
	}
	return (1);
}

int		mb_iscomment(t_str *str)
{
	register size_t	i;

	i = 0;
	while (str->line && (str->line)[i] && ft_isspace((str->line)[i]))
		++i;
	if ((str->line)[i] == COMMENT_CHAR)
	{
		str->type = COMMENT;
		return (true);
	}
	return (false);
}

void	mb_asm_err(char *s)
{
	mb_putstr_col(s, LRED);
	exit(EXIT_FAILURE);
}

size_t	mb_str_position(char *str, int c)
{
	register size_t i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == (char)c)
			return (i);
		++i;
	}
	return (-1);
}
