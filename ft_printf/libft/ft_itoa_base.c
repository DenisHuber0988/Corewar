/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 14:05:26 by dhuber            #+#    #+#             */
/*   Updated: 2018/06/25 16:05:50 by dhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_size(unsigned long long new, const size_t base)
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

static void		ft_fill_nbr(char *nbr, unsigned long long n,
		const size_t base, size_t i)
{
	while (i--)
	{
		nbr[i] = (char)(n % base + ((n % base > 9) ? 'A' - 10 : '0'));
		n /= base;
	}
}

char			*ft_itoa_base(const long long nb, const size_t base)
{
	size_t				i;
	size_t				signe;
	unsigned long long	n;
	char				*nbr;

	if (base <= 1)
		return (NULL);
	signe = 0;
	if (nb < 0)
	{
		if (base == 10)
			signe = 1;
	}
	n = (nb >= 0) ? (unsigned long long)nb : (unsigned long long)-nb;
	i = ft_size(n, base);
	if (!(nbr = (char*)ft_memalloc(sizeof(char) * (i + signe + 1))))
		return (NULL);
	ft_fill_nbr(nbr, n, base, i + signe);
	if (signe == 1)
		nbr[0] = '-';
	return (nbr);
}
