/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyvash <asyvash@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 15:37:27 by asyvash           #+#    #+#             */
/*   Updated: 2024/04/27 00:29:34 by asyvash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	change_to_home_dir(t_list **env)
{
	char	cwd[PATH_MAX];
	char	*home;

	home = NULL;
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("cd");
		return (126);
	}
	if (get_home_dir(&home, env))
		return (1);
	if (chdir(home) != 0)
	{
		free(home);
		perror("cd");
		return (1);
	}
	free(home);
	if (update_old_pwd_dir(env, cwd))
		return (126);
	if (update_pwd(env))
		return (126);
	return (0);
}

static int	change_to_absolute_path_dir(char *path, t_list **env)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("cd");
		return (126);
	}
	if (chdir(path) != 0)
	{
		perror("cd");
		return (1);
	}
	if (update_old_pwd_dir(env, cwd))
		return (126);
	if (update_pwd(env))
		return (126);
	return (0);
}

static int	change_to_relative_path_dir(char *path, t_list **env)
{
	char	cwd[PATH_MAX];
	char	actual_cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("cd");
		return (126);
	}
	ft_strlcpy(actual_cwd, cwd, sizeof(cwd));
	if (ft_strlen(cwd) + ft_strlen(path) + 1 > PATH_MAX)
		return (1);
	ft_strlcat(cwd, "/", sizeof(cwd));
	ft_strlcat(cwd, path, sizeof(cwd));
	if (chdir(cwd) != 0)
	{
		perror("cd");
		return (1);
	}
	if (update_old_pwd_dir(env, actual_cwd))
		return (126);
	if (update_pwd(env))
		return (126);
	return (0);
}

static int	change_to_old_pwd_dir(t_list **env)
{
	char	*old_pwd;
	char	cwd[PATH_MAX];

	old_pwd = NULL;
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("cd");
		return (126);
	}
	if (get_old_pwd(env, &old_pwd))
		return (1);
	printf("%s\n", old_pwd);
	if (chdir(old_pwd) != 0)
	{
		free(old_pwd);
		perror("cd");
		return (1);
	}
	free(old_pwd);
	if (update_old_pwd_dir(env, cwd))
		return (126);
	if (update_pwd(env))
		return (126);
	return (0);
}

int	execute_cd(char *path, t_list **env)
{
	char	thepath[PATH_MAX];
	int		code;

	ft_memset(thepath, '\0', sizeof(thepath));
	code = prepare_cd(path, thepath);
	if (code != 0)
		return (code);
	if (thepath[0] == '\0')
		return (change_to_home_dir(env));
	if (thepath[0] == '/')
		return (change_to_absolute_path_dir(thepath, env));
	else if (thepath[0] == '-' && (!thepath[1] || is_whitespace(thepath[1])))
		return (change_to_old_pwd_dir(env));
	else
		return (change_to_relative_path_dir(thepath, env));
	return (1);
}
