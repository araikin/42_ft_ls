/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asultanb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 15:40:32 by asultanb          #+#    #+#             */
/*   Updated: 2020/01/27 14:31:57 by asultanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	print_ls(uint8_t opt, t_file *file, t_wid *wid, int dir)
{
	if (file && opt & L_LOW && dir)
		ft_printf("total %d\n", file->total);
	if (opt & R_LOW)
		revorder(opt, file, wid);
	else
		inorder(opt, file, wid);
}

void	revorder(uint8_t opt, t_file *root, t_wid *wid)
{
	if (root != NULL)
	{
		revorder(opt, root->right, wid);
		if (opt & L_LOW)
			print_l_low(root, wid);
		else
			ft_printf("%s\n", root->name);
		revorder(opt, root->left, wid);
	}
}

void	inorder(uint8_t opt, t_file *root, t_wid *wid)
{
	if (root != NULL)
	{
		inorder(opt, root->left, wid);
		if (opt & L_LOW)
			print_l_low(root, wid);
		else
			ft_printf("%s\n", root->name);
		inorder(opt, root->right, wid);
	}
}

void	print_l_low(t_file *root, t_wid *wid)
{
	char	c;

	if (S_ISDIR(root->info.st_mode))
		c = 'd';
	else if (S_ISLNK(root->info.st_mode))
		c = 'l';
	else
		c = '-';
	ft_printf("%c%c%c%c%c%c%c%c%c%c  ", c,
			root->info.st_mode & S_IRUSR ? 'r' : '-',
			root->info.st_mode & S_IWUSR ? 'w' : '-',
			root->info.st_mode & S_IXUSR ? 'x' : '-',
			root->info.st_mode & S_IRGRP ? 'r' : '-',
			root->info.st_mode & S_IWGRP ? 'w' : '-',
			root->info.st_mode & S_IXGRP ? 'x' : '-',
			root->info.st_mode & S_IROTH ? 'r' : '-',
			root->info.st_mode & S_IWOTH ? 'w' : '-',
			root->info.st_mode & S_IXOTH ? 'x' : '-');
	ft_printf("%*d %-*s  %-*s  %*d ",
			wid->links, root->info.st_nlink,
			wid->uid, (getpwuid(root->info.st_uid))->pw_name,
			wid->gid, (getgrgid(root->info.st_gid))->gr_name,
			wid->size, root->info.st_size);
	parse_time(root->info.st_mtime);
	ft_printf(" %s\n", root->name);
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
		write(1, " ", 1);
		while (++i < 24)
			write(1, &mtime[i], 1);
	}
	else
		while (i < 16)
			write(1, &mtime[i++], 1);
}
