/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putlnbr_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 16:05:15 by dhuber            #+#    #+#             */
/*   Updated: 2018/05/30 16:38:28 by dhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putlnbr_base(long long nb, const int base)
{
	if (base < 1)
		return ;
	if (nb < 0)
	{
		nb = -nb;
		ft_putchar('-');
	}
	if (nb > base - 1)
		ft_putlnbr_base(nb / base, base);
	ft_putchar((char)(nb % base + ((nb % base > 9) ? 'A' - 10 : '0')));
}
