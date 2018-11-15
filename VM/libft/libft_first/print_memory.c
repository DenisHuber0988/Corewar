/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 11:30:30 by dhuber            #+#    #+#             */
/*   Updated: 2018/07/29 17:05:05 by dhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		print(unsigned char *tabmem, int *j)
{
	(void)tabmem;
	if (*j == 16)
	{
		write(1, tabmem, 16);
		write(1, "\n", 1);
		*j = 0;
	}
}

static void		final_print(unsigned char *tabmem, size_t i, int j)
{
	if (j && *tabmem)
	{
		while (i % 16 != 0)
		{
			write(1, "  ", 2);
			if (i % 2 == 1)
				write(1, " ", 1);
			i++;
		}
		write(1, tabmem, j);
		write(1, "\n", 1);
	}
}

void			print_memory(const void *addr, size_t size)
{
	unsigned char	*str;
	unsigned char	tabmem[16];
	unsigned char	tab[2];
	size_t			i;
	int				j;

	i = 0;
	j = 0;
	str = (unsigned char*)addr;
	while (i < size)
	{
		tab[0] = (*str / 16 < 10) ? (*str / 16 + 48) : (*str / 16 + 87);
		tab[1] = (*str % 16 < 10) ? (*str % 16 + 48) : (*str % 16 + 87);
		write(1, tab, 2);
		if (i++ % 2)
			write(1, " ", 1);
		i++;
		tabmem[j++] = 31 < *str && *str < 127 ? *str : '.';
		str++;
		print(tabmem, &j);
	}
	final_print(tabmem, i, j);
}
