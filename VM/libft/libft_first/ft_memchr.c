/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 15:22:15 by dhuber            #+#    #+#             */
/*   Updated: 2018/05/30 16:24:15 by dhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	const char		*tmp_src;
	unsigned char	d;

	i = 0;
	tmp_src = s;
	while (i < n)
	{
		d = ((const unsigned char*)tmp_src)[i];
		if (d == (unsigned char)c)
			return (void*)(&tmp_src[i]);
		i++;
	}
	return (NULL);
}
