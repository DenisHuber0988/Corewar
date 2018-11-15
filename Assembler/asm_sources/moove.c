/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moove.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jauplat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 15:30:03 by jauplat           #+#    #+#             */
/*   Updated: 2018/10/07 15:06:48 by jauplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../asm_includes/asm.h"

/*
**	check an argument's number
*/

int		void_argument(char *str)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 1;
	k = 0;
	while (end_line(str[i]))
	{
		if (str[i] == ',')
			j++;
		if (i > 0 && ((str[i] == 'r' || str[i] == '%' \
		|| str[i] == ':' || str[i] == '-' || ft_isdigit(str[i])) \
		&& (str[i - 1] == '\t' || str[i - 1] == ' ' || str[i - 1] == ',')))
			k++;
		i++;
	}
	if (k != j)
		return (1);
	return (0);
}

/*
**	check if the line is empty
*/

void	check_void_line(char *str)
{
	int		i;

	i = 0;
	while (end_line(str[i]))
	{
		if (space(str[i]))
			error(-4);
		i++;
	}
}

/*
**	take an OPcode to the instruction and up the size
*/

void	moove(t_champ *begin, char *str)
{
	begin->str[begin->prog_size] = type(str);
	begin->prog_size += 1;
}

/*
**	get a direct size octet or an indirect size octet for this argument
*/

int		get_size_octet(t_champ *begin, int n)
{
	int		j;

	if (!check_arg_dir(begin->str[begin->tmp_prog_size[n] - 1]) \
	&& (begin->sec[n][1] == ':'))
		j = T_IND;
	else
		j = T_DIR;
	return (j);
}

/*
**	check if argument missing or if argument is invalid
*/

void	check_end_line(char *str)
{
	int		i;

	i = 0;
	while (space(str[i]) == 1 && str[i] != ',')
		i++;
	while (space(str[i]) == 0 && str[i] != ',' && str[i] != '\0')
		i++;
	if (end_line(str[i]) && str[i] != ',')
		error(-12);
}
