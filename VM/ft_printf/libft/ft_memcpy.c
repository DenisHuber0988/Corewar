/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 19:53:08 by dhuber            #+#    #+#             */
/*   Updated: 2018/06/25 16:14:14 by dhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned int	i;
	char			*tmp_dst;
	const char		*tmp_src;

	i = 0;
	if (!(dst || src || n))
		return (NULL);
	tmp_dst = dst;
	tmp_src = src;
	if (dst > src)
		while (n--)
			tmp_dst[n] = tmp_src[n];
	else
		while (i < n)
		{
			tmp_dst[i] = tmp_src[i];
			i++;
		}
	return (dst);
}
