/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asultanb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 16:33:36 by asultanb          #+#    #+#             */
/*   Updated: 2020/01/31 14:00:23 by asultanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	set_options(uint16_t *opt, char *s, int i)
{
	while (s[++i])
	{
		if (s[i] == 'a')
			*opt = *opt | A_LOW;
		else if (s[i] == 'f')
			*opt = *opt | F_LOW;
		else if (s[i] == 'A')
			*opt = *opt | A_UPP;
		else if (s[i] == 'l')
			*opt = *opt | L_LOW;
		else if (s[i] == 't')
			*opt = *opt | T_LOW;
		else if (s[i] == 'r')
			*opt = *opt | R_LOW;
		else if (s[i] == 'R')
			*opt = *opt | R_UPP;
		else if (s[i] == 'S')
			*opt = *opt | S_UPP;
		else if (s[i] == 'G')
			*opt = *opt | G_UPP;
		else if (s[i] == 'F')
			*opt = *opt | F_UPP;
		else
			ls_output(1, &s[i]);
	}
}

void	set_info(uint16_t opt, t_file **f, char *arg)
{
	DIR			*dir;
	t_dirent	*dp;
	int			t;

	dir = NULL;
	dp = NULL;
	t = 0;
	if (is_file(arg) == 1)
		*f = insert_file(opt, *f, new_node(arg, NULL, &t));
	else if (!is_file(arg))
	{
		if (!(dir = opendir(arg)))
			ls_output(3, arg);
		else
		{
			while ((dp = readdir(dir)))
				if (check_dir(opt, dp))
					*f = insert_file(opt, *f, new_node(dp->d_name, arg, &t));
			closedir(dir);
		}
	}
	else
		ls_output(2, arg);
	*f == NULL ? ft_putstr("") : ((*f)->total = t);
}

void	set_wid(t_file *root, t_wid *wid)
{
	if (root != NULL)
	{
		set_wid(root->left, wid);
		if (wid->links < ft_digitcnt((int)root->info.st_nlink))
			wid->links = ft_digitcnt((int)root->info.st_nlink);
		if (wid->uid < (int)ft_strlen(getpwuid(root->info.st_uid)->pw_name))
			wid->uid = (int)ft_strlen(getpwuid(root->info.st_uid)->pw_name);
		if (wid->gid < (int)ft_strlen(getgrgid(root->info.st_gid)->gr_name))
			wid->gid = (int)ft_strlen(getgrgid(root->info.st_gid)->gr_name);
		if (S_ISCHR(root->info.st_mode) || S_ISBLK(root->info.st_mode))
		{
			wid->chr_blk++;
			if (wid->minor < ft_digitcnt(minor(root->info.st_rdev)))
				wid->minor = ft_digitcnt(minor(root->info.st_rdev));
			if (wid->major < ft_digitcnt(major(root->info.st_rdev)))
				wid->major = ft_digitcnt(major(root->info.st_rdev));
			if (wid->minor < wid->size)
				wid->minor = wid->size;
		}
		else if (wid->size < ft_digitcnt((int)root->info.st_size))
			wid->size = ft_digitcnt((int)root->info.st_size);
		set_wid(root->right, wid);
	}
}

void	sort_time_args(char **args)
{
	t_stat	st1;
	t_stat	st2;
	char	*tmp;
	int		i;

	i = -1;
	while (args[++i + 1])
	{
		ft_bzero(&st1, sizeof(t_stat));
		ft_bzero(&st2, sizeof(t_stat));
		lstat(args[i], &st1);
		lstat(args[i + 1], &st2);
		if (st1.st_mtime < st2.st_mtime)
		{
			tmp = args[i];
			args[i] = args[i + 1];
			args[i + 1] = tmp;
			i = -1;
		}
	}
}

void	handle_dir(uint16_t opt, char **args, t_wid *wid, int check)
{
	t_file	*f;
	int		i;
	char	*tmp;

	i = -1;
	while (args[++i])
	{
		f = NULL;
		if (is_dir(args[i]) == 1)
		{
			tmp = ft_strdup(args[i]);
			check > 0 ? ft_putchar('\n') : ft_putstr("");
			ft_printf("%s:\n", tmp);
			set_info(opt, &f, tmp);
			set_wid(f, wid);
			print_ls(opt, f, wid, 1);
			if (opt & R_UPP)
				iter_r(opt, tmp, wid, f);
			destroy_file(f);
			ft_bzero(wid, sizeof(t_wid));
			free(tmp);
			check++;
		}
	}
}
