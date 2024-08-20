/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogosan <diogosan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 10:34:42 by diogosan          #+#    #+#             */
/*   Updated: 2024/08/20 14:13:01 by diogosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_commands	*ft_build_commands(t_token *token, t_env *env)
{
	(void)env;
	while (token)
		token = token->next;
	return (NULL);
}
