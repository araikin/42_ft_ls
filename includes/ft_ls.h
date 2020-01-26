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
	int					total;
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

/*******************	ft_ls.c		********************/
void					ft_ls_one_arg(uint8_t flags, char *arg, t_wid *wid);
void					ft_ls_mul_args(uint8_t flags, char **args, t_wid *wid);
void					ft_ls_recur(uint8_t flags, char *arg, t_wid *wid, t_file *d);

/*******************	utils_ls.c		********************/
void					set_wid(t_file *root, t_wid *wid);
void					iterate_args(uint8_t flags, char **args, t_wid *wid);
void					handle_dir(uint8_t flags, char **args, t_wid *wid, int check);
void					set_lsflags(uint8_t *flags, char *s);
int						is_lsflag(uint8_t *flags, char c);

/*******************	file_ls.c	********************/
void					set_info(uint8_t flags, t_file **file, char *arg);
t_file					*new_node(char *name, char *path, int *total);
t_file					*insert_ascii(t_file *root, t_file *new_node);
t_file					*insert_time(t_file *root, t_file *new_node);

/*******************	check_ls.c	********************/
int						is_dir(char *arg);
int						is_file(char *arg);
int						check_dir(uint8_t flags, t_dirent *dp);
void					sort_args(char **args);

/*******************	print_ls.c	********************/
void					print_ls(uint8_t flags, t_file *file, t_wid *wid, int dir);
void					revorder(uint8_t flags, t_file *root, t_wid *wid);
void					inorder(uint8_t flags, t_file *root, t_wid *wid);
void					print_l_low(t_file *root, t_wid *wid);
void					parse_time(time_t mod_time);

/*******************	output.c	********************/
void					destroy_file(t_file *file);

#endif
