/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jauplat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 18:21:40 by jauplat           #+#    #+#             */
/*   Updated: 2018/06/11 18:32:17 by jauplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa_base(intmax_t n, int base)
{
	intmax_t	tmpn;
	int			len;
	int			negative;
	char		*str;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	tmpn = n;
	len = 2;
	negative = 0;
	ft_isnegative(&n, &negative);
	while (tmpn /= base)
		len++;
	len += negative;
	if ((str = (char*)malloc(sizeof(char) * len)) == NULL)
		return (NULL);
	str[--len] = '\0';
	while (len--)
	{
		if (n % base + '0' > 9 && n % base + '0' < 16)
			str[len] = n % base + 'W';
		else if (n % base + '0' < 10)
			str[len] = n % base + '0';
		n = n / base;
	}
	if (negative)
		str[0] = '-';
	return (str);
}
