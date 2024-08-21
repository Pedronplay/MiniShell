/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pebarbos <pebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 11:59:46 by pebarbos          #+#    #+#             */
/*   Updated: 2024/08/16 17:18:51 by pebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_cd(t_token *token)
{
	if (!token->next)
		chdir(" ");
	if (access(token->next->data, F_OK) == 0)
	{
		if (access(token->next->data, R_OK) == 0)
			chdir(token->next->data);
		else
			ft_built_err(token, file_permissions);
	}
	else
			ft_built_err(token, no_file);
	//else if (chdir(token->next->data) != 0) // sp ve se e 1 ou 0
	//	ft_printf_err("Minishell: cd: %s: No such file or directory\n", token->next->data);
}


/*
bash: cd: pasta/: Permission denied       cd to a folder that has no permissions 
bash: cd: HOME not set                    try to cd after unseting HOME
bash: cd: non_existant: No such file or directory
*/