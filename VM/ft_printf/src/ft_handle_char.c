/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 16:52:42 by dhuber            #+#    #+#             */
/*   Updated: 2018/06/22 19:22:31 by dhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/ft_printf.h"

static int	ft_handle_minus_char(char c, t_data *data, size_t size)
{
	if (data->width)
	{
		ft_buffer(&c, data, size);
		ft_printf_flag(' ', data, data->width - size);
		size = MAX(data->width, size);
	}
	else
		ft_buffer(&c, data, size);
	return (size);
}

static int	ft_handle_width_char(char c, t_data *data, size_t size)
{
	ft_printf_flag((data->zero) ? '0' : ' ', data, data->width - size);
	ft_buffer(&c, data, size);
	size = MAX(data->width, size);
	return (size);
}

int			ft_handle_char(char c, t_data *data, size_t size)
{
	size = 1;
	if (data->minus)
		size = ft_handle_minus_char(c, data, size);
	else if (data->width_field)
		size = ft_handle_width_char(c, data, size);
	else
		ft_buffer(&c, data, size);
	return (size);
}
