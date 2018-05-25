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

/*
** List of labels.
*/

typedef struct			t_lab
{
	char				*name;
	unsigned int		index;
	struct t_lab		*next;

}						t_lab;

/*typedef struct			s_header
{
	unsigned int		magic;
	char				prog_name[PROG_NAME_LENGTH + 1];
	unsigned int		prog_size;
	char				comment[COMMENT_LENGTH + 1];
}						t_header;*/

int						g_str;
int						g_indx;
int						g_temporary;

/*
** mb_support_func.c
*/

int						ft_strclen(char c, char *str);
void					mb_init_glob(void);
int						mb_move_i(char *inp_file, int i);
t_header				*mb_init_header(void);
t_lab					*mb_init_lab(char *str, t_lab *lab);

/*
** mb_support_func1.c
*/

int						mb_free_label_lst(t_lab *lab);
int						mb_return_header(char *str, t_header *header);
char					*mb_realloc(char *inp_file, char *str, int i);
int						mb_calc_i(t_lab *lab, char *inp_file);
char					*mb_join_free(char *inp_file, char *str);

/*
** mb_instruction_name.c
*/

int						mb_instruction_name2(char *str);
int						mb_instruction_name(char *str);

/*
** mb_check_arg_and_error.c
*/

int						mb_arg_check(int op, char **str);
int						mb_arg_check2(int op, char **str);
int						mb_error(int err);
int						mb_error2(int err);

/*
** mb_start_parse.c
*/

// int					mb_champion_check(char *champion);
// char					*mb_putline_infile(char *str, char *inp_file, int i);
// t_lab				*mb_parse_str(char **inp_file, int file_descr);
int						mb_start_parse(t_header *header, char *champ);

/*
** mb_header_cpy.c
*/

// int					mb_head_pass(int n, int c, int ch, char *str);
// int					mb_head_end_pass(int j, char *str);
// t_header				*mb_copy_head(t_header *header, char *str, int ch);
// int					mb_name_comm_copy(t_header *header, char *str, int n, int c);
int						mb_handle_name_comm(t_header *header, int file_descr);

/*
** mb_instruction_checker.c
*/

int						mb_check_sepchar(char **str);
int						mb_direct_check( int op, int ch, char **str);
int						mb_register_check(int ch, char **str);
int						mb_indirect_check(int ch, char **str);
int						mb_valid_line_check(char *str);

/*
** mb_label_checker.c
*/

// int					mb_label_match(char *line, t_lab *lab);
int						mb_label_exist(char *line, t_lab *lab);
int						mb_check_valid_label(char *line);
int						mb_check_label_duplicate(t_lab *lab);







/*
** asm_writer.c
*/

int						mb_convert_endian2(int b);
int						mb_convert_endian(int b);
int						mb_create_header(int file_descr, t_header *head);
int						mb_reader(t_lab *lab, t_header *head, char *champion, char *inp_file);

/*
** asm_binary_write.c
*/

int						asm_move_g_file(int fct);
int						mb_move_sepchar(char **inp_file);
int						mb_scary_func_name(int fct, int fd, t_lab *label, char **file);
int						mb_create_bin(int file_descr, t_lab *lab, char *inp_file);

/*
** asm_write_octal.c
*/

int						mb_opcode(int file_descr, int arg, int i, char *inp_file);
int						mb_write_direct(int file_descr, int size, t_lab *lab, char **inp_file);
int						mb_write_indirect(int file_descr, t_lab *lab, char **inp_file);
int						mb_write_register(int file_descr, char **inp_file);

#endif
