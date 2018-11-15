/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_function.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuber <dhuber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 15:51:04 by dhuber            #+#    #+#             */
/*   Updated: 2018/10/05 17:11:27 by dhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm_includes/virtual_machine.h"
#include <limits.h>

void			check_vm(t_vm *vm)
{
	if (vm->nbr_players == 0)
		usage();
	else if (vm->nbr_players > 4)
		vm_error(vm, "Max four champs.", "", 1);
	if (vm->dump > 0)
		vm->v = -1;
	if (vm->s != -1)
	{
		vm->v = -1;
		vm->t = -1;
	}
}

/*
** Check le nombre d arg apres les flags -dump -n et -a et free le split.
** S il y a plus d un arg il s agit d une erreur et le programme s arrete.
*/

static int		check_ptr(char **ptr)
{
	int	i;

	i = 0;
	if (ptr[1])
	{
		while (ptr[i])
			ft_memdel((void**)&ptr[i++]);
		free((void*)ptr);
		ptr = NULL;
		return (1);
	}
	while (ptr[i])
		ft_memdel((void**)&ptr[i++]);
	free((void*)ptr);
	ptr = NULL;
	return (0);
}

/*
**	Verifie que les adresses données aux champions permettent d écrire
**	correctement dans la vm. Sinon c est une erreur.
*/

int				check_load(int ref, int to_add)
{
	int	tmp;

	if (ref == -1)
		return (1);
	ref > to_add ? ft_swap(&ref, &to_add) : 0;
	if (to_add + CHAMP_MAX_SIZE > MEM_SIZE)
	{
		tmp = (to_add + CHAMP_MAX_SIZE) - MEM_SIZE;
		if (ref <= tmp || ref >= to_add - CHAMP_MAX_SIZE)
			return (0);
	}
	else if (to_add - CHAMP_MAX_SIZE < 0)
	{
		tmp = (to_add - CHAMP_MAX_SIZE) + MEM_SIZE;
		if (ref >= tmp || ref <= to_add + CHAMP_MAX_SIZE)
			return (0);
	}
	else if (to_add + CHAMP_MAX_SIZE <= MEM_SIZE &&
			to_add - CHAMP_MAX_SIZE >= 0)
	{
		if (ref >= to_add + CHAMP_MAX_SIZE ||
				ref >= to_add - CHAMP_MAX_SIZE)
			return (0);
	}
	return (1);
}

/*
**	Verifie que l arg après les flags soit un nombre.
*/

int				vm_isdigit(const char *s)
{
	char	**ptr;

	if (!s)
		return (0);
	ptr = ft_strsplit(s, ' ');
	if (check_ptr(ptr))
		return (0);
	while (ft_is_space(*s))
		s++;
	if (*s == '-' || *s == '+')
		s++;
	while (ft_strlen(s) && s)
	{
		if (ft_isdigit(*s))
			s++;
		else if (ft_is_space(*s))
			s++;
		else
			return (0);
	}
	return (1);
}

/*
**	Verifie qu il n y est pas d Overflow.
*/

long long		vm_atoll(const char *str, t_vm *vm)
{
	long	nb;
	long	signe;
	int		index;

	signe = 1;
	nb = 0;
	index = 0;
	while (ft_is_space(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			signe = -1;
		str++;
	}
	while (*str == '0')
		str++;
	while (str[index] >= '0' && str[index] <= '9')
		nb = nb * 10 + (str[index++] - '0');
	if (signe * nb > INT_MAX || signe * nb < INT_MIN || index > 11 \
		|| str[index - 1] == '-' || str[index - 1] == '+' \
		|| str[index] == '-' || str[index] == '+')
		vm_error(vm, "Incorrect int param (Over/Underflow, non digit).", "", 1);
	return (signe * nb);
}
