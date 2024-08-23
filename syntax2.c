/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogosan <diogosan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 10:21:23 by diogosan          #+#    #+#             */
/*   Updated: 2024/08/20 13:44:32 by diogosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_validation_input(char *input)
{
	if (ft_syntax_pipes(input) != SUCCESS)
		return (FAILURE);
	if (ft_syntax_redirects(input) != SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}
