/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flag_c.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 16:19:02 by dhuber            #+#    #+#             */
/*   Updated: 2018/02/25 16:59:14 by dhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/ft_printf.h"

static void			ft_check_data(t_data *data)
{
	if (data->width_field)
	{
		if (data->width <= data->len)
			data->width_field = 0;
	}
	data->sharp = 0;
	data->plus = 0;
	data->space = 0;
}

int					ft_flag_c(char **format, va_list *arg, t_data *data)
{
	ft_check_data(data);
	if (data->length == l || **format == 'C')
		return (ft_handle_wchar((wchar_t)va_arg(*arg, wint_t), data, 0));
	else
		return (ft_handle_char(va_arg(*arg, wint_t), data, 1));
}
