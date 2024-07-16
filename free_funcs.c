/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogosan <diogosan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:34:55 by diogosan          #+#    #+#             */
/*   Updated: 2024/07/16 16:55:53 by diogosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_token *stack)
{
	t_token	*current;

	if (NULL == stack)
		return ;
	current = stack;
	while (current)
	{
		if (current->data)
			free(current->data);
		current = current->next;
	}
	free(stack);
}
