/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 19:34:05 by imehdid           #+#    #+#             */
/*   Updated: 2024/02/23 17:26:59 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_tree(t_astnode *root)
{
	if (!root)
		return ;
	printf ("Type: %d, Value: %s\n", root->type, root->value);
	print_tree (root->left);
	print_tree (root->right);
}

int	main(void)
{
	char		*input;
	t_astnode	*ast_root;

	ast_root = NULL;
	while (1)
	{
		input = readline("BestShell 😎 >>> ");
		if (!input)
		{
			free(input);
			program_exit(1);
		}
		ast_root = parsing(input);
		if (ast_root)
		{
			print_tree(ast_root);
			if (handle_commands(input) == 1)
			{
				free_all_nodes(ast_root);
				free(input);
				program_exit(1);
			}
			free_all_nodes(ast_root);
		}
		free(input);
	}
	return (0);
}
