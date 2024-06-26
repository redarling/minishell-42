/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 15:37:38 by asyvash           #+#    #+#             */
/*   Updated: 2024/04/28 18:09:50 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	errors_handler_env(char *args)
{
	int	i;

	i = 0;
	if (args)
	{
		while (args[i] && is_whitespace(args[i]))
			i++;
		if (args[i] != '\0')
		{
			ft_putstr_fd("env: ", STDERR_FILENO);
			ft_putstr_fd(args + i, STDERR_FILENO);
			ft_putstr_fd(": Env command don't take arguments or options",
				STDERR_FILENO);
			ft_putstr_fd(" in Minishell\n",
				STDERR_FILENO);
			return (2);
		}
	}
	return (0);
}

int	execute_env(char **envp, char *args)
{
	int	i;

	i = 0;
	if (!envp)
		return (1);
	if (errors_handler_env(args))
		return (2);
	while (envp[i] != NULL)
	{
		ft_putstr_fd(envp[i], STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		i++;
	}
	return (0);
}
