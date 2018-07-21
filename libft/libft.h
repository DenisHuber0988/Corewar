/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 12:28:59 by dhuber            #+#    #+#             */
/*   Updated: 2018/07/21 15:52:37 by dhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <wchar.h>
# include <fcntl.h>

typedef struct		s_liste
{
	void			*content;
	size_t			content_size;
	struct s_liste	*next;
}					t_liste;

int					ft_max(int a, int b);
size_t				ft_wlen(unsigned int n);
int					ft_nblen(long long nb, const int base);
int					get_next_line(const int fd, char **line);
int					ft_is_space(char c);
int					ft_atoi(const char *str);
long long			ft_atoll(const char *s);
void				ft_bzero(void *s, size_t n);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
int					ft_is_lower(int c);
int					ft_is_upper(int c);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memset(void *b, int c, size_t len);
void				ft_putchar(char c);
void				ft_putchar_fd(char c, int fd);
void				ft_putwchar(wchar_t c);
void				ft_putwchar_fd(wchar_t c, int fd);
void				ft_putstr(char const *s);
void				ft_putwstr(const char *s);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl(char const *s);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr(int n);
void				ft_putlnbr_base(long long nb, const int base);
void				ft_putnbr_fd(int n, int fd);
long long			ft_power(long long nb, int pow, long long acc);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strchr(const char *s, int c);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strdup(const char *s1);
size_t				ft_strlen(const char *s);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strncat(char *s1, const char *s2, size_t n);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strnstr(const char *hay, const char *need, size_t len);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *haystack, const char *needle);
int					ft_tolower(int c);
int					ft_toupper(int c);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
char				*ft_itoa(int n);
char				*ft_itoa_base(const long long nb, const size_t base);
t_liste				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_liste **alst, void(*del)(void *, size_t));
void				ft_lstdel(t_liste **alst, void(*del)(void *, size_t));
void				ft_lstadd(t_liste **alst, t_liste *new);
void				ft_lstiter(t_liste *lst, void(*f)(t_liste *elem));
t_liste				*ft_lstmap(t_liste *lst, t_liste *(*f)(t_liste *elem));
char				*ft_strrev(char *s);
char				*ft_print_bit(int n);
void				ft_swap(int *a, int *b);
char				*ft_utoa_base(unsigned long long nb, const size_t base);

#endif