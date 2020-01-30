/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_format.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asultanb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 15:45:36 by asultanb          #+#    #+#             */
/*   Updated: 2020/01/29 16:43:45 by asultanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	long_format(uint16_t opt, t_file *file, t_wid *wid)
{
	print_st_mode(file);
	ft_printf("%*d %-*s  %-*s  %*d ",
		wid->links, file->info.st_nlink,
		wid->uid, (getpwuid(file->info.st_uid))->pw_name,
		wid->gid, (getgrgid(file->info.st_gid))->gr_name,
		wid->size, file->info.st_size);
	print_time(file->info.st_mtime);
	print_name(opt, file);
}

void	print_type(t_file *file)
{
	if (S_ISDIR(file->info.st_mode))
		ft_putchar('/');
	else if (S_ISLNK(file->info.st_mode))
		ft_putchar('@');
	else if (S_ISREG(file->info.st_mode) && (file->info.st_mode & S_IXUSR ||
			file->info.st_mode & S_IXGRP || file->info.st_mode & S_IXOTH))
		ft_putchar('*');
	else if (S_ISSOCK(file->info.st_mode))
		ft_putchar('=');
	else if (S_ISFIFO(file->info.st_mode))
		ft_putchar('|');
	else if (S_ISWHT(file->info.st_mode))
		ft_putchar('%');
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
	if ((opt & F_UPP) && (opt & L_LOW))
		print_type(file);
	ft_printf(" -> %s\n", link);
	free(link);
}

void	print_st_mode(t_file *file)
{
	char	c;
	char	s_uid;
	char	s_gid;
	char	st_bit;

	st_bit = file->info.st_mode & S_ISVTX ? 't' : 'x';
	s_uid = file->info.st_mode & S_ISUID ? 's' : 'x';
	s_gid = file->info.st_mode & S_ISGID ? 's' : 'x';
	c = S_ISDIR(file->info.st_mode) ? 'd' : '-';
	c = S_ISLNK(file->info.st_mode) ? 'l' : c;
	c = S_ISBLK(file->info.st_mode) ? 'b' : c;
	c = S_ISCHR(file->info.st_mode) ? 'c' : c;
	c = S_ISSOCK(file->info.st_mode) ? 's' : c;
	c = S_ISFIFO(file->info.st_mode) ? 'p' : c;
	ft_printf("%c%c%c%c%c%c%c%c%c%c%c ", c,
		file->info.st_mode & S_IRUSR ? 'r' : '-',
		file->info.st_mode & S_IWUSR ? 'w' : '-',
		file->info.st_mode & S_IXUSR ? s_uid : '-',
		file->info.st_mode & S_IRGRP ? 'r' : '-',
		file->info.st_mode & S_IWGRP ? 'w' : '-',
		file->info.st_mode & S_IXGRP ? s_gid : '-',
		file->info.st_mode & S_IROTH ? 'r' : '-',
		file->info.st_mode & S_IWOTH ? 'w' : '-',
		file->info.st_mode & S_IXOTH ? st_bit : '-',
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
