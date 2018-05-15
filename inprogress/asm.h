/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbortnic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/13 13:25:41 by mbortnic          #+#    #+#             */
/*   Updated: 2018/05/13 13:25:42 by mbortnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "./libft/libft.h"

// # include "op.h"

# define NAME_CMD_STRING	".name"
# define COMMENT_CMD_STRING	".comment"

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3

# define LABEL_CHARS			"abcdefghijklmnopqrstuvwxyz_0123456789"

# define REG_NUMBER				16

# define COMMENT_CHAR			'#'
# define LABEL_CHAR				':'
# define DIRECT_CHAR			'%'
# define SEPARATOR_CHAR			','

# define T_REG					1
# define T_DIR					2
# define T_IND					2
//# define T_IND					4 // in original op.h

/*static const t_op	op_tab[17] =
{
	{0, 0, {0}, 0, 0, 0, 0},
	{"live", 1, {T_DIR}, 1, 10, 0, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, 1, 0},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, 1, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, 1, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, 1, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG},
		6, 6, 1, 0},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
		7, 6, 1, 0},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
		8, 6, 1, 0},
	{"zjmp", 1, {T_DIR}, 9, 20, 0, 1},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25, 1, 1},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25, 1, 1},
	{"fork", 1, {T_DIR}, 12, 800, 0, 1},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, 1, 0},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50, 1, 1},
	{"lfork", 1, {T_DIR}, 15, 1000, 0, 1},
	{"aff", 1, {T_REG}, 16, 2, 1, 0}
};*/

typedef struct s_header	t_header;
typedef struct s_lab t_lab;

struct s_header
{
	unsigned int		magic;
	char				prog_name[PROG_NAME_LENGTH + 1];
	unsigned int		prog_size;
	char				comment[COMMENT_LENGTH + 1];
};

struct s_lab
{
	int		position;
	char	*name;
	struct	s_lab *next;
};

int		g_str;
int		g_position;
int		g_temporary;

/*
** mb_args.c
*/

int		mb_check_arguments1(char **str, int op);
int		mb_check_arguments2(char **str, int op);


/*
** mb_check.c
*/

int		mb_check_champion(char *c);
int		mb_sepchar_is_correct(char **str);
int		mb_checklabel(char *line);
int		mb_check_duplicate_label(t_lab *lab);
int		mb_check_indirect(char **str, int ch);

/*
** mb_check2.c
*/

int		mb_label_match(t_lab *lab, char *line);
int		mb_directory_check(char **str, int op, int ch);
int		mb_label_exists(t_lab *lab, char *line);
int		mb_check_correct_register(char **str, int ch);
int		mb_checkline(char *str);

/*
** mb_header.c
*/

int		mb_move_header(char *str, int name, int comment, int ch);
int		mb_move_header_end(char *str, int i);
int		mb_handle_name_comm(int file_descr, t_header *header);

/*
** mb_header2.c
*/

t_header	*mb_header_cpy(char *str, t_header *header, int ch);
int		mb_name_comm_cpy(char *str, t_header *header, int n, int c);
int		mb_return_header(t_header *header, char *str);

/*
** mb_operation_name.c
*/

int		mb_oper_name1(char *str);
int		mb_oper_name2(char *str);
int		mb_error1(int er);
int		mb_error2(int er);

/*
** mb_parse.c
*/

int		mb_parse(char *champ, t_header *header/*, int ch*/);

/*
** mb_parse2.c
*/

char	*mb_putline_infile(char *str, int i, char *f);
t_lab	*mb_parseline(int file_descr, char **file);

/*
** mb_support_func.c
*/

t_lab	*mb_asmlabel_initiation(t_lab *lab, char *str);
int		mb_asmlabel_free(t_lab *lab);
void	mb_globalvar_initiation(void);
int		mb_check_arguments(int ac);
t_header	*mb_asmheader_initiation(void);

/*
** mb_support_func2.c
*/

char	*mb_realloc(char *str, char *file, int i);
char	*mb_freejoin(char *str, char *file);
int		mb_tab_free(char **table, int res);
int		ft_strclen(char *str, char c);

#endif
