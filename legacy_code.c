/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   legacy_code.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogosan <diogosan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 09:33:45 by diogosan          #+#    #+#             */
/*   Updated: 2024/08/14 14:09:53 by diogosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// this was to expand in little steps and i deemed unescessary

char	*ft_expand_dollar(char *data, t_env *env)
{
	char	**temp;
	char	*str;
	int		c;
	int		d;
	int		p;
	char *bob = NULL;

	p = 0;
	temp = NULL;
	c = 0;
	d = 0;
	temp = (char **)ft_calloc(ft_see_inst_char(data, '$') + 1, sizeof(char *));
	while (data[c])
	{
		if (data[c] == '\"' || data[c] == '\'')
		{
			d = c;
			ft_skip_quotes(data, &c, data[c]);
			temp[p++] = ft_fine_strdup(data, d, c);
			c++;
			if (data[c] == '\0')
				break ;
		}
		else if (data[c] == '$')
		{
			d = c;
			c++;
			while (data[c] != '$' && data[c] != '\"' && data[c] != '\'' && data[c] != '\0')
				c++;
			temp[p++] = ft_fine_strdup(data, d, c - 1);
		}
		else
			c++;

	}
	c = 0;
	while (temp[c])
	{
		//bob = ft_see_expand(temp[c], env);
		bob = expand_variables(temp[c], env);
		if (bob && ft_strcmp(bob, temp[c]) != SUCCESS)
		{
			free(temp[c]);
			temp[c] = ft_strdup(bob);
			free(bob);
		}
		c++;
	}
	str = ft_array_strjoin(temp);
	char **cur = temp;
	while (*temp)
		free(*temp++);
	free(cur);

	return (str);
}


// expanding ~

str = ft_strchr(cur->data, '~');
	if (str)
	{
		title = ft_get_content(env, "HOME");
		if (!*++str)
		{
			free(cur->data);
			cur->data = ft_strdup(title->content);
		}
		else if (*str == '/')
		{
			temp = ft_strcat(title->content, str);
			free(cur->data);
			cur->data = ft_strdup(temp);
			free(temp);
		}
	}