/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jauplat <jauplat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 18:25:39 by jauplat           #+#    #+#             */
/*   Updated: 2018/05/11 19:43:13 by jauplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	int			i;
	char		*destb;
	const char	*srcb;

	i = 0;
	destb = dest;
	srcb = src;
	while (n != 0)
	{
		destb[i] = srcb[i];
		n--;
		i++;
	}
	return (dest);
}
