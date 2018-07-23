/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prog.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jauplat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 12:29:04 by jauplat           #+#    #+#             */
/*   Updated: 2018/07/21 15:41:32 by mkamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../asm_includes/asm.h"

int		voided(char *str)
{
	int		i;
	int		t;

	t = 0;
	i = 0;
	while (end_line(str[t]) && (str[t] == ' ' || str[t] == '\t'))
		t++;
	if (t == (int)ft_strlen(str) || !end_line(str[t]))
		return (2);
	while (label_chars(str[t + i]))
		i++;
	if (str[t + i] == ':' && space(str[0]))
		return (1);
	if (check_instru(str, t, i))
		return (3);
	return (0);
}

int		type(char *str)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	while (ft_strchr(LABEL_CHARS, str[i]))
		i++;
	if (str[i] != ':')
		i = 0;
	while (space(str[i]) != 1)
		i++;
	while (k < 16)
	{
		j = 0;
		while (str[i + j] == g_op_tab[k].name[j] && str[i + j])
			j++;
		if (space(str[i + j]) != 1 && g_op_tab[k].name[j] == '\0')
			break ;
		k++;
	}
	return (g_op_tab[k].opc);
}

int		index_arg(char *str)
{
	int		i;

	i = 0;
	while (ft_strchr(LABEL_CHARS, str[i]))
		i++;
	if (str[i] != ':')
		i = 0;
	while (space(str[i]) != 1 && str[i])
		i++;
	while (space(str[i]))
		i++;
	while (space(str[i]) != 1 && str[i])
		i++;
	return (i);
}

void	direct_last(t_champ *begin, int n)
{
	t_champ		*list;
	int			i;
	int			j;

	j = get_size_octet(begin, n);
	list = begin;
	while (list && ft_strcmp(list->label, (char*)begin->tmp[n]) != 0)
		list = list->next;
	(list == NULL) ? error(-13) : NULL;
	i = (list->adr - begin->tmp_prog_size[n]) + 1;
	while (j >= 0 && i > 0)
	{
		if (begin->str[begin->tmplen[n] + j])
			j--;
		begin->str[begin->tmplen[n] + j] = i % 16;
		i /= 16;
		if (i > 0)
		{
			begin->str[begin->tmplen[n] + j] += (i % 16) * 16;
			i /= 16;
		}
		j--;
	}
	ft_bzero(list->arg1, list->len);
	list->len = 0;
}

void	prog(t_champ *begin, int fd)
{
	int		i;
	int		r;
	char	*str;

	str = NULL;
	while ((r = get_next_line(fd, &str)) > 0)
	{
		if (voided(str) == 1)
			label(begin, &str);
		if (voided(str) == 0)
			instruction(begin, &str);
		if (voided(str) == 3)
			error(-8);
		ft_strdel(&str);
	}
	ft_strdel(&str);
	i = 0;
	while (begin->code[i] == 1)
	{
		direct_last(begin, i);
		i++;
	}
}
