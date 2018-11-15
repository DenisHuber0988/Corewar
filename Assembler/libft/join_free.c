/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jauplat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 18:49:20 by jauplat           #+#    #+#             */
/*   Updated: 2018/06/05 17:06:14 by jauplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*join_free(char const *s1, char const *s2)
{
	int		lens1;
	int		lens2;
	char	*str;

	lens1 = ft_strlen((char *)s1);
	lens2 = ft_strlen((char *)s2);
	if (!(str = (char *)malloc(sizeof(char) * (lens1 + lens2) + 1)))
		return (NULL);
	ft_strcpy(str, s1);
	ft_strdel((char**)&s1);
	ft_strcat(str, s2);
	return (str);
}
