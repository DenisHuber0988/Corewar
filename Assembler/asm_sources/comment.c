/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jauplat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 11:22:24 by jauplat           #+#    #+#             */
/*   Updated: 2018/10/07 14:59:35 by jauplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../asm_includes/asm.h"

/*
**	copy comment while second double quote is missing and check is size
*/

void	comment_copy(char *s, t_header *head)
{
	int		i;
	int		j;

	j = 0;
	i = ft_strlen(head->comment);
	while (s[j] && s[j] != '"' && i < COMMENT_LENGTH)
	{
		head->comment[i] = s[j];
		j++;
		i++;
	}
	if (s[j] == '\0')
	{
		head->comment[i] = '\n';
		i += 1;
	}
	if (i == COMMENT_LENGTH)
		error(-4);
	if (s[j] == '"')
	{
		if (s[j + 1])
			error(-4);
	}
}

/*
**	get a first quote (limit of comment)
**	and call function to cpy while a second quote is missing
*/

void	comment(t_header *head, int fd, char **str, int j)
{
	int		i;
	int		r;

	i = 0;
	if (!str || !str[0] || !str[0][0])
		((r = get_next_line(fd, &str[0]) <= 0)) ? error(-2) : NULL;
	if (j == 0)
		i = index_quote(str[0]);
	j += check_quote(str[0]);
	if (j > 0)
		comment_copy(str[0] + i, head);
	if (j < 2)
	{
		ft_strdel(&str[0]);
		comment(head, fd, &str[0], j);
	}
}
