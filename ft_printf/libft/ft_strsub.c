/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 16:16:17 by dhuber            #+#    #+#             */
/*   Updated: 2017/11/16 17:42:53 by dhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	index;

	if (!s)
		return (NULL);
	if (!(ptr = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	index = 0;
	while (s[start] && index < len)
		ptr[index++] = s[start++];
	ptr[index] = '\0';
	return (ptr);
}
