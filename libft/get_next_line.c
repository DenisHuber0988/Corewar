/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 17:00:25 by dhuber            #+#    #+#             */
/*   Updated: 2018/05/21 19:22:22 by dhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

static t_line			*create_new(const int fd)
{
	t_line	*new;

	if (!(new = (t_line*)malloc(sizeof(t_line))))
		return (NULL);
	new->fd = fd;
	new->line = NULL;
	if (!(new->tmp = (char*)ft_strnew(sizeof(char) * 0)))
		return (NULL);
	new->next = NULL;
	return (new);
}

static	t_line			*check_fd(const int fd, t_line **list)
{
	t_line	*tmp;
	t_line	*tmp2;

	tmp = *list;
	tmp2 = NULL;
	while (tmp != NULL)
	{
		if (tmp->fd == fd)
			return (tmp);
		tmp2 = tmp;
		tmp = tmp->next;
	}
	tmp = create_new(fd);
	if (tmp2 != NULL)
		tmp2->next = tmp;
	else
		*list = tmp;
	return (tmp);
}

static	int				check(t_line *ptr, char *it, char *buf, char **line)
{
	char	*tmp;

	if (!buf)
		return (0);
	tmp = ft_strchr(buf, '\n');
	free(it);
	it = NULL;
	if (tmp)
	{
		*tmp = '\0';
		*line = ft_strdup(buf);
		ft_strncpy(buf, &tmp[1], ft_strlen(&tmp[1]) + 1);
		return (1);
	}
	else if (ft_strlen(buf) > 0)
	{
		*line = ft_strdup(buf);
		*buf = '\0';
		return (1);
	}
	free(ptr->line);
	ptr->line = NULL;
	return (0);
}

int						get_next_line(const int fd, char **line)
{
	ssize_t			ret;
	char			*buf;
	t_line			*tmp;
	static	t_line	*ptr;

	if (!ptr)
		ptr = create_new(fd);
	if (fd < 0 || !line || BUFF_SIZE < 1)
		return (-1);
	tmp = check_fd(fd, &ptr);
	buf = (char*)ft_memalloc(sizeof(char) * (BUFF_SIZE + 1));
	while (!(ft_strchr(buf, '\n')))
	{
		ret = read(fd, (void*)buf, BUFF_SIZE);
		buf[ret] = '\0';
		if (ret < 0)
			return (-1);
		if (ret == 0)
			return (check(ptr, buf, tmp->tmp, line));
		tmp->line = ft_strjoin(tmp->tmp, buf);
		free(tmp->tmp);
		tmp->tmp = tmp->line;
	}
	return (check(ptr, buf, tmp->tmp, line));
}
