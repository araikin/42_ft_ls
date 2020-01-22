/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asultanb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 16:33:36 by asultanb          #+#    #+#             */
/*   Updated: 2020/01/16 11:33:20 by asultanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int		main(int ac, char **av)
{
	int				i;
	unsigned int	flags;

	i = 1;
	while (av[i] && av[i][0] == '-' && ac--)
		set_lsflags(&flags, av[i++]);
	if (av[i] == NULL)
		ft_ls_no_arg(flags);
	else if (ac == 2)
		ft_ls_single_arg(flags, av[i]);
	else
		ft_ls_arg(flags, &av[i]);
	return (0);
}

void	ft_ls_no_arg(unsigned int flags)
{
	t_file	*file;

	file = NULL;
	set_dirinfo(flags, &file, ".");
	print_ls(flags, file);
}

void	ft_ls_single_arg(unsigned int flags, char *arg)
{
	t_file	*file;

	file = NULL;
	if (is_file(arg))
		ft_printf("%s\n", arg);
	else if (is_dir(arg))
		set_dirinfo(flags, &file, arg);
	print_ls(flags, file);
}

void	ft_ls_arg(unsigned int flags, char **args)
{
	t_file	*f;
	t_file	*d;
	int		i;

	f = NULL;
	d = NULL;
	i = -1;
	sort_args(args);
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
	print_ls(flags, f);
	process_args(flags, d, 1);
}
