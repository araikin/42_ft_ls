/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_ls.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asultanb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 15:05:22 by asultanb          #+#    #+#             */
/*   Updated: 2020/01/30 15:12:35 by asultanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

t_file	*new_node(char *name, char *path, int *total)
{
	t_file	*new_node;
	int		res;

	if (!(new_node = (t_file *)malloc(sizeof(t_file))))
		return (NULL);
	if (name)
	{
		new_node->path = ft_strcjoin(path, '/', name);
		res = lstat(new_node->path, &new_node->info);
		if (res == -1)
		{
			free(new_node);
			return (NULL);
		}
		new_node->name = ft_strdup(name);
		new_node->left = NULL;
		new_node->right = NULL;
		*total += new_node->info.st_blocks;
	}
	return (new_node);
}

t_file	*insert_file(uint16_t opt, t_file *f, t_file *new)
{
	if (opt & F_LOW)
	{
		if (f == NULL)
			return (new);
		if (!ft_strcmp(new->name, ".") || !ft_strcmp(new->name, ".."))
			return (by_ascii(f, new));
		f->right = insert_file(opt, f->right, new);
		return (f);
	}
	if (opt & S_UPP)
		return (by_size(f, new));
	else if (opt & T_LOW)
		return (by_time(f, new));
	return (by_ascii(f, new));
}

t_file	*by_time(t_file *f, t_file *new)
{
	if (f == NULL)
		return (new);
	if (f->info.st_mtimespec.tv_sec < new->info.st_mtimespec.tv_sec)
		f->left = by_time(f->left, new);
	else if (f->info.st_mtimespec.tv_sec > new->info.st_mtimespec.tv_sec)
		f->right = by_time(f->right, new);
	else
	{
		if (f->info.st_mtimespec.tv_nsec < new->info.st_mtimespec.tv_nsec)
			f->left = by_time(f->left, new);
		else if (f->info.st_mtimespec.tv_nsec > new->info.st_mtimespec.tv_nsec)
			f->right = by_time(f->right, new);
		else
		{
			if (ft_strcmp(f->name, new->name) > 0)
				f->left = by_time(f->left, new);
			else
				f->right = by_time(f->right, new);
		}
	}
	return (f);
}

t_file	*by_size(t_file *f, t_file *new)
{
	if (f == NULL)
		return (new);
	if (f->info.st_size < new->info.st_size)
		f->left = by_size(f->left, new);
	else if (f->info.st_size > new->info.st_size)
		f->right = by_size(f->right, new);
	else
	{
		if (ft_strcmp(f->name, new->name) > 0)
			f->left = by_size(f->left, new);
		else
			f->right = by_size(f->right, new);
	}
	return (f);
}

t_file	*by_ascii(t_file *f, t_file *new)
{
	if (f == NULL)
		return (new);
	if (ft_strcmp(f->name, new->name) > 0)
		f->left = by_ascii(f->left, new);
	else
		f->right = by_ascii(f->right, new);
	return (f);
}
