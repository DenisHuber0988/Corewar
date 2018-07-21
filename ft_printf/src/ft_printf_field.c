/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_field.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 17:31:54 by dhuber            #+#    #+#             */
/*   Updated: 2018/02/26 18:52:43 by dhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/ft_printf.h"

char	*ft_flag(char **format, t_data *data)
{
	while (**format == ' ' || **format == '+' || **format == '-'
			|| **format == '0' || **format == '#')
	{
		if (**format == '-')
			data->minus = 1;
		else if (**format == '+')
			data->plus = 1;
		else if (**format == ' ')
			data->space = 1;
		else if (**format == '0')
			data->zero = 1;
		else if (**format == '#')
			data->sharp = 1;
		(*format)++;
		if (data->minus)
			data->zero = 0;
		if (data->plus)
			data->space = 0;
	}
	return (*format);
}

char	*ft_width(char **format, va_list *arg, t_data *data)
{
	int		nb;

	nb = 0;
	if (**format == '*')
	{
		data->width_field = 1;
		nb = va_arg(*arg, int);
		if (nb < 0)
		{
			data->width = -nb;
			data->minus = 1;
		}
		else
			data->width = nb;
		return (*format += 1);
	}
	while (ft_isdigit(**format))
		nb = nb * 10 + (*(*format)++ - '0');
	if (nb)
	{
		data->width_field = 1;
		data->width = ABS(nb);
	}
	return (*format);
}

char	*ft_precision(char **format, va_list *arg, t_data *data)
{
	int		nb;

	nb = 0;
	if (**format == '.')
	{
		(*format)++;
		if (**format == '*')
		{
			nb = va_arg(*arg, int);
			data->precision = (nb < 0) ? 0 : nb;
			data->precision_field = (nb < 0) ? 0 : 1;
			return (*format += 1);
		}
		else
		{
			data->precision_field = 1;
			while (ft_isdigit(**format))
				nb = nb * 10 + (*(*format)++ - '0');
		}
		data->precision = nb;
	}
	return (*format);
}

char	*ft_size(char **format, t_data *data)
{
	if ((**format == 'h' && *(*(format) + 1) == 'h') ||
			(**format == 'l' && *(*(format) + 1) == 'l'))
	{
		if (**format == 'h')
			data->length = hh;
		else if (data->length < 4)
			data->length = ll;
		return (*format += 2);
	}
	else if (*(*format) == 'h' && data->length < 2)
		data->length = h;
	else if (*(*format) == 'l' && data->length < 3)
		data->length = l;
	else if (*(*format) == 'j' && data->length < 5)
		data->length = j;
	else if (*(*format) == 'z' && data->length < 6)
		data->length = z;
	else if (*(*format) == 't' && data->length < 7)
		data->length = t;
	else if (*(*format) == 'L')
		data->length = L;
	if (ft_strchr("hljztL", **format) && **format != '\0')
		return (*format += 1);
	return (*format);
}

char	*ft_error(char **format)
{
	char	*error;

	error = "bcCdDfFinoOpuUsSxX%";
	if (ft_strchr(" -+#0.*hljztL", **format) && **format != '\0')
		return (*format);
	else if ((ft_strchr(error, **format) || ft_isdigit(**format)
			|| **format == ' ') && **format != '\0')
		return (*format);
	else
		return (NULL);
}
