/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virtual_machine.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuber <dhuber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 16:31:40 by dhuber            #+#    #+#             */
/*   Updated: 2018/10/05 13:39:28 by dhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIRTUAL_MACHINE_H
# define VIRTUAL_MACHINE_H
# include "op.h"
# include "../libft/includes/ft_printf.h"

# define OP_SUCCESS 1
# define OP_ERROR 0
# define AFF_MAX 256

# define CLEAR "\e[J\x1b[H"
# define CLEAR2 "\e[2J\x1b[H"

# define RED "\033[31m"
# define GRE "\033[32m"
# define YEL "\033[33m"
# define BLU "\033[36m"
# define BOLD "\033[1m"

# define BG_WHI "\e[5m\x1b[30;100m"
# define BG_RED "\e[5m\x1b[30;101m"
# define BG_GRE "\e[5m\x1b[30;102m"
# define BG_YEL "\e[5m\x1b[30;103m"
# define BG_BLU "\e[5m\x1b[30;104m"
# define DEFAULT "\x1b[0m"

/*
**	THE COLOR_ARENA STRUCTURE
**	Works like 4 tracing papers applied on the VM_ARENA, allowing to know :
**		- The color of the memory case you're on (int color[]);
**		- The presence of a pc and the color of its player (int pc[]);
**		- The Number of pc there are at the same time on the case (lpc[]);
**		- The last color of the case, before any PC passed on it (lcolor[]);
*/

typedef struct		s_col_arena
{
	int				color[MEM_SIZE + 1];
	int				pc[MEM_SIZE + 1];
	int				lpc[MEM_SIZE + 1];
	int				lcolor[MEM_SIZE + 1];
}					t_col_arena;

typedef struct		s_player
{
	char			name[PROG_NAME_LENGTH + 1];
	char			comment[COMMENT_LENGTH + 1];
	char			taunt[AFF_MAX + 1];
	unsigned char	code[CHAMP_MAX_SIZE + 1];
	int				color;
	int				program_size;
	int				number;
	int				index;
	size_t			address;
	int				lives;
	int				lives_p;
	int				carry;
	size_t			pc;
	size_t			tmpc;
	int				is_opc;
	int				dir;
	int				reg[REG_NUMBER];
	int				is_dead;
	int				instruction;
	int				op;
	int				countdown;
	int				type[4];
	int				arg[3];
	int				index_aff;
	struct s_player	*next;
}					t_player;

typedef struct		s_vm
{
	char			**av;
	int				ac;
	int				cor;
	int				p;
	int				s;
	int				t;
	int				v;
	int				h;
	int				m;
	int				cursors;
	int				dump;
	int				nbr_players;
	int				nbr_fork;
	int				players_alive;
	int				nbr_process;
	int				n[MAX_PLAYERS];
	int				a[MAX_PLAYERS];
	int				cycle;
	int				cycles_to_die;
	int				check;
	int				nbr_live;
	int				last_live;
	int				last_color;
	int				taunt_cycle;
	int				taunt_nb;
	char			winner_name[PROG_NAME_LENGTH + 1];
	char			taunt[AFF_MAX + 1];
	char			taunt_name[PROG_NAME_LENGTH + 1];
	unsigned char	arena[MEM_SIZE + 1];
	t_col_arena		c_arena;
	t_player		player[MAX_PLAYERS];
	t_player		*fork;
}					t_vm;

typedef struct		s_base
{
	char			*name;
	int				nb_arg;
	int				type[4];
	int				opc;
	int				cycle;
	char			*comment;
	int				carry;
	int				direct_bit;
	int				(*ft_op)(t_vm*, t_player*, int*);
}					t_base;

extern t_base		g_op_tab[17];

int					main(int ac, char **av);

void				usage(void);
void				setting_vm(t_vm *vm);
void				init(t_vm *vm, int ac, char **av);
void				parse_flag(t_vm *vm, char **tmp);
void				parse_flag2(t_vm *vm);
void				check_vm(t_vm *vm);
void				unknown_instruction(t_vm *vm, char *av, char *next);
void				valid_extension(t_vm *vm, char *av);
void				vm_error(t_vm *vm, char *msg, char *type, int n);
void				declare_winner(t_vm *vm);
int					vm_isdigit(const char *s);
long long			vm_atoll(const char *s, t_vm *vm);

void				parse_champ(t_vm *vm);
int					check_load(int ref, int to_add);
void				init_champ(t_vm *vm, t_player *player, int i);
void				ft_place_champ(t_vm *vm);
void				ft_check_ad(t_vm *vm, int x, int j);
void				ft_four(t_vm *vm, int j, int x, int i);
void				ft_fill_vma(t_vm *vm, int *address, int x, int j);

void				load_arena(t_vm *vm);
void				ft_sort_champ(t_vm *vm, int i, int j);
void				run_vm(t_vm *vm);
void				free_all(t_vm *vm);

void				recup_reg(t_vm *vm, t_player *player, int index);
void				recup_dir4(t_vm *vm, t_player *player, int index);
void				recup_dir_index(t_vm *vm, t_player *player, int index);

void				take_instruction(t_vm *vm, t_player *player);
void				exec_instruction(t_vm *vm, t_player *player, \
									int (*ft_op)(t_vm*, t_player*, int*));
void				ft_check_fork(t_vm *vm, t_player *fork);
void				do_fork(t_vm *vm, t_player *player);

void				print_vm(t_vm *vm);
void				print_visu(t_vm *vm, int i);
void				print_arena(t_vm *vm);
void				print_color(t_vm *vm, int i);
void				dump(t_vm *vm, int i);
void				dump_memory(t_vm *vm, int i);
void				dump_memory_s(t_vm *vm, int i);

void				*ft_vm_move(void *dst, const void *src,
							size_t len, size_t over_mem);
void				ft_color_move(t_vm *vm, int color, int adr, int size);
void				move_pc(t_vm *vm, t_player *player);

int					op_live(t_vm *vm, t_player *player, int *tab);
int					op_ld(t_vm *vm, t_player *player, int *tab);
int					op_st(t_vm *vm, t_player *player, int *tab);
int					op_add(t_vm *vm, t_player *player, int *tab);
int					op_sub(t_vm *vm, t_player *player, int *tab);
int					op_and(t_vm *vm, t_player *player, int *tab);
int					op_or(t_vm *vm, t_player *player, int *tab);
int					op_xor(t_vm *vm, t_player *player, int *tab);
int					op_zjmp(t_vm *vm, t_player *player, int *tab);
int					op_ldi(t_vm *vm, t_player *player, int *tab);
int					op_sti(t_vm *vm, t_player *player, int *tab);
int					op_fork(t_vm *vm, t_player *player, int *tab);
int					op_lld(t_vm *vm, t_player *player, int *tab);
int					op_lldi(t_vm *vm, t_player *player, int *tab);
int					op_lfork(t_vm *vm, t_player *player, int *tab);
int					op_aff(t_vm *vm, t_player *player, int *tab);

#endif
