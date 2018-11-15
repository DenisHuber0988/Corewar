/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 16:44:44 by dhuber            #+#    #+#             */
/*   Updated: 2018/06/22 19:45:44 by dhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t		ft_size(unsigned long long new, const size_t base)
{
	size_t	size;

	size = 1;
	while (new > (unsigned long long)base - 1)
	{
		new /= base;
		size++;
	}
	return (size);
}

char				*ft_utoa_base(unsigned long long nb, const size_t base)
{
	size_t				i;
	char				*nbr;

	if (base <= 1)
		return (NULL);
	i = ft_size(nb, base);
	nbr = ft_strnew(i);
	while (i--)
	{
		nbr[i] = (char)(nb % base + ((nb % base > 9) ? 'a' - 10 : '0'));
		nb /= base;
	}
	return (nbr);
}
