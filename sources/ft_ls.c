/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asultanb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 15:05:12 by asultanb          #+#    #+#             */
/*   Updated: 2020/01/28 18:01:48 by asultanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int		g_flag = 1;

int		main(int ac, char **av)
{
	int			i;
	uint16_t	opt;
	t_wid		wid;

	i = 1;
	ft_bzero(&wid, sizeof(t_wid));
	while (av[i] && av[i][0] == '-' && ac--)
		set_options(&opt, av[i++], 0);
	if (ac == 2 || av[i] == NULL)
		ft_ls_one_arg(opt, ft_strdup(av[i] ? av[i] : "."), &wid);
	else
		ft_ls_mul_args(opt, &av[i], &wid);
	return (0);
}

void	ft_ls_one_arg(uint16_t opt, char *arg, t_wid *wid)
{
	t_file	*file;

	file = NULL;
	set_info(opt, &file, arg);
	if (opt & L_LOW)
		set_wid(file, wid);
	print_ls(opt, file, wid, is_dir(arg) ? 1 : 0);
	if (opt & R_UPP)
		iter_r(opt, arg, wid, file);
	destroy_file(file);
	free(arg);
}

void	ft_ls_mul_args(uint16_t opt, char **args, t_wid *wid)
{
	t_file	*f;
	int		i;
	int		check;

	i = -1;
	f = NULL;
	ft_strsort(args);
	while (args[++i])
		if (is_file(args[i]) == 1)
			set_info(opt, &f, args[i]);
	check = f == NULL ? 0 : 1;
	if (opt & L_LOW)
	{
		g_flag = 0;
		set_wid(f, wid);
		iterate_args(opt, args, wid);
	}
	g_flag = 1;
	print_ls(opt, f, wid, 0);
	destroy_file(f);
	handle_dir(opt, args, wid, check);
}

void	r_upp(uint16_t opt, char *path, t_wid *wid, t_file *f)
{
	char	*tmp;
	DIR		*d;

	tmp = ft_strcjoin(path, '/', f->name);
	if ((d = opendir(tmp)) &&
			ft_strcmp(f->name, ".") && ft_strcmp(f->name, ".."))
	{
		closedir(d);
		ft_printf("\n%s:\n", tmp);
		ft_ls_one_arg(opt, tmp, wid);
	}
	else if (is_dir(tmp) == 1 && !(d = opendir(tmp)) && g_flag)
	{
		ft_printf("\n%s:\n", tmp);
		ls_output(3, tmp);
	}
	else
	{
		d != 0 ? closedir(d) : 0;
		free(tmp);
	}
}

void	iter_r(uint16_t opt, char *path, t_wid *wid, t_file *d)
{
	if (d != NULL)
	{
		iter_r(opt, path, wid, d->left);
		r_upp(opt, path, wid, d);
		iter_r(opt, path, wid, d->right);
	}
}
