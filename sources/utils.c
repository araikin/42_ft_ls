/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asultanb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 16:33:36 by asultanb          #+#    #+#             */
/*   Updated: 2020/01/28 17:44:47 by asultanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

extern int g_flag;

void	set_options(uint16_t *opt, char *s, int i)
{
	while (s[++i])
	{
		if (s[i] == 'a')
			*opt = *opt | A_LOW;
		if (s[i] == 'f')
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
	else if (is_dir(arg) == 1)
	{
		if (!(dir = opendir(arg)) && g_flag)
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
	if (*f)
		(*f)->total = t;
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
		if (wid->size < ft_digitcnt((int)root->info.st_size))
			wid->size = ft_digitcnt((int)root->info.st_size);
		set_wid(root->right, wid);
	}
}

void	iterate_args(uint16_t opt, char **args, t_wid *wid)
{
	t_file	*f;
	int		i;
	char	*tmp;

	f = NULL;
	i = -1;
	while (args[++i])
	{
		if (is_dir(args[i]) == 1)
		{
			tmp = ft_strdup(args[i]);
			set_info(opt, &f, tmp);
			set_wid(f, wid);
			free(tmp);
		}
	}
	destroy_file(f);
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
			print_ls(opt, f, wid, 1);
			if (opt & R_UPP)
				iter_r(opt, tmp, wid, f);
			destroy_file(f);
			free(tmp);
			check++;
		}
		else
			ls_output(2, args[i]);
	}
}
