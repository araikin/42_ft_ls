/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asultanb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 16:42:07 by asultanb          #+#    #+#             */
/*   Updated: 2020/01/18 16:42:09 by asultanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int     is_dir(char *arg)
{
    t_stat  checkdir;

    if (lstat(arg, &checkdir))    
        return (0);
    if (!(S_ISDIR(checkdir.st_mode)))
        return (0);
    return (1);
}

int     is_file(char *arg)
{
    t_stat  checkfile;

    if (lstat(arg, &checkfile))
        return (-1); 
    if (!(S_ISDIR(checkfile.st_mode)))
        return (1);
    return (0);
}
