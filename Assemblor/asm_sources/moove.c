/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moove.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jauplat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 15:30:03 by jauplat           #+#    #+#             */
/*   Updated: 2018/07/21 15:41:13 by mkamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../asm_includes/asm.h"

void	moove(t_champ *begin, char *str)
{
	begin->str[begin->prog_size] = type(str);
	begin->prog_size += 1;
}

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
