/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pebarbos <pebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 16:08:11 by pebarbos          #+#    #+#             */
/*   Updated: 2024/08/13 14:05:16 by pebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(t_token *token)
{
	char	cwd[256];
	
	if (token->next && token->next->type == 4)
	{
		ft_built_err(token, flag_err);
		return ;
	}
	if (token)
		getcwd(cwd, sizeof(cwd));
	ft_printf("%s\n", cwd);
}
