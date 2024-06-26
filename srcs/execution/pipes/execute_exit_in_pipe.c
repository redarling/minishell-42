/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_exit_in_pipe.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyvash <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 12:37:11 by asyvash           #+#    #+#             */
/*   Updated: 2024/04/30 12:37:18 by asyvash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	check_args_quantity(char **args)
{
	if (size_double_array(args) > 1)
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		g_last_command_status = 1;
		return (1);
	}
	return (0);
}

static int	check_all_digits(char *args)
{
	int	i;

	i = 0;
	if (!args)
		return (0);
	while (args[i])
	{
		if (!ft_isdigit(args[i]))
		{
			if (i == 0 && args[i] == '-')
			{
				i++;
				continue ;
			}
			ft_putstr_fd("exit\n", 2);
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(args, 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			g_last_command_status = 2;
			return (1);
		}
		i++;
	}
	return (0);
}

static int	errors_handler(char **args)
{
	if (ft_atoi_check_limit(args[0]) == 1)
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[0], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		g_last_command_status = 2;
		return (1);
	}
	if (check_all_digits(args[0]))
		return (1);
	if (check_args_quantity(args))
	{
		free_double_array(args);
		return (2);
	}
	return (0);
}

void	execute_exit_pipe(t_pipeline *utl, t_list **env)
{
	char	**args;
	char	*input;
	int		code;

	code = 0;
	input = get_arg_exit_pipe(utl);
	args = split_quotes_bash(input, " \t\n", NULL);
	free(input);
	free_list(env);
	if (!args)
		g_last_command_status = 126;
	trim_quotes(args, false);
	if (!args)
		g_last_command_status = 126;
	code = errors_handler(args);
	if (code == 2)
		return ;
	if (code == 0 && size_double_array(args) == 1)
		g_last_command_status = ft_atoi(args[0]);
	free_double_array(args);
	rl_clear_history();
	if (code == 0)
		ft_putstr_fd("exit\n", 2);
	exit(g_last_command_status);
}
