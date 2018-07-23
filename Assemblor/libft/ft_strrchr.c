/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jauplat <jauplat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 20:59:04 by jauplat           #+#    #+#             */
/*   Updated: 2017/11/16 11:16:06 by jauplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*str;

	str = (char *)s;
	i = ft_strlen(str);
	while (i != 0)
	{
		if (str[i] == (char)c)
			return (str + i);
		i--;
	}
	if (str[i] == (char)c)
		return (str + i);
	return (NULL);
}
