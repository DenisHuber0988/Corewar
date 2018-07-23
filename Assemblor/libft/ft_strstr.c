/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jauplat <jauplat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 21:09:40 by jauplat           #+#    #+#             */
/*   Updated: 2017/11/16 11:54:41 by jauplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int		i;
	int		j;
	char	*str;
	char	*find;

	find = (char *)needle;
	str = (char *)haystack;
	i = 0;
	j = 0;
	if (find[j] == '\0')
		return (str);
	while (str[i])
	{
		j = 0;
		while (find[j] == str[i + j] && find[j])
		{
			if (find[j + 1] == '\0')
				return (str + i);
			j++;
		}
		i++;
	}
	return (NULL);
}
