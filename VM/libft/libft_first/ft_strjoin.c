/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 17:46:46 by dhuber            #+#    #+#             */
/*   Updated: 2018/05/21 17:47:50 by dhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	size_t	index;
	char	*ptr;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	index = 0;
	if (!(ptr = (char*)ft_memalloc(sizeof(char) * (len_s1 + len_s2 + 1))))
		return (NULL);
	while (s1[index])
	{
		ptr[index] = s1[index];
		index++;
	}
	index = 0;
	while (s2[index])
		ptr[len_s1++] = s2[index++];
	return (ptr);
}
