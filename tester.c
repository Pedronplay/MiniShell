/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogosan <diogosan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 10:45:00 by diogosan          #+#    #+#             */
/*   Updated: 2024/07/10 16:02:08 by diogosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	hello_print(t_type name)
{
	if (name == CD)
		ft_println("hello its CD");
	else
		ft_println("da fck is this");
}

static char	*type_to_string(t_type type)
{
	if (type == ECHO)
		return ("ECHO");
	else if (type == CD)
		return ("CD");
	else if (type == PWD)
		return ("PWD");
	else if (type == EXPORT)
		return ("EXPORT");
	else if (type == UNSET)
		return ("UNSET");
	else if (type == ENV)
		return ("ENV");
	else if (type == EXIT)
		return ("EXIT");
	else if (type == WORDS)
		return ("WORDS");
	else if (type == FLAG)
		return ("FLAG");
	else if (type == MATH)
		return ("MATH");
	else if (type == PIPE)
		return ("PIPE");
	else
		return ("UNKNOWN");
}


void	ft_print_info(t_token *token)
{
	t_token	*print;

	print = token;
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
}
