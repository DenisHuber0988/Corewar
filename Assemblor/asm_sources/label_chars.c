/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label_chars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jauplat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 17:06:53 by jauplat           #+#    #+#             */
/*   Updated: 2018/07/21 15:40:34 by mkamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../asm_includes/asm.h"

int		label_chars(char c)
{
	if ((c > 47 && c < 58) || \
	(c > 96 && c < 123) || c == 95)
		return (1);
	return (0);
}

int		check_instru(char *str, int index, int len)
{
	int		i;

	i = 0;
	if (len > 5 || len < 2)
	{
		ft_putchar('T');
		return (1);
	}
	str[index + len] = '\0';
	while (i < 16 && ft_strcmp(str + index, g_op_tab[i].name))
		i++;
	if (i >= 16)
		return (1);
	str[index + len] = ' ';
	return (0);
}
