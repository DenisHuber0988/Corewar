/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_champ.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuber <dhuber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 12:55:59 by dhuber            #+#    #+#             */
/*   Updated: 2018/09/26 12:28:51 by dhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm_includes/virtual_machine.h"

/*
** All player names and comments must finish with 1 empty byte.
*/

static void		check_null_octet(t_vm *vm, int fd, int k)
{
	int		i;
	char	octet[4];

	read(fd, octet, 4);
	i = 0;
	while (i < 4)
	{
		if (octet[i] != 0 && !k)
			vm_error(vm, "No null octet after name.", "", 1);
		else if (octet[i] != 0 && k)
			vm_error(vm, "No null octet after comment.", "", 1);
		i++;
	}
}

/*
** Stores player name.
** Errors if 'magic number' is incorrect (as defined in op.h)
** or if failed to read name.
*/

static void		parse_name(t_vm *vm, int nbr, int fd)
{
	ssize_t			ret;
	unsigned char	magic_nbr[8];
	char			name[PROG_NAME_LENGTH + 1];

	ft_bzero(magic_nbr, 8);
	ft_bzero(name, PROG_NAME_LENGTH + 1);
	read(fd, magic_nbr, 4);
	convert_memory(magic_nbr, 8);
	if (ft_strncmp((char*)magic_nbr, "00ea83f3", 8))
		vm_error(vm, "Wrong Exec_Magic.", (char*)magic_nbr, 1);
	if ((ret = read(fd, name, PROG_NAME_LENGTH)) == -1)
		vm_error(vm, "Can't read file.", "", 1);
	ft_memmove(vm->player[nbr].name, name, PROG_NAME_LENGTH + 1);
}

/*
** Stores player comment.
** Errors if comment is too big (larger than COMMENT_LENGTH defined in op.h)
** or if failed to read comment.
*/

static void		parse_comment(t_vm *vm, int nbr, int fd)
{
	ssize_t				ret;
	unsigned char		octet[9];
	char				comment[COMMENT_LENGTH + 1];

	ft_bzero(octet, 9);
	ft_bzero(comment, COMMENT_LENGTH + 1);
	read(fd, octet, 4);
	convert_memory(octet, 8);
	vm->player[nbr].program_size = ft_atoi_base((const char*)&octet[0], 16);
	if (vm->player[nbr].program_size > CHAMP_MAX_SIZE)
		vm_error(vm, "Champ too big.", "", 1);
	if ((ret = read(fd, comment, COMMENT_LENGTH)) == -1)
		vm_error(vm, "Can't read file.", "", 1);
	ft_memmove(vm->player[nbr].comment, comment, COMMENT_LENGTH + 1);
}

/*
** Compares the actual size of the .cor file with that file's declared size
** (verifies that the player's code has not been modified or corrupted).
*/

static void		parse_code(t_vm *vm, int nbr, int fd)
{
	ssize_t				ret;
	int					size;
	unsigned char		code[CHAMP_MAX_SIZE + 1];

	ft_bzero(code, CHAMP_MAX_SIZE + 1);
	size = CHAMP_MAX_SIZE;
	if ((ret = read(fd, code, CHAMP_MAX_SIZE)) == -1)
		vm_error(vm, "Can't read file.", "", 1);
	ft_memmove(vm->player[nbr].code, code, CHAMP_MAX_SIZE + 1);
	if (ret != vm->player[nbr].program_size)
		vm_error(vm, "Invalid header.", "", 1);
}

/*
** Parses for valid players and stores info in vm->player[nbr]...
*/

void			parse_champ(t_vm *vm)
{
	int		nbr;
	int		fd;
	char	**tmp;

	tmp = (vm->av + 1);
	nbr = 0;
	while (*tmp)
	{
		if (ft_strstr(*tmp, ".cor"))
		{
			if ((fd = open(*tmp, O_RDONLY)) < 0)
				vm_error(vm, "Fail to read champ : ", *tmp, 1);
			init_champ(vm, &vm->player[nbr], nbr);
			parse_name(vm, nbr, fd);
			check_null_octet(vm, fd, 0);
			parse_comment(vm, nbr, fd);
			check_null_octet(vm, fd, 1);
			parse_code(vm, nbr++, fd);
			if (close(fd) == -1)
				vm_error(vm, "Can't close file.", "", 1);
		}
		tmp += 1;
	}
	ft_place_champ(vm);
}
