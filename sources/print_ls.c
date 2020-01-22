/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asultanb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 15:40:32 by asultanb          #+#    #+#             */
/*   Updated: 2020/01/17 15:40:33 by asultanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	print_ls(unsigned int flags, t_file *file)
{
	(flags & R_LOW) ? revorder(flags, file) : inorder(flags, file);
}

void	parse_time(time_t mod_time)
{
	int		flag;
	int		i;
	char	*mtime;
	
	flag = (time(NULL) - mod_time > 15552000) ? 1 : 0;
	mtime = ctime(&mod_time);
	i = 3;
	while (++i < 11)
		write(1, &mtime[i], 1);
	if (flag)
	{
		i += 8;
		while (++i < 24)
			write(1, &mtime[i], 1);
	}
	else
		while (i < 16)
			write(1, &mtime[i++], 1);
}

void	print_node(unsigned int flags, t_file *root)
{
	if (flags & L_LOW)
	{
		ft_printf("%c%c%c%c%c%c%c%c%c%c %d\t%s %s %d \t",
								S_ISDIR(root->info.st_mode) ? 'd' : '-',
								root->info.st_mode & S_IRUSR ? 'r' : '-',
								root->info.st_mode & S_IWUSR ? 'w' : '-',
								root->info.st_mode & S_IXUSR ? 'x' : '-',
								root->info.st_mode & S_IRGRP ? 'r' : '-',
								root->info.st_mode & S_IWGRP ? 'w' : '-',
								root->info.st_mode & S_IXGRP ? 'x' : '-',
								root->info.st_mode & S_IROTH ? 'r' : '-',
								root->info.st_mode & S_IWOTH ? 'w' : '-',
								root->info.st_mode & S_IXOTH ? 'x' : '-',
								root->info.st_nlink,
								(getpwuid(root->info.st_uid))->pw_name,
								(getgrgid(root->info.st_gid))->gr_name,
								root->info.st_size);
		parse_time(root->info.st_mtime);
		ft_printf("\t%s\n", root->name);
	}
	else
		ft_printf("%s\n", root->name);
}

void	revorder(unsigned int flags, t_file *root)
{
	if (root != NULL)	
	{
		revorder(flags, root->right);
		print_node(flags, root);
		revorder(flags, root->left);
	}
}

void	inorder(unsigned int flags, t_file *root)
{
	if (root != NULL)
	{
		inorder(flags, root->left);
		print_node(flags, root);
		inorder(flags, root->right);
	}
}
