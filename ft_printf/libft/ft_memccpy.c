/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 18:13:01 by dhuber            #+#    #+#             */
/*   Updated: 2017/12/27 18:08:19 by dhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	char			*tmp_dst;
	unsigned char	d;
	const char		*tmp_src;

	i = 0;
	tmp_dst = dst;
	tmp_src = src;
	while (i < n)
	{
		tmp_dst[i] = tmp_src[i];
		d = ((unsigned char*)tmp_dst)[i];
		if (d == (unsigned char)c)
			return (void*)(&tmp_dst[i + 1]);
		i++;
	}
	return (NULL);
}
