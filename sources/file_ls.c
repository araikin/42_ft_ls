/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_ls.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asultanb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 11:07:53 by asultanb          #+#    #+#             */
/*   Updated: 2020/01/17 11:07:56 by asultanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

t_file	*new_node(char *name)
{
	t_file	*new_node;
	t_stat	info;

	if (!(new_node = (t_file *)malloc(sizeof(t_file))))
		return (NULL);
	if (stat(name, &info) == -1)
		exit(1);
	new_node->name = name;
	new_node->info = info;
	new_node->left = NULL;
	new_node->right = NULL;
	return (new_node);
}

void	revorder(t_file *root)
{
	if (root != NULL)	
	{
		revorder(root->right);
		printf("%s\n", root->name);
		revorder(root->left);
	}
}

void	inorder(t_file *root)
{
	if (root != NULL)
	{
		inorder(root->left);
		printf("%s\n", root->name);
		inorder(root->right);
	}
}

/*
t_file	*insert_ascii(t_file *node, char *name)
{
	if (node == NULL)	
		return (new_node(name));
	if (ft_strcmp(node->name, name) > 0)
		node->left = insert(node->left, name);
	else
		node->right = insert(node->right, name);
	return (node);
}

t_file	*insert_time(t_file *node, char *name)
{
	t_stat	*info;

	lstat(node->name, &info);

	if (node == NULL)	
		return (new_node(name));
	if (name.info->)
	if (ft_strcmp(node->name, name) > 0)
		node->left = insert(node->left, name);
	else
		node->right = insert(node->right, name);
	return (node);
}
*/

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
