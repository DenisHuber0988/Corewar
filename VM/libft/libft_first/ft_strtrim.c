/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 18:16:19 by dhuber            #+#    #+#             */
/*   Updated: 2017/12/27 19:41:23 by dhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t		ft_isspace(char c)
{
	if (c == ' ' || c == '\n' || c == '\t')
		return (1);
	return (0);
}

static	size_t		ft_rm_start_space(char const *s)
{
	size_t	index;

	index = 0;
	while (ft_isspace(s[index]))
		index++;
	return (index);
}

static	size_t		ft_rm_end_space(char const *s, size_t len)
{
	while (ft_isspace(s[len]) && len != 0)
		len--;
	return (len);
}

char				*ft_strtrim(char const *s)
{
	char	*ptr;
	size_t	start;
	size_t	end;
	size_t	len;
	size_t	index;

	if (!s)
		return (NULL);
	len = ft_strlen(s) - 1;
	start = ft_rm_start_space(s);
	end = ft_rm_end_space(s, len);
	len = end - start;
	if (start > end)
		len = start - end;
	ptr = ft_strnew(len + 1);
	if (!ptr)
		return (NULL);
	index = 0;
	while (s[start] && start < end + 1)
		ptr[index++] = s[start++];
	return (ptr);
}
