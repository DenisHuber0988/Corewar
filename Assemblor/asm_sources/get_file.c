/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jauplat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 16:14:18 by jauplat           #+#    #+#             */
/*   Updated: 2018/07/23 13:46:50 by dhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../asm_includes/asm.h"

void	magic(t_champ *begin, t_header *head, char *file)
{
	int		i;
	int		len;

	len = ft_strlen(file);
	i = 1;
	if (file[len - 1] == 's' && file[len - 2] == '.')
	{
		head->magic[0] = 0x00;
		head->magic[1] = 0xea;
		head->magic[2] = 0x83;
		head->magic[3] = 0xf3;
	}
	else
		error(-3);
	file[len - 1] = '\0';
	begin->file = ft_strjoin(file, "cor");
}

void	tmp_header(char **str, t_header *head, int fd, int i)
{
	if (ft_strstr(str[0], NAME_CMD_STRING))
	{
		if (i != 0)
			error(-4);
		name(head, fd, &str[0], 0);
		i++;
	}
	else if (ft_strstr(str[0], COMMENT_CMD_STRING))
	{
		if (i != 1)
			error(-4);
		comment(head, fd, &str[0], 0);
		i++;
	}
}

void	get_file(t_champ *begin, t_header *head, char *file)
{
	int		fd;
	char	*str;
	int		i;

	i = 0;
	str = NULL;
	((fd = open(file, O_RDONLY)) == -1 ? error(-2) : NULL);
	magic(begin, head, file);
	while (get_next_line(fd, &str) > 0 && i != 2)
	{
		if (ft_strstr(str, NAME_CMD_STRING) \
		|| ft_strstr(str, COMMENT_CMD_STRING))
		{
			tmp_header(&str, head, fd, i);
			i++;
			if (i == 2)
				break ;
		}
		ft_strdel(&str);
	}
	ft_strdel(&str);
	if (i != 2)
		error(-4);
	prog(begin, fd);
}
