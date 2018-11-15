/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 11:41:38 by dhuber            #+#    #+#             */
/*   Updated: 2018/05/21 17:41:05 by dhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

# define BUFF_SIZE 32

typedef	struct		s_line
{
	int				fd;
	char			padding[4];
	char			*line;
	char			*tmp;
	struct s_line	*next;
}					t_line;

int					get_next_line(const int fd, char **line);

#endif
