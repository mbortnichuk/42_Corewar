/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbortnic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/13 18:10:01 by mbortnic          #+#    #+#             */
/*   Updated: 2018/05/25 02:59:02 by mbortnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <fcntl.h>

# include "../corewar.h"

# define HEADER_SIZE	((4 * SIZE) + PROG_NAME_LENGTH + COMMENT_LENGTH)

typedef struct			s_lab_lst
{
	char				*data;
	int					index;
	struct s_lab_lst	*next;
}						t_lab_lst;

typedef struct			s_assm
{
	int					fd_s;
	int					fd_cor;
	t_header			header;
	t_lab_lst			*lab_lst;
	t_lab_lst			*line_lst;
	unsigned int		inst_n;
	unsigned int		args_count;
	int					count;
	unsigned int		arg_type;
	unsigned int		codage;
	unsigned int		codage_pos;
	int					inst_pos;
	unsigned int		magic;
	unsigned int		push;
	int					esc;
	char				*line;
	int					line_nb;
}						t_assm;

void					reader(t_assm *assm, char *champion);

void					assembler(t_assm *assm);

/*
**	The assembler functions:
*/

void					io_save_header_info(t_assm *assm, char **buff);
void					fill_champ_header(t_assm *assm);

int						is_label(char *line);
int						is_instr_nbr(char *line);

void					parse_champ_code(t_assm *assm);

void					push_args(t_assm *assm, char *line);

unsigned int			magic(unsigned int s);
unsigned int			magic_2(unsigned int s);
int						get_size(t_assm *assm);
void					get_codage(t_assm *assm);
int						get_label_pos(t_assm *assm, char *line);

int						count_quote(char *line);
int						not_cmd(char *line);
void					check_new_line(t_assm *assm, char *line, int z);
void					first_check(t_assm *assm, char *line, int z, int n);
int						before_str(char *line, int z);
int						before_cmd(char *line);

void					io_create_lab_lst(t_lab_lst **head, char *lab);

/*
**	Validation functions:
*/

int						mb_arg_check(t_assm *assm, int op, char **str);
int						error(t_assm *assm, int err);

void					mb_parse_str(t_assm *a, char **i, char **s, char **t);

int						mb_dir_check(t_assm *assm, int op, int c, char **s);
int						mb_reg_check(t_assm *assm, int ch, char **str);
int						mb_ind_check(t_assm *assm, int ch, char **str);
int						mb_valid_line_check(t_assm *assm, char *str);

int						io_instruction_name(char *str);
int						mb_label_exist(t_assm *assm, char **line);
int						mb_check_valid_label(t_assm *assm, char *line);
int						mb_check_label_duplicate(t_assm *assm, t_lab_lst *lab);

#endif
