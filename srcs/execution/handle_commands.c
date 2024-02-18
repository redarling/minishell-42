/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 17:30:15 by imehdid           #+#    #+#             */
/*   Updated: 2024/02/18 15:40:06 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int ctrl_c_pressed;

int	handle_commands(char *input)
{
	if (!input)
		return (1);
	if (handle_builtin(input))
		return (1);
	return (0);
}