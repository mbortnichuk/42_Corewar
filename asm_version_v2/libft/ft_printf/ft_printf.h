/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iosypenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 11:40:35 by iosypenk          #+#    #+#             */
/*   Updated: 2017/12/09 11:40:38 by iosypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H

# define FT_PRINTF_H

# include <stdarg.h>
# include "../libft.h"

# define RC "\x1B[0m"

# define RED "\x1B[31m"
# define GRN "\x1B[32m"
# define YEL "\x1B[33m"
# define BLU "\x1B[34m"
# define MAG "\x1B[35m"
# define CYN "\x1B[36m"
# define WHT "\x1B[37m"

# define BRED	"\x1B[41m"
# define BGRN	"\x1B[42m"
# define BYEL	"\x1B[43m"
# define BBLU	"\x1B[44m"
# define BMAG	"\x1B[45m"
# define BCYN	"\x1B[46m"
# define BWHT	"\x1B[47m"

# define UNDER	"\e[4m"
# define BLINK	"\e[5m"
# define REVER	"\e[7m"
# define CONC	"\e[8m"
# define BOLD	"\e[1m"
# define DIM	"\e[2m"
# define NORM	"\e[24m"

typedef struct	s_type
{
	int			ret_nb;
	char		*res;
	char		tp;
	int			no_tp;
	int			plus;
	int			minus;
	int			space;
	int			octo;
	int			zero;
	int			aster;
	char		*nb_w;
	char		*nb_p;
	int			width;
	int			w;
	int			prec;
	int			p;
	int			h;
	int			hh;
	int			l;
	int			ll;
	int			j;
	int			z;
	int			ln;
	int			sign;
	char		c;
}				t_type;

int				ft_printf(const char *format, ...);

int				get_spec(const char **ft, t_type *k, char **sp);
void			get_type(char *sp, t_type *k);
void			get_length(char *sp, t_type *k);

char			*ib(intmax_t value, int base);
char			*ui(uintmax_t value, int base, int c);

void			print_d_i(va_list ap, t_type *k);
void			print_bd(va_list ap, t_type *k);
void			print_u(va_list ap, t_type *k);
void			print_bu(va_list ap, t_type *k);
void			print_o(va_list ap, t_type *k);
void			print_bo(va_list ap, t_type *k);
void			print_x(va_list ap, t_type *k);
void			print_bx(va_list ap, t_type *k);
void			print_c(va_list ap, t_type *k);
void			print_bc(va_list ap, t_type *k);
void			print_s(va_list	ap, t_type *k);
void			print_bs(va_list ap, t_type *k);
void			print_b(va_list ap, t_type *k);
void			print_p(va_list ap, t_type *k);
void			save_n(va_list ap, t_type *k);

void			get_width_prec(va_list ap, char *sp, t_type *k);
void			if_as(va_list ap, t_type *k, int n);
void			if_width(t_type *k);
void			if_prec(t_type *k);

void			if_plus(t_type *k);
void			if_minus(t_type *k);
void			if_space(t_type *k);
void			if_zero(t_type *k);
void			if_octo(t_type *k);

char			*add_to_res(char *str, char symb);
void			one(t_type *k, int *n, int tmp);
void			two(t_type *k, int *n, int tmp);
void			three(t_type *k, int *n, int tmp);
void			four(t_type *k, int *n, int tmp);

#endif
