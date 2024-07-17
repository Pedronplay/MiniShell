/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogosan <diogosan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 10:15:33 by diogosan          #+#    #+#             */
/*   Updated: 2024/07/17 15:19:08 by diogosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libraries/libft/libft.h"
#include "minishell.h"
#include <stdbool.h>

static int	ft_check_cmd(t_token *token)
{
	if (!token->data)
		return (FAILURE);
	if (ft_strcmp(token->data, "echo") == SUCCESS)
		return (SUCCESS);
	else if (ft_strcmp(token->data, "cd") == SUCCESS)
		return (SUCCESS);
	else if (ft_strcmp(token->data, "pwd") == SUCCESS)
		return (SUCCESS);
	else if (ft_strcmp(token->data, "export") == SUCCESS)
		return (SUCCESS);
	else if (ft_strcmp(token->data, "unset") == SUCCESS)
		return (SUCCESS);
	else if (ft_strcmp(token->data, "env") == SUCCESS)
		return (SUCCESS);
	return (FAILURE);
}

static int	ft_flag_checker(t_token *token)
{
	char	*str;

	str = token->data;
	if (!str)
		return (FAILURE);
	if (str[0] == '-' || str[1] == '-')
	{
		if (ft_strchr_bool(str, ' ') == FAILURE)
			return (SUCCESS);
	}
	return (FAILURE);
}

void	ft_data_type(t_token *token, bool reset)
{
	static int	flag_check;

	if (reset)
		flag_check = 0;
	if (ft_strcmp(token->data, "<") == SUCCESS)
		token->type = R_IN;
	else if (ft_strcmp(token->data, "<<") == SUCCESS)
		token->type = R_IN2;
	else if (ft_strcmp(token->data, ">") == SUCCESS)
		token->type = R_OUT;
	else if (ft_strcmp(token->data, ">>") == SUCCESS)
		token->type = R_OUT2;
	else if (ft_strcmp(token->data, "exit") == SUCCESS)
		token->type = EXIT;
	else if (ft_strcmp(token->data, "|") == SUCCESS)
		token->type = PIPE;
	else if ((ft_flag_checker(token) == SUCCESS) && (flag_check != 1))
	{
		token->type = FLAG;
		flag_check = 1;
	}
	else if (ft_check_cmd(token) == SUCCESS)
		token->type = CMD;
	else
		token->type = STR;
}
