/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbortnic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 14:36:58 by mbortnic          #+#    #+#             */
/*   Updated: 2018/05/06 14:36:59 by mbortnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "libft/libft.h"
# include "op.h"

# include <stdbool.h>

# define RC "\033[0m"
# define RED "\033[22;31m"
# define LRED "\033[1;31m"
# define GR "\033[22;32m"

# define FCOL(i, j) mb_putstr_col(i, j);
# define RET_ERR(i, j) {FCOL("ERROR: ", RED); FCOL(i, LRED); return (j);}

// # define LABLE_SIZE 2

// # define VERBOSE_OPT 1
// # define LEAKS_OPT 2

# define LAST_COMMENT_CHR ';'

# define STR	((t_str*)(temp->content))
# define SYMBOL ((t_symbol*)(temp->content))

enum error
{
	TOO_MANY_PAR = 0, 
	NOT_ENOUGHT_PAR
};

enum symbol
{
	UNKNWN = 0,
	COMMAND_NAME,
	COMMAND_COMMENT,
	COMMENT,
	EXECUTABLE,
	SLINE,
	LABEL,
	INSTRUCT,
	ARG_REG = 9,
	ARG_DIR = 10,
	ARG_IND = 12,
	ARG_INDLAB,
	ARG_DLAB
};


// enum e_errortype
// {
// 	TOO_MANY_PAR = 0, 
// 	NOT_ENOUGHT_PAR
// } error;

// enum e_symboltype
// {
// 	UNKNWN = 0,
// 	COMMAND_NAME,
// 	COMMAND_COMMENT,
// 	COMMENT,
// 	EXECUTABLE,
// 	SLINE,
// 	LABEL,
// 	INSTRUCT,
// 	ARG_REG = 9,
// 	ARG_DIR = 10,
// 	ARG_IND = 12,
// 	ARG_INDLAB,
// 	ARG_DLAB
// } symbol;

typedef struct s_symbol t_symbol;
typedef struct s_str t_str;
typedef struct s_file t_file;
typedef struct s_op	t_op;

struct s_symbol
{
	char	*line;
	int		val;
	size_t	id;
	t_op	*op;
	enum symbol type;
};

struct s_str
{
	enum symbol type;
	size_t	param_nbr;
	char	*line;
	size_t	code_size;
	size_t	id;
	char	bytec[14];
	char	codep;
	t_list	*symbols;
};

struct s_file
{
	int		ret_res;
	int		fds;
	int		fdcor;
	size_t	line_nbr;
	size_t	hasname;
	int		opt;
	t_header	header;
	t_list	*strs;
	char	*s_name;
	char	*cor_name;
};

// struct s_op
// {
// 	char	*name;
// 	int		param_nbr;
// 	int		param_type[4];
// 	int		opcode;
// 	int		cycle_nbr;
// 	char	*descr;
// 	int		is_pcode;
// 	int		has_id;
// };

struct		s_op
{
	char	*name;
	int		args_nb;
	int		arg[3];
	int		opcode;
	int		cycles_cost;
	char	codage;
	char	dir_siz;
};

/*
** mb_asm.h
*/

void	mb_check_asm_arg(/*t_file *f, */int argc, char *argv[]);

/*
** mb_support_func.c
*/

void	mb_putstr_col(char *str, char *col);
int		mb_haslabel(char *line);

/*
** mb_support_func2.c
*/

int		mb_hasname(t_file *f);
int		mb_only_whtspace(char *str);
int		mb_iscomment(t_str *str);
void	mb_asm_err(char *s);

/*
** mb_checkup.c
*/

int		mb_has_valid_parameter(t_str *str);
int		mb_check_valid_param(t_symbol *symbol, char *str);
void	mb_check_valid_comment(t_file *f, t_str *str);
void	mb_check_valid_name(t_file *f, t_str *str);

/*
** mb_mainread.c
*/

int		mb_readfile(t_file *f);
int		mb_addline(t_file *f, char *line, size_t *i, int haslabel);

/*
** mb_parsing.c
*/

int		mb_parsefile(t_file *f);

/*
** mb_initiation.c
*/

void	mb_initfile(t_file *f);
int		mb_initline(t_file *f, char *line, size_t i, int linetype);


#endif
