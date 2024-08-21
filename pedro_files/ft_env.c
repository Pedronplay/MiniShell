/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pebarbos <pebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 12:12:22 by pebarbos          #+#    #+#             */
/*   Updated: 2024/08/16 17:32:28 by pebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(t_env *env, t_token *token)
{
	if (!env)
		return;
	if (token->next != NULL && token->next->type == FLAG)
	{
		ft_built_err(token, flag_err);
		return ;
	}
	while (env)
	{
		ft_printf("%s%s%s\n", env->title, "=", env->content);
		if (!env->next)
			return;
		env = env->next;
	}
}
