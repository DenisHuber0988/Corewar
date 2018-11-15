/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flag_p.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuber <dhuber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 17:38:49 by dhuber            #+#    #+#             */
/*   Updated: 2018/10/04 14:10:40 by dhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void			ft_check_data(t_data *data, size_t size)
{
	if (data->width_field || data->precision_field)
	{
		if (data->width <= size || data->precision >= data->width)
			data->width_field = 0;
		if (data->precision <= data->len)
			data->precision = 0;
	}
}

int					ft_flag_p(char **format, va_list *arg, t_data *data)
{
	unsigned long long	adr;
	size_t				size;
	char				*nbr;

	(void)format;
	adr = va_arg(*arg, unsigned long long);
	nbr = ft_utoa_base(adr, 16);
	data->len = ft_strlen((const char*)nbr);
	size = data->len + 2;
	if (!adr)
		size = 2;
	ft_check_data(data, size);
	return (ft_handle_ptr(&nbr, data, size));
}
