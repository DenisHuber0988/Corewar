/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jauplat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 11:49:20 by jauplat           #+#    #+#             */
/*   Updated: 2018/10/07 15:07:52 by jauplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../asm_includes/asm.h"

/*
**	check if this argument is a good typing
*/

int		check_op_tab(t_champ *begin, int j, char *str)
{
	int		i;

	i = 0;
	if (str[0] == 'r')
	{
		i = g_op_tab[(int)begin->str[begin->prog_size - 1] - 1].arg[j - 1] \
		& T_REG;
		if (i != T_REG)
			return (1);
	}
	if (str[0] == '%')
	{
		i = g_op_tab[(int)begin->str[begin->prog_size - 1] - 1].arg[j - 1] \
		& T_DIR;
		if (i != T_DIR)
			return (1);
	}
	if (str[0] == '-' || ft_isdigit(str[0]) || str[0] == ':')
	{
		i = g_op_tab[(int)begin->str[begin->prog_size - 1] - 1].arg[j - 1] \
		& T_IND;
		if (i != T_IND)
			return (1);
	}
	return (0);
}

/*
**	return a number of quote on this linee
*/

int		check_quote(char *str)
{
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
			j++;
		i++;
	}
	return (j);
}

/*
**	return an index after a first quote
*/

int		index_quote(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
			return (i + 1);
		i++;
	}
	return (0);
}

/*
**	take a negative number
*/

void	tmp(t_champ *list, t_champ *begin, char *str, int j)
{
	indirect(list, begin, str, j);
	if (no_type(begin))
		add_opc(begin, list, str[0], j);
}

int		check_in(char *str, t_champ *begin)
{
	int		i;
	t_champ	*list;

	list = begin;
	i = 0;
	while (list && list->label[0])
	{
		if (ft_strcmp(str, list->label) == 0)
			error(-7);
		list = list->next;
	}
	if (list)
		i = ft_strlen(list->label);
	while (end_line(str[i]) && ft_isprint(str[i]) == 0)
		i++;
	if (i == (int)ft_strlen(str) || !end_line(str[i]))
		return (0);
	return (1);
}
