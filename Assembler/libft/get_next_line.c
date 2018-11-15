/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jauplat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 09:12:44 by jauplat           #+#    #+#             */
/*   Updated: 2018/05/02 17:39:20 by jauplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		check_val_r(char **line, int r, char **rest, char **tmp)
{
	ft_strdel(tmp);
	if (r < 0)
		return (-1);
	if (r == 0 && (**line == '\0' || *line == NULL))
	{
		ft_strdel(rest);
		return (0);
	}
	return (1);
}

int		read_line(int fd, char **tmp, char **str)
{
	char		*buff;
	char		*a;
	int			r;

	while (*str == NULL)
	{
		buff = ft_strnew(BUFF_SIZE);
		r = read(fd, buff, BUFF_SIZE);
		buff[r] = '\0';
		if (r < 0)
			return (-1);
		a = ft_strdup(*tmp);
		ft_strdel(tmp);
		*tmp = ft_strjoin(a, buff);
		*str = ft_strchr(*tmp, '\n');
		ft_strdel(&a);
		ft_strdel(&buff);
		if (r == 0)
			return (0);
	}
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	static char	*rest[OPEN_MAX];
	char		*tmp;
	char		*str;
	int			r;
	int			i;

	i = 0;
	if (fd < 0 || !line || BUFF_SIZE <= 0 || fd > OPEN_MAX || \
		read(fd, "", 0) < 0)
		return (-1);
	if (!rest[fd])
		rest[fd] = ft_strnew(BUFF_SIZE);
	tmp = ft_strdup(rest[fd]);
	str = ft_strchr(tmp, '\n');
	r = read_line(fd, &tmp, &str);
	while (tmp[i] != '\n' && tmp[i] != '\0')
		i++;
	tmp[i] = '\0';
	*line = ft_strdup(tmp);
	ft_strdel(&rest[fd]);
	if (str)
		rest[fd] = ft_strdup(str + 1);
	return (check_val_r(line, r, &rest[fd], &tmp));
}
