/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vm_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuber <dhuber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 14:08:13 by aschukin          #+#    #+#             */
/*   Updated: 2018/10/04 14:50:57 by dhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm_includes/virtual_machine.h"

/*
**	Change the color inside the vm.
*/

void		ft_color_move(t_vm *vm, int color, int adr, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		vm->c_arena.color[(adr + i) % MEM_SIZE] = color;
		vm->c_arena.lcolor[(adr + i) % MEM_SIZE] = color;
		i++;
	}
}

/*
**	Write inside the arena.
*/

void		*ft_vm_move(void *dst, const void *src, size_t len, size_t over_mem)
{
	size_t			i;
	char			*tmp_dst;
	const char		tmp_src[5];

	if (!(dst || src))
		return (NULL);
	tmp_dst = dst;
	ft_bzero((void*)&(tmp_src[0]), 5);
	i = 0;
	while (i < len)
	{
		ft_memmove((void*)&(tmp_src[i]), &src[len - i - 1], 1);
		i++;
	}
	i = 0;
	if (over_mem < MEM_SIZE)
		return (ft_memmove(&dst[over_mem - len], tmp_src, len));
	while (i < len)
	{
		ft_memmove(&tmp_dst[(over_mem - len) % MEM_SIZE], &tmp_src[i++], 1);
		over_mem++;
	}
	return (dst);
}
