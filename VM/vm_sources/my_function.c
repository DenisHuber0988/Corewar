/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_function.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 15:51:04 by dhuber            #+#    #+#             */
/*   Updated: 2018/07/21 17:07:36 by mkamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm_includes/virtual_machine.h"
#include <limits.h>

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
	if (signe * nb > INT_MAX || index > 11 ||
			str[index - 1] == '-' || str[index - 1] == '+' ||
			str[index] == '-' || str[index] == '+')
		vm_error(vm, "Overflow.", "", 1);
	return (signe * nb);
}
