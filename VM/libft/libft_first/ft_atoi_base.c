/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 17:06:43 by dhuber            #+#    #+#             */
/*   Updated: 2018/07/29 17:07:34 by dhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		ft_to_upper(char c)
{
	if (c >= 'a' && c <= 'z')
		return (c - ('a' - 'A'));
	return (c);
}

static int		ft_inbase(char c, int base)
{
	if (base <= 10)
		return (c >= '0' && c <= '9');
	return ((c >= '0' && c <= '9') ||
			(ft_toupper(c) >= 'A' && ft_toupper(c) <= ('A' + base - 10)));
}

int				ft_atoi_base(const char *str, int str_base)
{
	int		value;
	int		sign;

	value = 0;
	if (str_base <= 1 || str_base > 36)
		return (0);
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\f'
			|| *str == '\r' || *str == '\v')
		str++;
	sign = (*str == '-') ? -1 : 1;
	if (*str == '-' || *str == '+')
		str++;
	while (ft_inbase(*str, str_base))
	{
		if (ft_to_upper(*str) - 'A' >= 0)
			value = value * str_base + (ft_toupper(*str) - 'A' + 10);
		else
			value = value * str_base + (*str - '0');
		str++;
	}
	return (value * sign);
}
