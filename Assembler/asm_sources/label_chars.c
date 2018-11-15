/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label_chars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jauplat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 17:06:53 by jauplat           #+#    #+#             */
/*   Updated: 2018/10/07 15:06:32 by jauplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../asm_includes/asm.h"

/*
**	allow to take a good formatting to register
*/

int		check_reg(char *str)
{
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (space(str[i]) && end_line(str[i]) && str[i] != ',')
	{
		if (i == 0 && str[i] != 'r')
			return (1);
		if (i > 0 && !ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

/*
**	just for size line to norme
*/

int		direct_last1(t_champ *begin, int n, int j)
{
	if (begin->tmplen[n] + j >= begin->prog_size)
		return (1);
	if (begin->str[begin->tmplen[n] + j])
		return (1);
	return (0);
}

/*
**	check if it's a direct argument or no
*/

int		direct_arg(char c)
{
	if (label_chars(c) || c == ':' || c == '-')
		return (1);
	return (0);
}

/*
**	check if a character for a label is valid or not
*/

int		label_chars(char c)
{
	if ((c > 47 && c < 58) || \
	(c > 96 && c < 123) || c == 95)
		return (1);
	return (0);
}

/*
**	compare with g_op_tab to check if it's a great instruction
*/

int		check_instru(char *str, int index, int len)
{
	int		i;

	i = 0;
	if (len > 5 || len < 2)
		return (1);
	if (str[index + len] == ' ' || str[index + len] == '\t')
		str[index + len] = '\0';
	else
		error(-8);
	while (i < 16 && ft_strcmp(str + index, g_op_tab[i].name))
		i++;
	if (i >= 16)
		return (1);
	str[index + len] = ' ';
	return (0);
}
