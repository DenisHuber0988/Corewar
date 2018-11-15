/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jauplat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 14:04:31 by jauplat           #+#    #+#             */
/*   Updated: 2018/10/07 15:07:54 by jauplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../asm_includes/asm.h"

/*
**	check if a chracter is an end of line
*/

int		end_line(char c)
{
	if (c != '\0' && c != ';' && c != '#')
		return (1);
	return (0);
}

/*
**	check if a code is on for the label missing
*/

int		check_line(int *code)
{
	int		i;

	i = 0;
	while (code[i])
		i++;
	return (i);
}

/*
**	get first the octet n[0]
*/

void	octet(t_champ *list, int *n, int len, int bit)
{
	bit = 0;
	list->arg1[list->len + (len - 1)] += n[0] & 0xff;
	n[0] /= 0x100;
}

/*
**	check an instruction needed typing
*/

int		check_arg_dir(char c)
{
	if (c != 1 && c != 2 && c != 6 && c != 8 && c != 7 && c != 13)
		return (1);
	return (0);
}

/*
**	add on program all missing argument
*/

void	prog_join(t_champ *begin, t_champ *list)
{
	int		i;

	i = 0;
	while (i < list->len)
	{
		begin->str[begin->prog_size] = list->arg1[i];
		i++;
		begin->prog_size += 1;
	}
	ft_bzero(list->arg1, list->len);
	list->len = 0;
}
