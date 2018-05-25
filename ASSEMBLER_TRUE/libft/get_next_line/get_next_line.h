/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iosypenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 14:20:31 by iosypenk          #+#    #+#             */
/*   Updated: 2017/11/25 14:20:34 by iosypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include "../libft.h"

# define BUFF_SIZE 100

typedef struct		s_string
{
	int				fd;
	char			*s;
	struct s_string	*next;
}					t_string;

int					get_next_line(const int fd, char **line);

#endif
