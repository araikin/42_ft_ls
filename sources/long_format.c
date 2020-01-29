/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_format.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asultanb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 15:45:36 by asultanb          #+#    #+#             */
/*   Updated: 2020/01/28 17:37:55 by asultanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	long_format(uint16_t opt, t_file *file, t_wid *wid)
{
	print_st_mode(file, wid);
	ft_printf("%*d %-*s  %-*s  %*d ",
		wid->links, file->info.st_nlink,
		wid->uid, (getpwuid(file->info.st_uid))->pw_name,
		wid->gid, (getgrgid(file->info.st_gid))->gr_name,
		wid->size, file->info.st_size);
	print_time(file->info.st_mtime);
	print_name(opt, file, wid);
}

void	print_name(uint16_t opt, t_file *file, t_wid *wid)
{
	if (wid->mode == 'l')
		return (print_link(opt, file));
	if (!(opt & G_UPP))
		ft_printf("%s\n", file->name);
	else
	{
		if (wid->mode == 'd')
			write(1, "\x1b[34m", 5);
		else if (wid->mode == 's')
			write(1, "\x1b[32m", 5);
		else if (wid->mode == 'b')
			write(1, "\x1b[36m", 5);
		else if (wid->mode == 'c' || wid->mode == 'p')
			write(1, "\x1b[30m", 5);
		else if (wid->mode == '-' && (file->info.st_mode & S_IXUSR ||
			file->info.st_mode & S_IXGRP || file->info.st_mode & S_IXOTH))
			write(1, "\x1b[31m", 5);
		ft_printf("%s\n", file->name);
		write(1, "\x1b[0m", 5);
	}
}

void	print_link(uint16_t opt, t_file *file)
{
	t_stat	status;
	char	*link;

	lstat(file->path, &status);
	link = (char*)malloc(sizeof(char) * (status.st_size + 1));
	readlink(file->path, link, status.st_size + 1);
	link[status.st_size] = '\0';
	if (opt & G_UPP)
		write(1, "\x1b[35m", 5);
	ft_printf("%s", file->name);
	write(1, "\x1b[0m", 5);
	ft_printf(" -> %s\n", link);
	free(link);
}

void	print_st_mode(t_file *file, t_wid *wid)
{
	wid->mode = S_ISDIR(file->info.st_mode) ? 'd' : '-';
	wid->mode = S_ISLNK(file->info.st_mode) ? 'l' : wid->mode;
	wid->mode = S_ISBLK(file->info.st_mode) ? 'b' : wid->mode;
	wid->mode = S_ISCHR(file->info.st_mode) ? 'c' : wid->mode;
	wid->mode = S_ISSOCK(file->info.st_mode) ? 's' : wid->mode;
	wid->mode = S_ISFIFO(file->info.st_mode) ? 'p' : wid->mode;
	ft_printf("%c%c%c%c%c%c%c%c%c%c%c ", wid->mode,
		file->info.st_mode & S_IRUSR ? 'r' : '-',
		file->info.st_mode & S_IWUSR ? 'w' : '-',
		file->info.st_mode & S_IXUSR ? 'x' : '-',
		file->info.st_mode & S_IRGRP ? 'r' : '-',
		file->info.st_mode & S_IWGRP ? 'w' : '-',
		file->info.st_mode & S_IXGRP ? 'x' : '-',
		file->info.st_mode & S_IROTH ? 'r' : '-',
		file->info.st_mode & S_IWOTH ? 'w' : '-',
		file->info.st_mode & S_IXOTH ? 'x' : '-',
		listxattr(file->path, NULL, 0, XATTR_NOFOLLOW) > 0 ? '@' : ' ');
}

void	print_time(time_t mod_time)
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
	write(1, " ", 1);
}
