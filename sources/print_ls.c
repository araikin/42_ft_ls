/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asultanb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 15:40:32 by asultanb          #+#    #+#             */
/*   Updated: 2020/01/28 18:02:24 by asultanb         ###   ########.fr       */
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

void	print_name(uint16_t opt, t_file *file)
{
	if (S_ISLNK(file->info.st_mode))
		return (print_link(opt, file));
	if (opt & G_UPP)
	{
		if (S_ISDIR(file->info.st_mode))
			write(1, "\x1b[34m", 5);
		else if (S_ISSOCK(file->info.st_mode))
			write(1, "\x1b[32m", 5);
		else if (S_ISBLK(file->info.st_mode))
			write(1, "\x1b[36m", 5);
		else if (S_ISCHR(file->info.st_mode) ||
				S_ISFIFO(file->info.st_mode))
			write(1, "\x1b[30m", 5);
		else if (S_ISREG(file->info.st_mode) &&
				(file->info.st_mode & S_IXUSR ||
				file->info.st_mode & S_IXGRP ||
				file->info.st_mode & S_IXOTH))
			write(1, "\x1b[31m", 5);
	}
	ft_printf("%s", file->name);
	write(1, "\x1b[0m", 5);
	if ((opt & F_UPP) && (opt & L_LOW))
		print_type(file);
	ft_printf("\n");
}

void	ls_output(int mode, char *arg)
{
	char	*tmp;
	int		i;
	int		k;

	tmp = NULL;
	k = 0;
	if (mode == 1)
	{
		ft_printf("ls: illegal option -- %c\n", arg[0]);
		ft_printf("usage: ./ft_ls [-AGFRSaflrt] [file ...]\n");
		exit(EXIT_FAILURE);
	}
	else if (mode == 2)
		ft_printf("ls: %s: No such file or directory\n", arg);
	else if (mode == 3)
	{
		i = -1;
		while (arg[++i])
			if (arg[i] == '/')
				k = i + 1;
		tmp = k > 0 ? ft_strdup(&arg[k]) : ft_strdup(arg);
		ft_printf("ls: %s: Permission denied\n", tmp);
		free(tmp);
	}
}
