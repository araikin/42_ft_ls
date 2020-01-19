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

int		check_dir(unsigned int flags, t_dirent *dp)
{
	if (flags & A_UPP && !(flags & A_LOW))
	{
		if (!ft_strcmp(dp->d_name, ".") || !ft_strcmp(dp->d_name, ".."))
			return (0);
		return (1);
	}
	else if (!(flags & A_LOW))
	{
		if (dp->d_name[0] == '.')
			return (0);
		return (1);
	}
	return (1);
}


void	set_dirinfo(unsigned int flags, t_file **file, char *name)
{
	DIR			*dir;
	t_dirent	*dp;

	dir = opendir(name);
	while ((dp = readdir(dir)))
		if (check_dir(flags, dp))
			*file = flags & T_LOW ? insert_time(*file, new_node(dp->d_name)) :
				insert_ascii(*file, new_node(dp->d_name));
	closedir(dir);
}

void	ft_ls(unsigned int flags)
{
	t_file	*file;

	file = NULL;
	set_dirinfo(flags, &file, ".");
	print_ls(flags, file);
}

void	ft_ls_arg(unsigned int flags, char *arg)
{
	if (is_dir(arg))
	{

	}
}

int		main(int ac, char **av)
{
	int				i;
	unsigned int	flags;

	(void)ac;
	i = 1;
	while (av[i] && av[i][0] == '-')
		set_lsflags(&flags, av[i++]);
	if (av[i] == NULL)
		ft_ls(flags);
	else
		while (av[i])
			ft_ls_arg(flags, ft_strdup(av[i++]));
	return (0);
}
