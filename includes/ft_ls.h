/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asultanb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 12:48:03 by asultanb          #+#    #+#             */
/*   Updated: 2020/02/04 15:50:07 by asultanb         ###   ########.fr       */
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
# define S_UPP 64
# define F_LOW 128
# define G_UPP 256
# define F_UPP 512
# define ONE 1024

typedef struct dirent	t_dirent;
typedef struct stat		t_stat;

typedef struct		s_file
{
	char			*name;
	char			*path;
	int				total;
	t_stat			info;
	struct s_file	*left;
	struct s_file	*right;
}					t_file;

typedef struct		s_wid
{
	int				links;
	int				uid;
	int				gid;
	int				size;
	int				chr_blk;
	int				minor;
	int				major;
	char			mode;
}					t_wid;

void				ft_ls_one_arg(uint16_t opt, char *arg, t_wid *wid);
void				ft_ls_mul_args(uint16_t opt, char **args, t_wid *wid);
void				r_upp(uint16_t opt, char *path, t_wid *wid, t_file *f);
void				iter_r(uint16_t opt, char *path, t_wid *wid, t_file *f);

void				set_options(uint16_t *opt, char *s, int i);
void				set_info(uint16_t opt, t_file **file, char *arg);
void				set_wid(t_file *root, t_wid *wid);
void				handle_dir(uint16_t opt, char **args, t_wid *wid, int n);
void				sort_time_args(char **args);

t_file				*new_node(char *name, char *path, int *total);
t_file				*insert_file(uint16_t opt, t_file *f, t_file *new);
t_file				*by_ascii(t_file *f, t_file *new);
t_file				*by_time(t_file *f, t_file *new);
t_file				*by_size(t_file *f, t_file *new);

int					is_dir(char *arg);
int					is_file(char *arg);
int					check_dir(uint16_t opt, t_dirent *dp);
void				destroy_file(t_file *file);
void				ls_output(int mode, char *arg);

void				print_ls(uint16_t opt, t_file *file, t_wid *wid, int n);
void				revorder(uint16_t opt, t_file *file, t_wid *wid);
void				inorder(uint16_t opt, t_file *file, t_wid *wid);
void				print_name(uint16_t opt, t_file *file);

void				long_format(uint16_t opt, t_file *file, t_wid *wid);
void				print_st_mode(t_file *file);
void				print_time(time_t mod_time);
void				print_link(uint16_t opt, t_file *file);

void				set_color(t_stat info);
void				print_type(t_stat info);

#endif
