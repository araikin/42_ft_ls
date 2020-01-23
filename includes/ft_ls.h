/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asultanb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 12:48:03 by asultanb          #+#    #+#             */
/*   Updated: 2020/01/22 17:32:20 by asultanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "../libft/libft.h"
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/xattr.h>
# include <uuid/uuid.h>
# include <stdio.h>
# include <dirent.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>

# define A_UPP 1
# define A_LOW 2
# define L_LOW 4
# define T_LOW 8
# define R_LOW 16
# define R_UPP 32

typedef struct dirent	t_dirent;
typedef struct stat		t_stat;

typedef struct			s_file
{
	char				*name;
	t_stat				info;
	struct s_file		*left;
	struct s_file		*right;
}						t_file;

typedef struct			s_wid
{
	int					links;
	int					uid;
	int					gid;
	int					size;
}						t_wid;

void					ft_ls_no_arg(uint8_t flags, t_wid *wid);
void					ft_ls_single_arg(uint8_t flags, char *arg, t_wid *wid);
void					ft_ls_arg(uint8_t flags, char **args, t_wid *wid);

void					set_lsflags(uint8_t *flags, char *s);
int						is_lsflag(uint8_t *flags, char c);

void					set_info(uint8_t flags, t_file **file, char *arg);
void					process_args(uint8_t flags, t_file *d, int n,
						t_wid *wid);
t_file					*new_node(char *name, char *path);
t_file					*insert_ascii(t_file *root, t_file *new_node);
t_file					*insert_time(t_file *root, t_file *new_node);

int						is_dir(char *arg);
int						is_file(char *arg);
int						check_dir(uint8_t flags, t_dirent *dp);
void					sort_args(char **args);

void					print_ls(uint8_t flags, t_file *file, t_wid *wid);
int						get_digitsnum(int n);
void					set_widwid(t_file *root, t_wid *wid);
void					revorder(uint8_t flags, t_file *root, t_wid *wid);
void					inorder(uint8_t flags, t_file *root, t_wid *wid);

void					print_l_low(t_file *root, t_wid *wid);
void					handle_width(uint8_t flags, t_file *d, t_wid *wid);
void					print_attributes(t_file *root);
void					parse_time(time_t mod_time);

#endif
