/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_memory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 14:07:10 by dhuber            #+#    #+#             */
/*   Updated: 2018/07/29 17:06:11 by dhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		convert_memory(unsigned char *addr, size_t size)
{
	unsigned char	*str;
	unsigned char	tmp[size];
	unsigned char	tab[2];
	size_t			i;
	size_t			j;

	i = 0;
	j = 1;
	str = (unsigned char*)addr;
	while (i < size)
	{
		tab[0] = (*str / 16 < 10) ? (*str / 16 + 48) : (*str / 16 + 87);
		tab[1] = (*str % 16 < 10) ? (*str % 16 + 48) : (*str % 16 + 87);
		tmp[i++] = tab[0];
		tmp[i++] = tab[1];
		str++;
	}
	str = &tmp[0];
	addr = ft_memmove(addr, str, size);
}
