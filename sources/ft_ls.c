/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asultanb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 16:33:36 by asultanb          #+#    #+#             */
/*   Updated: 2020/01/24 12:42:33 by asultanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int		main(int ac, char **av)
{
	int		i;
	uint8_t	flags;
	t_wid	wid;

	i = 1;
	ft_bzero(&wid, sizeof(t_wid));
	while (av[i] && av[i][0] == '-' && ac--)
		set_lsflags(&flags, av[i++]);
	if (ac == 2 || av[i] == NULL)
		ft_ls_one_arg(flags, ft_strdup(av[i] ? av[i] : "."), &wid);
	else
		ft_ls_mul_args(flags, &av[i], &wid);
	return (0);
}

void	ft_ls_one_arg(uint8_t flags, char *arg, t_wid *wid)
{
	t_file	*file;

	file = NULL;
	set_info(flags, &file, arg);
	if (flags & L_LOW)
		set_wid(file, wid);
	print_ls(flags, file, wid, is_dir(arg) ? 1 : 0);
	if (flags & R_UPP)
		recur_start(flags, arg, wid, file);
	destroy_file(file);
	free(arg);
}

void	ft_ls_mul_args(uint8_t flags, char **args, t_wid *wid)
{
	t_file	*f;
	int		i;
	int		check;

	i = -1;
	f = NULL;
	check = 0;
	sort_args(args);
	while (args[++i])	
	{
		if (is_file(args[i]) == 1)
			set_info(flags, &f, args[i]);
		check++;
	}
	if (flags & L_LOW)
	{
		set_wid(f, wid);
		iterate_args(flags, args, wid);
	}
	print_ls(flags, f, wid, 0);
	destroy_file(f);
	handle_dir(flags, args, wid, check);
}

void	recur_process(uint8_t flags, char *path, t_wid *wid, t_file *f)
{
	char	*tmp;
	DIR		*d;

	tmp = ft_strcjoin(path, '/', f->name);	
	if ((d = opendir(tmp)) && f->name[0] != '.')
	{
		closedir(d);
		ft_printf("\n%s:\n", tmp);
		ft_ls_one_arg(flags, tmp, wid);
	}
	else
	{
		d != 0 ? closedir(d) : 0;
		free(tmp);
	}
}

void	recur_start(uint8_t flags, char *path, t_wid *wid, t_file *d)
{
	if (d != NULL)
	{
		recur_start(flags, path, wid, d->left);
		recur_process(flags, path, wid, d);
		recur_start(flags, path, wid, d->right);
	}
}
