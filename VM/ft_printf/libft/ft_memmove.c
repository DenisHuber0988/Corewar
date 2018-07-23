/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 18:01:09 by dhuber            #+#    #+#             */
/*   Updated: 2018/06/25 16:41:47 by dhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	char			*tmp_dst;
	const char		*tmp_src;

	if (!(dst || src))
		return (NULL);
	tmp_dst = dst;
	tmp_src = src;
	if (dst > src)
		while (len--)
			tmp_dst[len] = tmp_src[len];
	else
	{
		i = 0;
		while (i < len)
		{
			tmp_dst[i] = tmp_src[i];
			i++;
		}
	}
	return (dst);
}
