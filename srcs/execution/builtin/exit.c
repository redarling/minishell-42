/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 15:37:41 by asyvash           #+#    #+#             */
/*   Updated: 2024/03/06 15:58:56 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	execute_exit(char *input, t_list **env, t_astnode *root, char **envp)
{
	int	code;

	code = 0;
	while (*input && (*input >= '9' || *input <= '0'))
		input++;
	if (*input >= '0' && *input <= '9')
		code = ft_atoi(input);
	else
		code = 0;
	(void)env;
	free_double_array(envp);
	free_all_nodes(root);
	exit(code);
}