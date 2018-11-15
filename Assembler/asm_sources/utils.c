/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jauplat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 14:16:56 by jauplat           #+#    #+#             */
/*   Updated: 2018/10/07 15:07:55 by jauplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../asm_includes/asm.h"

/*
**	check if it's a character or not
*/

int		space(char c)
{
	if (c != ' ' && c != '\t' && c)
		return (1);
	return (0);
}

int		arg(char c, char b)
{
	if ((b != ' ' && b != '\t' && b != ',') && c == '%')
		error(-12);
	if ((b != ' ' && b != '\t' && b != ',' && b != '%') \
	&& (c == ':' || c == '-'))
		error(-12);
	if ((b == ' ' || b == ',' || b == '\t') \
	&& (c != '%' && c != ':' && c != '-' && !ft_isdigit(c) && c != ' ' \
	&& c != '\t' && c != 'r' && c != ','))
		error(-12);
	if (((c == ':' || c == 'r' || c == '%' || ft_isdigit(c)) \
	&& (b == ' ' || b == '\t' || b == ',')))
		return (1);
	return (0);
}

void	cpy_arg(char *src, t_champ *list, t_champ *begin)
{
	int		i;
	int		j;

	j = 0;
	i = 0;
	begin->sec[check_line(begin->code)][0] = src[0];
	begin->sec[check_line(begin->code)][1] = src[1];
	while (src[j] == ':' || src[j] == '%')
		j++;
	begin->tmplen[check_line(begin->code)] = begin->prog_size + list->len;
	begin->tmp_prog_size[check_line(begin->code)] = begin->prog_size;
	while (src[j + i] && ft_strchr(LABEL_CHARS, src[j + i]))
	{
		begin->tmp[check_line(begin->code)][i] = src[j + i];
		i++;
	}
}

void	check_octet(t_champ *list, int i, int len)
{
	int		j;
	int		t;
	int		neg;

	neg = 0;
	t = i;
	j = len;
	while (i && len > 0)
	{
		octet(list, &i, len, j);
		len--;
		if (i < 0 && list->arg1[list->len + len])
			i -= 0x01;
	}
	while (len != 0)
	{
		if (t >= 0)
			list->arg1[list->len + (len - 1)] = 0;
		else if (t < 0)
			list->arg1[list->len + (len - 1)] = 0xFF;
		len--;
	}
	list->len += j;
}

int		no_type(t_champ *begin)
{
	if (begin->str[begin->prog_size - 1] == 9)
		return (0);
	if (begin->str[begin->prog_size - 1] == 12)
		return (0);
	if (begin->str[begin->prog_size - 1] == 1)
		return (0);
	if (begin->str[begin->prog_size - 1] == 15)
		return (0);
	return (1);
}
