/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_print_ls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asultanb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 11:51:53 by asultanb          #+#    #+#             */
/*   Updated: 2020/01/22 17:12:12 by asultanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	handle_width(uint8_t flags, t_file *d, t_wid *wid)
{
	t_file	*new;

	new = NULL;
	if (d != NULL)
	{
		handle_width(flags, d->left, wid);
		set_info(flags, &new, d->name);
		set_widwid(d, wid);
		handle_width(flags, d->right, wid);
	}
	free(new);
}

void	set_widwid(t_file *root, t_wid *wid)
{
	if (root != NULL)
	{
		set_widwid(root->left, wid);
		if (wid->links < ft_digitcnt((int)root->info.st_nlink))
			wid->links = ft_digitcnt((int)root->info.st_nlink);
		if (wid->uid < (int)ft_strlen(getpwuid(root->info.st_uid)->pw_name))
			wid->uid = (int)ft_strlen(getpwuid(root->info.st_uid)->pw_name);
		if (wid->gid < (int)ft_strlen(getgrgid(root->info.st_gid)->gr_name))
			wid->gid = (int)ft_strlen(getgrgid(root->info.st_gid)->gr_name);
		if (wid->size < ft_digitcnt((int)root->info.st_size))
			wid->size = ft_digitcnt((int)root->info.st_size);
		set_widwid(root->right, wid);
	}
}

void	print_l_low(t_file *root, t_wid *wid)
{
	ft_printf("%c%c%c%c%c%c%c%c%c%c  ",
			S_ISDIR(root->info.st_mode) ? 'd' : '-',
			root->info.st_mode & S_IRUSR ? 'r' : '-',
			root->info.st_mode & S_IWUSR ? 'w' : '-',
			root->info.st_mode & S_IXUSR ? 'x' : '-',
			root->info.st_mode & S_IRGRP ? 'r' : '-',
			root->info.st_mode & S_IWGRP ? 'w' : '-',
			root->info.st_mode & S_IXGRP ? 'x' : '-',
			root->info.st_mode & S_IROTH ? 'r' : '-',
			root->info.st_mode & S_IWOTH ? 'w' : '-',
			root->info.st_mode & S_IXOTH ? 'x' : '-');
	ft_printf("%*d %*s  %*s  %*d ",
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
