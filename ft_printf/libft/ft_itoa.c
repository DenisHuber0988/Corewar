/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 20:42:30 by dhuber            #+#    #+#             */
/*   Updated: 2018/01/09 18:45:26 by dhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	ft_len(size_t x)
{
	size_t	len;

	len = 1;
	while (x > 9)
	{
		x /= 10;
		len++;
	}
	return (len);
}

static	char	*ft_print_num(char *tab, size_t x, size_t len)
{
	while (len--)
	{
		tab[len] = x % 10 + '0';
		x /= 10;
	}
	return (tab);
}

char			*ft_itoa(int n)
{
	char	*tab;
	size_t	len;
	size_t	sign;
	size_t	x;

	sign = (n >= 0) ? 0 : 1;
	x = (n >= 0) ? (size_t)n : (size_t)-n;
	if (n == -2147483648)
		x = 2147483648;
	len = ft_len(x);
	tab = ft_strnew(len + sign);
	if (!tab)
		return (NULL);
	tab = ft_print_num(tab, x, len + sign);
	if (sign == 1)
		*tab = '-';
	return (tab);
}
