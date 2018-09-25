/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_vm.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iosypenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 16:37:58 by iosypenk          #+#    #+#             */
/*   Updated: 2018/05/01 16:38:02 by iosypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_VM_H

# define HEADER_VM_H

# include "../corewar.h"

# define ALIGNMENT		((PROG_NAME_LENGTH + 1) % 4)
# define CODE_SIZE_POS	((9 + PROG_NAME_LENGTH) - ALIGNMENT)
# define COMMENT_POS	((13 + PROG_NAME_LENGTH) - ALIGNMENT)
# define CODE_POS		(COMMENT_POS + COMMENT_LENGTH + 4)

/*
**	size
*/

# define S_REG			1
# define S_DIR_0			4
# define S_DIR_1			2
# define S_IND			2

/*
**	codage
*/

# define C_REG			1
# define C_DIR			2
# define C_IND			3

typedef struct s_core	t_core;
typedef struct s_proc	t_proc;
typedef struct s_champ	t_champ;

/*
**	Main funtions:
*/

void					parsing_champ(t_core *core, char *argv);
void					create_map(t_core *core);
void					create_proc(t_proc **head, int id, int pc, int col_nbr);
void					create_champ(t_core *core);
void					place_champs(t_core *core);

void					show_usage(void);
void					err(int nb);
void					err_arg(int nb, char *arg);
int						check_flags(t_core *core, char **argv, int i);
void					dump_stop(t_core *core);
void					init_champ(t_champ *champ, t_core *core);

t_champ					*get_last_list(t_champ *head);
void					add_proc(t_proc **alst, t_proc *new);
t_proc					*new_proc(int id, int pc);

void					print_dump(t_core core);
void					introduce(t_champ *champ, int nb);

#endif
