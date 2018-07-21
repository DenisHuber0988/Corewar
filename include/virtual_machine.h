/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virtual_machine.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 18:24:51 by dhuber            #+#    #+#             */
/*   Updated: 2018/07/21 15:58:24 by dhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIRTUAL_MACHINE_H
# define VIRTUAL_MACHINE_H
# include "op.h"
# include "../libft/libft.h"

typedef struct		s_op
{
	char			*name;
}					t_op;

typedef struct		s_cursor
{
}					t_cursor;

typedef struct		s_player
{
	char			*file_name;
	char			name[PROG_NAME_LENGTH];
	char			code[CHAMP_MAX_SIZE];
	int				proram_size;
	int				number;
	int				lives;
	int				*start;
	int				carry;
	int				fork;
	int				color;
	int				*pc;
	int				reg[REG_NUMBER];
	struct s_player	*next;
}					t_player;

typedef struct		s_vm
{
	char			**av;
	int				ac;
	int				v;
	int				cursors;
	int				dump;
	int				nbr_players;
	int				n[MAX_PLAYERS];
	int				a[MAX_PLAYERS];
	int				cycle;
	int				cycles_to_die;
	int				check;
	int				nbr_live;
	int				last_live;
	char			winner_name[PROG_NAME_LENGTH];
	char			arena[MEM_SIZE];
	t_player		*player[MAX_PLAYERS + 1];
	t_cursor		*head;
	t_op			op_tab[17];
}					t_vm;

void				virtual_machine(t_vm *vm);
void				init(t_vm *vm, int ac, char **av);
void				parse_flag(t_vm *vm);
void				unknown_instruction(t_vm *vm, char *av, char *next);
void				valid_extension(t_vm *vm, char *av);
void				ft_error(t_vm *vm, char *msg, char *type, int n);
int					my_isdigit(const char *s);
long long			my_atoll(const char *s, t_vm *vm);

#endif
