/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nblen.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 13:42:07 by dhuber            #+#    #+#             */
/*   Updated: 2018/05/30 16:37:42 by dhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_nblen(long long nb, const int base)
{
	int	len;

	if (base < 1)
		return (0);
	len = (nb >= 0) ? 1 : 2;
	nb = (nb >= 0) ? nb : -nb;
	while (nb > base - 1)
	{
		nb /= base;
		len++;
	}
	return (len);
}
