/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mb_checkup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbortnic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 19:42:20 by mbortnic          #+#    #+#             */
/*   Updated: 2018/05/06 19:42:21 by mbortnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#define OPTAB	op_tab[instance - 1]

extern	t_op op_tab[17]; /* 'extern' keyword is used to extend
							the visibility of variables/functions/structures.
							'extern' ініціалізує, в нашому випадку t_op, і вказує на те, 
							що вона має зовнішні компонування (її ім'я буде видимим не тільки 
							в межах файлу, в якому вона ініціалізована, а й в інших  файлах).
							Коли виконується зміна t_op, ключове слово extern означає, що вона має статичну властивість - 
							виділяється на початку запуску програми і звільняється при її закінченні. */

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

int		mb_has_valid_parameter(t_str *str)
{
	int		new_t; //new type
	size_t	nbr;
	size_t	instance;
	t_list	*temp;

	if (!(temp = str->symbols))
		return (1);
	// start from here next time;
}
