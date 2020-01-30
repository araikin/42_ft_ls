/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asultanb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 15:40:32 by asultanb          #+#    #+#             */
/*   Updated: 2020/01/29 17:38:05 by asultanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	print_ls(uint16_t opt, t_file *file, t_wid *wid, int dir)
{
	if (file && opt & L_LOW && dir)
		ft_printf("total %d\n", file->total);
	if (opt & R_LOW)
		revorder(opt, file, wid);
	else
		inorder(opt, file, wid);
}

void	revorder(uint16_t opt, t_file *file, t_wid *wid)
{
	if (file != NULL)
	{
		revorder(opt, file->right, wid);
		if (opt & L_LOW)
			long_format(opt, file, wid);
		else
			print_name(opt, file);
		revorder(opt, file->left, wid);
	}
}

void	inorder(uint16_t opt, t_file *file, t_wid *wid)
{
	if (file != NULL)
	{
		inorder(opt, file->left, wid);
		if (opt & L_LOW)
			long_format(opt, file, wid);
		else
			print_name(opt, file);
		inorder(opt, file->right, wid);
	}
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

void	print_name(uint16_t opt, t_file *file)
{
	if (S_ISLNK(file->info.st_mode) && opt & L_LOW)
		return (print_link(opt, file));
	if (opt & G_UPP)
		set_color(file->info);
	ft_printf("%s", file->name);
	write(1, "\x1b[0m", 5);
	if (opt & F_UPP)
		print_type(file);
	ft_printf("\n");
}
