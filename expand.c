/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogosan <diogosan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 16:56:07 by diogosan          #+#    #+#             */
/*   Updated: 2024/08/01 17:06:50 by diogosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_find_expand(t_token **token, t_env *env)
{
	t_token	*cur;

	cur = *token;
	while (cur)
	{
		ft_view_data(&cur, env);
		cur = cur->next;
	}
}

void	ft_view_data(t_token **token, t_env *env)
{
	int		c;
	t_env	*title;
	t_token	*cur;

	cur = *token;
	c = 0;
	title = ft_get_content(env, "HOME");
	if (ft_strcmp(cur->data, "~") == SUCCESS)
	{
		free(cur->data);
		cur->data = ft_strdup(title->content);
		ft_println("%s", cur->data);
	}

}

t_env	*ft_get_content(t_env *env, char *title)
{
	t_env	*cur;
	int		c;

	c = 0;
	cur = env;
	while (cur)
	{
		if (ft_strcmp(cur->title, title) == SUCCESS)
			return (cur);
		cur = cur->next;
	}
	return (env);
}

