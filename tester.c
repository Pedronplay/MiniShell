/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogosan <diogosan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 10:45:00 by diogosan          #+#    #+#             */
/*   Updated: 2024/08/01 17:04:26 by diogosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*type_to_string(t_type type)
{
	if (type == BUILT_IN)
		return ("Built_in");
	else if (type == EXIT)
		return ("exit");
	else if (type == FLAG)
		return ("FLAG");
	else if (type == R_IN)
		return ("R_IN");
	else if (type == R_IN2)
		return ("R_IN2");
	else if (type == EXIT)
		return ("EXIT");
	else if (type == R_OUT)
		return ("R_OUT");
	else if (type == R_OUT2)
		return ("R_OUT2");
	else if (type == PIPE)
		return ("PIPE");
	else
		return ("STR");
}


void	ft_print_info(t_token *token)
{
	t_token	*print;

	print = token;
	ft_println("-----------------------");
	while (print)
	{
		ft_println("text is: %s", print->data);
		ft_println("type is: %s", type_to_string(print->type));
		if (print->next != NULL)
		{
			ft_println("the next node is: %s", print->next->data);
			ft_printf("\n");
		}
		else
			ft_println("the next node is: no next node");
		print = print->next;
	}
	ft_println("-----------------------");
}
