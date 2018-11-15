/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jauplat <jauplat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 22:14:40 by jauplat           #+#    #+#             */
/*   Updated: 2017/11/12 14:16:49 by jauplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	char		*destb;
	const char	*srcb;
	int			i;

	i = 0;
	destb = (char *)dest;
	srcb = (const char *)src;
	while (n != 0)
	{
		destb[i] = srcb[i];
		if ((char)c == destb[i])
			return (dest + i + 1);
		i++;
		n--;
	}
	return (NULL);
}
