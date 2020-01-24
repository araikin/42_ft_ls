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
		ft_ls_one_arg(flags, av[i] ? av[i] : ".", &wid);
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
	destroy_file(file);
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
		if (is_file(args[i]))
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

void	handle_dir(uint8_t flags, char **args, t_wid *wid, int check)
{
	t_file *f;
	int		i;

	i = -1;
	while (args[++i])
	{
		f = NULL;
		if (is_dir(args[i]))
		{
			set_info(flags, &f, args[i]);
			check > 0 ? ft_putchar('\n') : ft_putstr("");
			ft_printf("%s:\n", args[i]);
			print_ls(flags, f, wid, 1);
			destroy_file(f);
		}
	}
}
