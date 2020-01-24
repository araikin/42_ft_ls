/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_ls.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asultanb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 11:07:53 by asultanb          #+#    #+#             */
/*   Updated: 2020/01/23 17:49:06 by asultanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

t_file	*new_node(char *name, char *path)
{
	t_file	*new_node;
	char	*tmp;
	int		res;

	if (!(new_node = (t_file *)malloc(sizeof(t_file))))
		return (NULL);
	if (path)
	{
		tmp = (path[ft_strlen(path) - 1] == '/') ? ft_strjoin(path, name) :
			ft_strcjoin(path, '/', name);
		res = lstat(tmp, &new_node->info);
		free(tmp);
	}
	else
		res = lstat(name, &new_node->info);
	if (res == -1)
	{
		free(new_node);
		return (NULL);
	}
	new_node->name = ft_strdup(name);
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->total += new_node->info.st_blocks;
	return (new_node);
}

void	set_info(uint8_t flags, t_file **file, char *arg)
{
	DIR			*dir;
	t_dirent	*dp;
	t_file		*node;

	dir = NULL;
	dp = NULL;
	node = NULL;
	if (is_file(arg))
		*file = (flags & T_LOW) ? insert_time(*file, new_node(arg, NULL)) :
			insert_ascii(*file, new_node(arg, NULL));
	else
	{
		dir = opendir(arg);
		while ((dp = readdir(dir)))
		{
			if (check_dir(flags, dp))
			{
				node = new_node(dp->d_name, arg);
				*file = (flags & T_LOW) ? insert_time(*file, node) :
					insert_ascii(*file, node);
			}
			(*file)->total += node->info.st_blocks;
		}
		closedir(dir);
	}
}

void	proc_args(uint8_t flags, t_file *d, int n, t_wid *wid)
{
	t_file	*new;

	new = NULL;
	if (d != NULL)
	{
		proc_args(flags, d->left, n + 1, wid);
		n > 0 ? ft_printf("\n") : ft_printf("");
		ft_printf("%s:\n", d->name);
		set_info(flags, &new, d->name);
		print_ls(flags, new, wid);
		proc_args(flags, d->right, n + 1, wid);
	}
	destroy_file(new);
}

t_file	*insert_time(t_file *root, t_file *new_node)
{
	if (root == NULL)
		return (new_node);
	if (root->info.st_mtime < new_node->info.st_mtime)
		root->left = insert_time(root->left, new_node);
	else
		root->right = insert_time(root->right, new_node);
	return (root);
}

t_file	*insert_ascii(t_file *root, t_file *new_node)
{
	if (root == NULL)
		return (new_node);
	if (ft_strcmp(root->name, new_node->name) > 0)
		root->left = insert_ascii(root->left, new_node);
	else
		root->right = insert_ascii(root->right, new_node);
	return (root);
}
