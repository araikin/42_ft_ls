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

t_file	*insert(uint8_t opt, t_file *file, t_file *new_node)
{
	if (opt & T_LOW)
		return (insert_time(file, new_node));
	return (insert_ascii(file, new_node));
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
