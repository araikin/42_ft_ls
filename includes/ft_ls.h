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

void	set_lsflags(unsigned int *flags, char *s);
int		is_lsflag(unsigned int *flags, char c);

void	print_ls(unsigned int flags, t_file *file);

t_file	*new_node(char *name);
t_file	*insert_ascii(t_file *root, t_file *new_node);
t_file	*insert_time(t_file *root, t_file *new_node);
void	inorder(t_file *root);
void	revorder(t_file *root);

# endif
