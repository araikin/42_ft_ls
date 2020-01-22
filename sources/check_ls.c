/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asultanb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 16:42:07 by asultanb          #+#    #+#             */
/*   Updated: 2020/01/21 16:21:50 by asultanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int     is_dir(char *arg)
{
    t_stat  checkdir;

    if (lstat(arg, &checkdir) == -1)
        return (0);
    if (!(S_ISDIR(checkdir.st_mode)))
        return (0);
    return (1);
}

int     is_file(char *arg)
{
    t_stat  checkfile;

    if (lstat(arg, &checkfile) == -1)
        return (-1); 
    if (!(S_ISDIR(checkfile.st_mode)))
        return (1);
    return (0);
}

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

void	sort_args(char **args)
{
	char	*tmp;
	int		i;

	i = -1;
	while (args[++i + 1])
	{
		if (ft_strcmp(args[i], args[i + 1]) > 0)
		{
			tmp = args[i];
			args[i] = args[i + 1];
			args[i + 1] = tmp;
			i = -1;
		}
	}
}
