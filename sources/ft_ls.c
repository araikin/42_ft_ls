/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asultanb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 15:05:12 by asultanb          #+#    #+#             */
/*   Updated: 2020/02/07 13:27:10 by asultanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int		main(int ac, char **av)
{
	int			i;
	uint16_t	opt;
	t_wid		wid;

	i = 1;
	ft_bzero(&wid, sizeof(t_wid));
	while (av[i] && av[i][0] == '-' && av[i][1] && ac--)
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
	ft_bzero(wid, sizeof(t_wid));
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
	opt & T_LOW ? sort_time_args(args) : ft_strsort(args);
	while (args[++i])
		if (is_file(args[i]))
			set_info(opt, &f, args[i]);
	check = f == NULL ? 0 : 1;
	opt & L_LOW ? set_wid(f, wid) : 0;
	print_ls(opt, f, wid, 0);
	destroy_file(f);
	i = -1;
	while (args[++i])
	{
		if (is_dir(args[i]) == 1)
		{
			check > 0 ? ft_putchar('\n') : 0;
			ft_printf("%s:\n", args[i]);
			ft_ls_one_arg(opt, ft_strdup(args[i]), wid);
			check++;
		}
	}
}

void	r_upp(uint16_t opt, char *path, t_wid *wid, t_file *f)
{
	char	*tmp;
	DIR		*d;

	tmp = ft_strcjoin(path, '/', f->name);
	if (ft_strcmp(f->name, ".") && ft_strcmp(f->name, "..") && !is_file(tmp))
	{
		if (!(d = opendir(tmp)))
		{
			ft_printf("\n%s:\n", tmp);
			ls_output(3, f->name);
			free(tmp);
		}
		else
		{
			closedir(d);
			ft_printf("\n%s:\n", tmp);
			ft_ls_one_arg(opt, tmp, wid);
		}
	}
	else
		free(tmp);
}

void	iter_r(uint16_t opt, char *path, t_wid *wid, t_file *d)
{
	if (d != NULL)
	{
		iter_r(opt, path, wid, d->left);
		if (!S_ISLNK(d->info.st_mode))
			r_upp(opt, path, wid, d);
		iter_r(opt, path, wid, d->right);
	}
}
