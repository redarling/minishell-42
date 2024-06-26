/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 00:09:18 by imehdid           #+#    #+#             */
/*   Updated: 2024/04/29 22:29:52 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	size_double_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return (0);
	while (array[i])
		i++;
	return (i);
}

void	free_double_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free (array);
}

void	free_all_nodes(t_astnode *root)
{
	if (!root)
		return ;
	free_all_nodes(root->left);
	free_all_nodes(root->right);
	if (root->value)
	{
		free(root->value);
		root->value = NULL;
	}
	free(root);
	root = NULL;
}

int	ft_strcmp(char *one, char *two)
{
	int	i;

	i = 0;
	if (ft_strlen(one) != ft_strlen(two))
		return (0);
	while (one[i])
	{
		if (one[i] != two[i])
			return (0);
		i++;
	}
	return (1);
}

int	contain_str(char **array, char *element)
{
	int	i;

	i = 0;
	while (array[i])
	{
		if (ft_strcmp(element, array[i]))
			return (1);
		i++;
	}
	return (0);
}
