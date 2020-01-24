/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asultanb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 16:33:36 by asultanb          #+#    #+#             */
/*   Updated: 2020/01/22 17:31:43 by asultanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

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

void	iterate_args(uint8_t flags, char **args, t_wid *wid)
{
	t_file	*f;
	int		i;

	f = NULL;
	i = -1;
	while (args[++i])
	{
		if (is_dir(args[i]))
		{
			set_info(flags, &f, args[i]);
			set_wid(f, wid);
		}
	}
	destroy_file(f);
}
