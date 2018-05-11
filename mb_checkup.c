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

extern	const t_op op_tab[17]; /* 'extern' keyword is used to extend
						the visibility of variables/functions/structures.
						'extern' ініціалізує, в нашому випадку t_op, і вказує на те, 
						що вона має зовнішні компонування (її ім'я буде видимим не тільки 
						в межах файлу, в якому вона ініціалізована, а й в інших файлах).
						Коли виконується зміна t_op, ключове слово 'extern' означає, що вона має 
						статичну властивість - виділяється на початку запуску програми 
						і вивільняється при її закінченні. */

int		mb_has_valid_parameter(t_str *str)
{
	int		new_t; //new type
	size_t	nbr;
	size_t	instance;
	t_list	*temp;

	if (!(temp = str->symbols))
		return (1);
	instance = SYMBOL->op->opcode; // from here check in progress if structure element has changed;
	if (OPTAB.args_nb != (int)str->param_nbr)
		RET_ERR("Incorrect parameters number for the instance.\n", 0);
	if (!(temp->next))
		return (0);
	temp = temp->next;
	nbr = 0;
	while (temp || (int)nbr < OPTAB.args_nb)
	{
		new_t = (SYMBOL->type == ARG_DLAB ? 2 : SYMBOL->type - 8);
		new_t = (new_t == ARG_INDLAB - 8 ? 4 : new_t);
		if (new_t & ~OPTAB.arg[nbr]) /*tilda '~' in C-like languages 
					 performs as a bitwise NOT operation - all the 1 bits in the
					 operand are set to 0 and all the 0 bits in the operand
					 are set to 1. In other words, it creates the complement 
					 of the original number.
					 For example:
					 10101000 11101001 // Original  (Binary for -22,295 in 16-bit two's complement)
					 01010111 00010110 // ~Original (Binary for  22,294 in 16-bit two's complement) */
			return (0);
		temp = temp->next;
		++nbr;
	}
	return (1);
}

int		mb_check_valid_param(t_symbol *symbol, char *str)
{
	register size_t i;
	char	*checkup;

	checkup = LABEL_CHARS;
	i = 0;
	if (symbol->type == LABEL || symbol->type == ARG_DLAB || \
		symbol->type == ARG_INDLAB)
	{
		while (str[i])
		{
			if (!ft_strchr(LABEL_CHARS, str[i]) && \
				!(i == 0 && str[i] == DIRECT_CHAR) && \
				!((i == 0 || i == 1) && str[i] == LABEL_CHAR))
				RET_ERR("Incorrect char used in label.\n", EXIT_FAILURE);
			++i;
		}
		return (EXIT_SUCCESS);
	}
	else if (symbol->type == ARG_REG)
	{
		if (ft_atoi(symbol->line + 1) > REG_NUMBER)
			RET_ERR("Register number is too big.\n", EXIT_FAILURE);
	}
	return (EXIT_SUCCESS); /* 'EF' unsuccessful execution of a program;
						'ES' successful execution of a program. 
						in this case usage of "exit(1 or 0)" is non-portable. */
}

void	mb_check_valid_comment(t_file *f, t_str *str)
{
	int		empty;
	int		name_beginning;
	int		name_ending;
	char	*line;

	empty = 0;
	while (ft_isspace((str->line)[empty]))
		++empty;
	line = str->line + empty;
	if (ft_strncmp(line, COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING)) == 0)
	{
		str->type = COMMAND_COMMENT;
		name_beginning = ft_strlen(COMMENT_CMD_STRING);
		while (line && line[name_beginning] && line[name_beginning] != '"')
			++name_beginning;
		++name_beginning;
		name_ending = name_beginning;
		while (line && line[name_ending] && line[name_ending] != '"')
			++name_ending;
		ft_strncpy(f->header.comment, (const char*)line + name_beginning, name_ending - name_beginning);
	}
	return ;
}

void	mb_check_valid_name(t_file *f, t_str *str)
{
	int		empty;
	int		name_beginning;
	int		name_ending;
	char	*line;

	empty = 0;
	while (ft_isspace((str->line)[empty]))
		++empty;
	line = str->line + empty;
	if (ft_strncmp(line, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)) == 0)
	{
		f->hasname = 1;
		str->type = COMMAND_NAME;
		name_beginning = ft_strlen(NAME_CMD_STRING);
		while (line && line[name_beginning] && line[name_beginning] != '"')
			++name_beginning;
		++name_beginning;
		name_ending = name_beginning;
		while (line && line[name_ending] && line[name_ending] != '"')
			++name_ending;
		ft_strncpy(f->header.prog_name, (const char*)line + name_beginning, name_ending = name_beginning);
	}
	return ;
}
