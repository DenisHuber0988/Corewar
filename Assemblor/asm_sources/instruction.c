/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jauplat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 17:47:24 by jauplat           #+#    #+#             */
/*   Updated: 2018/07/21 15:40:27 by mkamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../asm_includes/asm.h"

void	instruction(t_champ *begin, char **str)
{
	t_champ	*list;

	list = begin;
	if (list->label[0] == '\0')
		list->adr = begin->prog_size;
	if (begin->label[0] == '\0')
		begin->label[0] = 'A';
	while (list->next)
		list = list->next;
	if (check_in(str[0], begin))
	{
		moove(begin, str[0]);
		opc(begin, list, str[0]);
		prog_join(begin, list);
	}
}

void	opc(t_champ *begin, t_champ *list, char *str)
{
	int		i;
	int		j;
	int		k;

	k = (int)begin->str[begin->prog_size - 1];
	j = 1;
	i = index_arg(str);
	while (end_line(str[i]))
	{
		(str[i] == ',') ? j++ : j;
		if (str[i] == '-' && (str[i - 1] == ' ' || str[i - 1] == '\t' \
		|| str[i - 1] == ',') && ft_isdigit(str[i + 1]))
			tmp(list, begin, str + i, j);
		if (arg(str[i], str[i - 1]) == 1 && j <= g_op_tab[k - 1].nb_arg)
		{
			argument(list, begin, str + i, j);
			if (no_type(begin))
				add_opc(begin, list, str[i], j);
		}
		i++;
	}
	if (g_op_tab[k - 1].nb_arg != j)
		error(-1);
}

void	add_opc(t_champ *begin, t_champ *list, char c, int j)
{
	int		i;
	int		tmp;

	tmp = begin->prog_size - 1;
	i = 8;
	if (list)
		i = 8;
	if (c == 'r')
		begin->str[begin->prog_size] += 0b00000001 << (i - (j * 2));
	else if (c == '%')
		begin->str[begin->prog_size] += 0b00000010 << (i - (j * 2));
	else if (c == ':' || ft_isdigit(c) == 1 || c == '-')
		begin->str[begin->prog_size] += 0b00000011 << (i - (j * 2));
	if (j == g_op_tab[(int)begin->str[tmp] - 1].nb_arg)
		begin->prog_size += 1;
}
