/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 18:05:47 by dhuber            #+#    #+#             */
/*   Updated: 2018/06/25 17:32:16 by dhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <limits.h>
# include <stdint.h>
# include <stddef.h>
# include "../libft/libft.h"

# define BUFF		64
# define MAX(a, b)	((a > b) ? a : b)
# define MIN(a, b)	((a < b) ? a : b)
# define ABS(a)		((a > 0) ? a : -a)

typedef struct		s_data
{
	size_t			minus : 1;
	size_t			plus : 1;
	size_t			sharp : 1;
	size_t			space : 1;
	size_t			zero : 1;

	size_t			width_field : 1;
	size_t			precision_field : 1;
	size_t			param_field : 1;

	char			pad[7];
	size_t			width;
	size_t			precision;

	size_t			len;

	enum
	{
		none,
		hh,
		h,
		l,
		ll,
		j,
		z,
		t,
		L,
	}				length;
	char			pad2[4];
	size_t			i;
	char			buf[BUFF];
}					t_data;

typedef struct		s_func
{
	int				(*ptr_func)(char**, va_list*, t_data*);
	char			key[8];
}					t_func;

int					ft_printf(const char *format, ...);

void				ft_buffer(const char *format, t_data *data, size_t size);
void				ft_printf_flag(char c, t_data *data, size_t size);

int					ft_flag_b(char **format, va_list *arg, t_data *data);
int					ft_flag_c(char **format, va_list *arg, t_data *data);
int					ft_flag_capx(char **format, va_list *arg, t_data *data);
int					ft_flag_d(char **format, va_list *arg, t_data *data);
int					ft_flag_f(char **format, va_list *arg, t_data *data);
int					ft_flag_o(char **format, va_list *arg, t_data *data);
int					ft_flag_p(char **format, va_list *arg, t_data *data);
int					ft_flag_s(char **format, va_list *arg, t_data *data);
int					ft_flag_u(char **format, va_list *arg, t_data *data);
int					ft_flag_x(char **format, va_list *arg, t_data *data);
int					ft_noflag(char **format, va_list *arg, t_data *data);
int					ft_wrong(char **format, va_list *arg, t_data *data);

int					ft_handle_bin(char **n, t_data *data, size_t size);
int					ft_handle_hex(char **n, t_data *data, size_t size, char *s);
int					ft_handle_neg(char **n, t_data *data, size_t size, char *s);
int					ft_handle_pos(char **n, t_data *data, size_t size, char *s);
int					ft_handle_ptr(char **n, t_data *data, size_t size);
int					ft_handle_zero(t_data *data);

int					ft_handle_char(char c, t_data *data, size_t size);
int					ft_handle_str(char *s, t_data *data, size_t size);
int					ft_handle_wchar(wchar_t c, t_data *data, size_t size);
int					ft_handle_wstr(wchar_t *s, t_data *data,
		va_list *arg, size_t size);

char				*ft_flag(char **format, t_data *data);
char				*ft_width(char **format, va_list *arg, t_data *data);
char				*ft_precision(char **format, va_list *arg, t_data *data);
char				*ft_size(char **format, t_data *data);
char				*ft_error(char **format);

int					ft_printf_conversion(char **format, va_list *arg,
		t_data *data, size_t ret);

#endif
