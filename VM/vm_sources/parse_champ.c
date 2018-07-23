/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_champ.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 12:55:59 by dhuber            #+#    #+#             */
/*   Updated: 2018/07/23 19:10:44 by dhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm_includes/virtual_machine.h"

static void		extract_name(t_vm *vm, char *name, int nbr)
{
	char	*tmp;
	ft_printf("to extract = [%s]\n", name);
	ft_printf("size name = [%d]\n", ft_strlen(name));
	tmp = ft_strchr(name, '.');
	ft_memcpy(vm->player[nbr].name, tmp, ft_strlen(tmp));
	ft_printf("extracted name = [%s]\n", vm->player[nbr].name);
}

static void		parse(t_vm *vm, char *data, int nbr)
{
	int			fd;
	ssize_t		ret;
	char		name[PROG_NAME_LENGTH];
	char		comment[COMMENT_LENGTH];

	ft_memset(name, '0', sizeof(name));
	ft_bzero(comment, sizeof(comment));
	fd = open(data, O_RDONLY);
	if (fd < 0)
		vm_error(vm, "Fail to read champ : ", data, 1);
	ret = read(fd, (void*)name, PROG_NAME_LENGTH);
	extract_name(vm, name, nbr);
	ft_printf("read name =\n[%s]\n", name);
	ft_memmove(vm->player[nbr].name, name, ret);
	ret = read(fd, (void*)comment, COMMENT_LENGTH);
	ft_printf("read comment =\n[%s]\n", comment);
	ft_memmove(vm->player[nbr].comment, comment, ret);
	if (close(fd) == -1)
		vm_error(vm, "Can't close file.", "", 1);
}

void			parse_champ(t_vm *vm)
{
	int		nbr;
	char	**tmp;

	tmp = (vm->av + 1);
	nbr = 0;
	while (*tmp)
	{
		if (ft_strstr(*tmp, ".cor"))
		{
			init_champ(vm, &vm->player[nbr], nbr);
			parse(vm, *tmp, nbr++);
		}
		tmp += 1;
	}
}
