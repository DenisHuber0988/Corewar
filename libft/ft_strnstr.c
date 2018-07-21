/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 12:05:00 by dhuber            #+#    #+#             */
/*   Updated: 2017/11/22 17:52:16 by dhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *hay, const char *need, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	if (!need[i])
		return ((char*)hay);
	while (hay[i] && i < len)
	{
		j = 0;
		k = i;
		while (hay[k] == need[j] && k < len)
		{
			j++;
			k++;
			if (need[j] == '\0')
				return ((char*)&hay[i]);
		}
		i++;
	}
	return (0);
}
