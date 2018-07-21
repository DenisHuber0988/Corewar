/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flag_s.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 14:00:34 by dhuber            #+#    #+#             */
/*   Updated: 2018/06/22 20:11:21 by dhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/ft_printf.h"

static void			ft_check_str(t_data *data)
{
	if (data->width_field || data->precision_field)
	{
		if (data->precision >= data->len)
			data->precision_field = 0;
	}
	data->space = 0;
	data->sharp = 0;
	data->plus = 0;
}

int					ft_flag_s(char **format, va_list *arg, t_data *data)
{
	char	*s;
	size_t	size;

	s = NULL;
	if (data->length == l || **format == 'S')
		return (ft_handle_wstr((wchar_t*)s, data, arg, 0));
	else
	{
		s = va_arg(*arg, char*);
		if (!s)
			s = "(null)";
		data->len = ft_strlen((const char*)s);
		size = data->len;
		ft_check_str(data);
		return (ft_handle_str(s, data, size));
	}
}
