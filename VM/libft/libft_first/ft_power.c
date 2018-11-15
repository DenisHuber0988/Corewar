/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 17:45:34 by dhuber            #+#    #+#             */
/*   Updated: 2018/02/21 16:56:51 by dhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_power(long long nb, int pow, long long acc)
{
	if (pow == 0)
		return (acc);
	return (ft_power(nb, pow - 1, nb * acc));
}
