/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_ls.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asultanb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 15:05:22 by asultanb          #+#    #+#             */
/*   Updated: 2020/01/27 16:47:54 by asultanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

t_file	*new_node(char *name, char *path, int *total)
{
	t_file	*new_node;
	char	*tmp;
	int		res;

	if (!(new_node = (t_file *)malloc(sizeof(t_file))))
		return (NULL);
	if (name)
	{
		tmp = ft_strcjoin(path, '/', name);
		res = lstat(tmp, &new_node->info);
		free(tmp);
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

t_file	*insert_file(uint8_t opt, t_file *file, t_file *insert)
{
	if (opt & F_LOW)
		return (no_sort(file, insert));
	if (opt & S_UPP)
		return (by_size(file, insert));
	else if (opt & T_LOW)
		return (by_time(file, insert));
	return (by_ascii(file, insert));
}

t_file	*no_sort(t_file *root, t_file *insert)
{
	if (root == NULL)
		return (insert);
	root->right = no_sort(root->right, insert);
	return (root);
}

t_file	*by_time(t_file *root, t_file *insert)
{
	if (root == NULL)
		return (insert);
	if (root->info.st_mtimespec.tv_sec <
			insert->info.st_mtimespec.tv_sec)
		root->left = by_time(root->left, insert);
	else if (root->info.st_mtimespec.tv_sec >
			insert->info.st_mtimespec.tv_sec)
		root->right = by_time(root->right, insert); 
	else
	{
		if (root->info.st_mtimespec.tv_nsec <
				insert->info.st_mtimespec.tv_nsec)
			root->left = by_time(root->left, insert);
		else if (root->info.st_mtimespec.tv_nsec >
				insert->info.st_mtimespec.tv_nsec)
			root->right = by_time(root->right, insert);
		else
		{
			if (ft_strcmp(root->name, insert->name) > 0)
				root->left = by_time(root->left, insert);
			else
				root->right = by_time(root->right, insert);
		}
	}
	return (root);
}

t_file	*by_size(t_file *root, t_file *insert)
{
	if (root == NULL)		
		return (insert);
	if (root->info.st_size < insert->info.st_size)
		root->left = by_size(root->left, insert);
	else if (root->info.st_size > insert->info.st_size)
		root->right = by_size(root->right, insert);
	else 
	{
		if (ft_strcmp(root->name, insert->name) > 0)
			root->left = by_size(root->left, insert);
		else
			root->right = by_size(root->right, insert);
	}
	return (root);
}

t_file	*by_ascii(t_file *root, t_file *insert)
{
	if (root == NULL)
		return (insert);
	if (ft_strcmp(root->name, insert->name) > 0)
		root->left = by_ascii(root->left, insert);
	else
		root->right = by_ascii(root->right, insert);
	return (root);
}
