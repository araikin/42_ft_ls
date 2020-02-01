/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asultanb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 10:01:20 by asultanb          #+#    #+#             */
/*   Updated: 2020/01/31 10:01:22 by asultanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	print_type(t_stat info)
{
	if (S_ISDIR(info.st_mode))
		ft_putchar('/');
	else if (S_ISLNK(info.st_mode))
		ft_putchar('@');
	else if (S_ISREG(info.st_mode) && (info.st_mode & S_IXUSR ||
			info.st_mode & S_IXGRP || info.st_mode & S_IXOTH))
		ft_putchar('*');
	else if (S_ISSOCK(info.st_mode))
		ft_putchar('=');
	else if (S_ISFIFO(info.st_mode))
		ft_putchar('|');
	else if (S_ISWHT(info.st_mode))
		ft_putchar('%');
}

void	set_color(t_stat info)
{
	if (S_ISDIR(info.st_mode) && info.st_mode & S_IWOTH)
	{
		write(1, info.st_mode & S_ISVTX ? "\x1b[42m" : "\x1b[43m", 5);
		write(1, "\x1b[30m", 5);
	}
	else if (S_ISDIR(info.st_mode))
		write(1, "\x1b[34m", 5);
	S_ISSOCK(info.st_mode) ? write(1, "\x1b[32m", 5) : 0;
	S_ISBLK(info.st_mode) ? write(1, "\x1b[46m", 5) : 0;
	S_ISCHR(info.st_mode) ? write(1, "\x1b[43m", 5) : 0;
	S_ISFIFO(info.st_mode) ? write(1, "\x1b[33m", 5) : 0;
	if (S_ISBLK(info.st_mode) || S_ISCHR(info.st_mode))
		write(1, "\x1b[34m", 5);
	if (info.st_mode & S_IXUSR || info.st_mode & S_IXGRP ||
			info.st_mode & S_IXOTH)
	{
		if (S_ISREG(info.st_mode))
			write(1, "\x1b[31m", 5);
		else if (info.st_mode & S_ISUID || info.st_mode & S_ISGID)
		{
			write(1, "\x1b[30m", 5);
			if (info.st_mode & S_ISUID)
				write(1, info.st_mode & S_ISUID ? "\x1b[41m" : "\x1b[46m", 5);
		}
	}
}
