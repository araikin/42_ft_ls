/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asultanb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 16:33:36 by asultanb          #+#    #+#             */
/*   Updated: 2020/01/22 17:08:30 by asultanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int		main(int ac, char **av)
{
	int			i;
	uint8_t		flags;
	t_wid	wid;

	i = 1;
	ft_bzero(&wid, sizeof(t_wid));
	while (av[i] && av[i][0] == '-' && ac--)
		set_lsflags(&flags, av[i++]);
	if (av[i] == NULL)
		ft_ls_no_arg(flags, &wid);
	else if (ac == 2)
		ft_ls_single_arg(flags, av[i], &wid);
	else
	{
		sort_args(&av[i]);
		ft_ls_arg(flags, &av[i], &wid);
	}
	return (0);
}

void	ft_ls_no_arg(uint8_t flags, t_wid *wid)
{
	t_file	*file;

	file = NULL;
	set_info(flags, &file, ".");
	if (flags & L_LOW)
		handle_width(flags, file, wid);
	print_ls(flags, file, wid);
	free(file);
}

void	ft_ls_single_arg(uint8_t flags, char *arg, t_wid *wid)
{
	t_file	*file;

	file = NULL;
	set_info(flags, &file, arg);
	if (flags & L_LOW)
	{
		if (is_dir(arg))
			handle_width(flags, file, wid);
		else
			set_widwid(file, wid);
	}
	print_ls(flags, file, wid);
	free(file);
}

void	ft_ls_arg(uint8_t flags, char **args, t_wid *wid)
{
	t_file	*f;
	t_file	*d;
	int		i;

	f = NULL;
	d = NULL;
	i = -1;
	while (args[++i])
	{
		if (is_dir(args[i]))
			d = (flags & T_LOW) ? insert_time(d, new_node(args[i], NULL)) :
				insert_ascii(d, new_node(args[i], NULL));
		else if (is_file(args[i]))
			f = (flags & T_LOW) ? insert_time(f, new_node(args[i], NULL)) :
				insert_ascii(f, new_node(args[i], NULL));
		else
			exit(1);
	}
	if (flags & L_LOW)
	{
		set_widwid(f, wid);
		handle_width(flags, d, wid);
	}
	print_ls(flags, f, wid);
	process_args(flags, d, (f == NULL) ? 0 : 1, wid);
}
