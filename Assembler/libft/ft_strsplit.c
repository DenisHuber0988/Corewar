/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jauplat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 17:10:13 by jauplat           #+#    #+#             */
/*   Updated: 2017/11/22 14:49:09 by jauplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_lentab(const char *s, char c)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (*s == '\0')
		return (0);
	if (s[i] != c)
		j++;
	while (s[i])
	{
		if (s[i - 1] == c && s[i] != c)
			j++;
		i++;
	}
	return (j);
}

static int	ft_lenchr(const char *s, char c)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (*s == '\0')
		return (0);
	if (c == s[i])
		i++;
	while (s[i] != c && s[i])
	{
		i++;
		j++;
	}
	return (j);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**tab;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = -1;
	if (!s)
		return (NULL);
	if (!(tab = (char **)malloc(sizeof(char *) * (ft_lentab(s, c) + 1))))
		return (NULL);
	while (++j < ft_lentab(s, c))
	{
		while (c == s[i])
			i++;
		if (!(tab[j] = (char *)malloc(sizeof(char) * (ft_lenchr(&s[i], c)))))
			return (NULL);
		ft_bzero(tab[j], ft_lenchr(&s[i], c));
		k = 0;
		while (s[i] && s[i] != c)
			tab[j][k++] = s[i++];
		tab[j][k] = '\0';
	}
	tab[j] = NULL;
	return (tab);
}
