/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jauplat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 16:34:51 by jauplat           #+#    #+#             */
/*   Updated: 2018/07/21 15:39:39 by mkamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../asm_includes/asm.h"

void	argument(t_champ *list, t_champ *begin, char *str, int j)
{
	int		i;

	i = 0;
	check_end_line(str);
	if (str[i] == 'r')
		registre(list, str, j, begin);
	else if (str[i] == ':' || str[i + 1] == ':' \
	|| (str[i] == '%' && check_arg_dir(begin->str[begin->prog_size - 1])))
		direct(list, begin, str, j);
	else if ((str[i + 1] == '-' && ft_isdigit(str[i + 2])) || \
	(str[i] == '-' && ft_isdigit(str[i + 1])) || \
	ft_isdigit(str[i]) || ft_isdigit(str[i + 1]))
		indirect(list, begin, str, j);
}

void	registre(t_champ *list, char *str, int j, t_champ *begin)
{
	if (check_op_tab(begin, j, str))
		error(-12);
	list->arg1[list->len] = ft_atoi(str + 1);
	if (list->arg1[list->len] > 16)
		error(-9);
	list->len += 1;
}

void	direct(t_champ *list, t_champ *begin, char *str, int j)
{
	t_champ	*tmp;
	int		i;

	tmp = begin;
	i = 0;
	if (check_op_tab(begin, j, str))
		error(-12);
	if (str[0] == '%' && str[1] != ':' && !ft_isdigit(str[1]) && str[1] != '-')
		error(-11);
	else if ((str[0] == ':' || str[1] == ':') && j)
	{
		cpy_arg(str, list, begin);
		while (tmp && ft_strcmp(tmp->label, \
		(char*)begin->tmp[check_line(begin->code)]) != 0)
			tmp = tmp->next;
		i = direct_tmp(begin, tmp);
	}
	else if (ft_isdigit(str[1]) || str[1] == '-')
		i = ft_atoi(str + 1);
	if (str[1] == ':' && !check_arg_dir(begin->str[begin->prog_size - 1]))
		check_octet(list, i, T_IND);
	else
		check_octet(list, i, T_DIR);
}

int		direct_tmp(t_champ *begin, t_champ *tmp)
{
	int		i;
	int		j;

	j = begin->prog_size;
	i = 0;
	if (tmp)
	{
		if (j == 0)
			i = tmp->adr;
		else if (j > tmp->adr)
			i = (tmp->adr - j) + 1;
		else
			i = (tmp->adr - j);
		begin->tmplen[check_line(begin->code)] = 0;
		begin->tmp_prog_size[check_line(begin->code)] = 0;
		ft_bzero(begin->tmp[check_line(begin->code)], 50);
		ft_bzero(begin->sec[check_line(begin->code)], 3);
	}
	else
		begin->code[check_line(begin->code)] = 1;
	return (i);
}

void	indirect(t_champ *list, t_champ *begin, char *str, int j)
{
	int		i;
	int		k;

	k = 0;
	if (check_op_tab(begin, j, str))
		error(-12);
	while (ft_isdigit(str[k]) == 0 && str[k] != '-')
		k++;
	i = ft_atoi(str + k);
	if (i > INT_MAX || i < INT_MIN)
		error(-10);
	if (str[0] != '%')
		check_octet(list, i, T_DIR);
	else
		check_octet(list, i, T_IND);
}
