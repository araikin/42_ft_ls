/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asultanb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 12:48:03 by asultanb          #+#    #+#             */
/*   Updated: 2020/01/15 16:38:16 by asultanb         ###   ########.fr       */
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

typedef struct		s_file
{
	char			*name;
	t_stat			info;
	struct s_file	*left;	
	struct s_file	*right;	
}					t_file;

void	ft_ls_no_arg(unsigned int flags);
void	ft_ls_single_arg(unsigned int flags, char *arg);
void	ft_ls_arg(unsigned int flags, char **args);

void	set_lsflags(unsigned int *flags, char *s);
int		is_lsflag(unsigned int *flags, char c);

void    parse_time(time_t mod_time);
void	print_ls(unsigned int flags, t_file *file);
void	inorder(unsigned int flags, t_file *root);
void	revorder(unsigned int flags, t_file *root);

void	set_dirinfo(unsigned int flags, t_file **file, char *arg);
void	process_args(unsigned int flags, t_file *d, int n);
t_file	*new_node(char *name, char *path);
t_file	*insert_ascii(t_file *root, t_file *new_node);
t_file	*insert_time(t_file *root, t_file *new_node);

int     is_dir(char *arg);
int     is_file(char *arg);
int		check_dir(unsigned int flags, t_dirent *dp);
void	sort_args(char **args);

# endif
