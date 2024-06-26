/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyvash <asyvash@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 15:55:34 by asyvash           #+#    #+#             */
/*   Updated: 2024/04/26 23:55:00 by asyvash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	free_and_exit(char **envp, char **cmds, char *cmd_path, int code)
{
	if (cmd_path)
		free(cmd_path);
	free_double_array(cmds);
	free_double_array(envp);
	if (code != -1)
	{
		g_last_command_status = code;
		return ;
	}
	exit (0);
}

static int	get_indx(char **envp)
{
	int	i;

	i = -1;
	if (!envp)
		return (-1);
	while (envp[++i] != NULL)
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
	return (i);
}

static int	error_handling(char *cmd_path, char **cmds, char **envp)
{
	if (cmd_path == NULL && g_last_command_status == 126)
	{
		free_and_exit(envp, cmds, NULL, 126);
		return (1);
	}
	if (cmd_path == NULL)
	{
		free_and_exit(envp, cmds, NULL, 127);
		return (1);
	}
	return (0);
}

void	launch_cmd(char *cmd, char **envp, char *cmd_path, char **cmds)
{
	cmds = split_quotes_bash(cmd, " \t\n", NULL);
	trim_quotes(cmds, false);
	if ((get_indx(envp) == -1 || envp[get_indx(envp)] == NULL) && \
		cmds && access(cmds[0], F_OK) != 0)
	{
		print_error_not_found(cmds[0], 1);
		free_and_exit(envp, cmds, NULL, 127);
		return ;
	}
	cmd_path = get_path(cmds[0], envp[get_indx(envp)] + 5);
	if (error_handling(cmd_path, cmds, envp) == 1)
		return ;
	if (execve(cmd_path, cmds, envp) < 0)
	{
		print_error_not_found(cmds[0], 2);
		free_and_exit(envp, cmds, cmd_path, 126);
		return ;
	}
	free_and_exit(envp, cmds, cmd_path, -1);
}

char	*get_content(t_astnode *node)
{
	char	*content;

	if (node->type == PIPE_NODE)
		content = ft_strdup(node->left->value);
	else
		content = ft_strdup(node->value);
	if (!content)
		return (NULL);
	return (content);
}
