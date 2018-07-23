/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jauplat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 15:01:56 by jauplat           #+#    #+#             */
/*   Updated: 2018/07/19 16:48:21 by jauplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "../libft/libft.h"
# include "op.h"

# define NO_LABEL "reference to an unexisting label from direct or indirect"

typedef struct		s_champ
{
	char			label[100];
	short			adr;					//	adr_label
	unsigned char	arg1[100];				//	arg
	int				len;					//	len_arg

	unsigned char	arg[100][100];			//	save_arg
	unsigned char	tmp[100][100];			//	save_instr
	char			sec[100][3];
	int				tmplen[100];			//	save_adrr_arg
	int				tmp_prog_size[100];		//	save_size_label_call
	int				code[100];				//	bitsave

	unsigned char	str[MEM_SIZE];			//	prog
	int				prog_size;				//	len_prog
	char			*file;					//	file + ext
	struct s_champ	*next;
}					t_champ;

typedef struct		s_op
{
	char			*name;
	int				nb_arg;
	int				arg[3];
	int				opc;
	int				cycle;
	char			*comment;
	char			test;					//	carry
	char			carry;					//	bit_opc
}					t_op;

extern t_op			g_op_tab[17];

int					main(int argc, char **argv);
void				init_tab(char *str, t_champ *begin);
char				**tab_realloc(char **str, int i);
t_champ				*init_champ(void);
t_header			*init_header(void);
void				error(int n);
void				error1(int n);

void				magic(t_champ *begin, t_header *head, char *file);
void				get_file(t_champ *begin, t_header *head, char *file);

void				name(t_header *head, int fd, char **str, int j);
void				name_copy(char *s, t_header *head);
int					check_quote(char *str);
int					index_quote(char *str);
void				comment(t_header *head, int fd, char **str, int j);
void				comment_copy(char *s, t_header *head);

void				prog(t_champ *begin, int fd);
void				label(t_champ *begin, char **str);
void				check_label(t_champ *begin, t_champ *list);
void				add_label(t_champ *list, char *str);
void				instruction(t_champ *begin, char **str);
void				add_instru(t_champ *begin, t_champ *list, char *str);
void				opc(t_champ *begin, t_champ *list, char *str);
void				add_opc(t_champ *begin, t_champ *list, char c, int j);
void				argument(t_champ *list, t_champ *begin, char *str, int j);
void				registre(t_champ *list, char *str, int j, t_champ *begin);
void				direct(t_champ *list, t_champ *begin, char *str, int j);
void				indirect(t_champ *list, t_champ *begin, char *str, int j);
int					direct_tmp(t_champ *begin, t_champ *tmp);

void				cpy_arg(char *src, t_champ *list, t_champ *begin);
void				check_octet(t_champ *list, int i, int len);
int					check_arg_dir(char c);
int					arg(char c, char b);
int					end_line(char c);
void				octet(t_champ *list, int *n, int len, int bit);
int					space(char c);
int					no_type(t_champ *begin);

int					check_line(int *code);
void				prog_join(t_champ *begin, t_champ *list);
int					type(char *str);
int					index_arg(char *str);
void				moove(t_champ *begin, char *str);
void				tmp(t_champ *list, t_champ *begin, char *str, int j);
void				live(t_champ *begin, char *str);

int					check_op_tab(t_champ *begin, int j, char *str);
int					check_in(char *str, t_champ *begin);
void				del_list(t_champ **begin, t_header *head);
int					label_chars(char c);
int					check_instru(char *str, int index, int len);
void				tmp_header(char **str, t_header *head, int fd, int i);
int					get_size_octet(t_champ *begin, int n);
void				check_end_line(char *str);


#endif
