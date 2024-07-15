/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogosan <diogosan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 16:53:08 by diogosan          #+#    #+#             */
/*   Updated: 2024/07/15 17:04:26 by diogosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	ft_space_skiper(char *str, int *c)
{
	while (str[*c] == ' ')
		(*c)++;
}

void	ft_reset_int(int *c, int *i)
{
	(*c) = 0;
	(*i) = 0;
}

void	ft_count_helper(char *str, int *c, int *size)
{
	if (str[*c - 1] == ' ' && str[*c + 1] == ' ')
		return ;
	if (str[*c - 1] != ' ')
		(*size)++;
	if (str[*c + 1] != ' ')
		(*size)++;
}