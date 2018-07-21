/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 16:08:36 by dhuber            #+#    #+#             */
/*   Updated: 2017/11/16 16:13:25 by dhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strnequ(char const *s1, char const *s2, size_t n)
{
	size_t len;

	len = 0;
	if (!s1 || !s2)
		return (0);
	if (n == 0)
		return (1);
	while (*s1 && *s2 && *s1 == *s2 && len < n - 1)
	{
		s1++;
		s2++;
		len++;
	}
	if (*s1 == *s2)
		return (1);
	return (0);
}
