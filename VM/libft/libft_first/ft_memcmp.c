/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 09:19:22 by dhuber            #+#    #+#             */
/*   Updated: 2018/05/30 16:43:14 by dhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t		i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n - 1)
	{
		if (((const unsigned char*)s1)[i] != ((const unsigned char*)s2)[i])
			return (int)(((const unsigned char*)s1)[i] -
					((const unsigned char*)s2)[i]);
			i++;
	}
	return (int)(((const unsigned char*)s1)[i] - ((const unsigned char*)s2)[i]);
}
