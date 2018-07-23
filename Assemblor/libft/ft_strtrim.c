/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jauplat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 13:39:33 by jauplat           #+#    #+#             */
/*   Updated: 2017/11/17 17:31:04 by jauplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	int		i;
	int		len;
	int		j;
	char	*str;

	j = 0;
	if (s == '\0')
		return (NULL);
	len = ft_strlen((char *)s);
	while (s[len - 1] == ' ' || s[len - 1] == '\t' || s[len - 1] == '\n')
		len--;
	i = 0;
	while (len != 0 && (s[i] == ' ' || s[i] == '\t' || s[i] == '\n'))
	{
		len--;
		i++;
	}
	if (!(str = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	while (j != len)
		str[j++] = s[i++];
	str[j] = '\0';
	return (str);
}
