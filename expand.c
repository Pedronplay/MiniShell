/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogosan <diogosan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 16:56:07 by diogosan          #+#    #+#             */
/*   Updated: 2024/08/13 19:47:50 by diogosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <time.h>

char	*ft_expand_dollar(char *data, t_env *env);
//char	*ft_see_expand(char *str, t_env *env);
int		ft_see_inst_char(char *str, char c);
char	*expand_variables(char *str, t_env *env);

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

//TODO do norminette here!
void	ft_view_data(t_token **token, t_env *env)
{
	t_env	*title;
	t_token	*cur;
	char	*str;
	char	*temp;

	cur = *token;
	temp = NULL;
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
	str = ft_strchr(cur->data, '$');
	if (str)
	{
		if (!*++str)
			return ;
		else if (ft_isdigit(*str) == SUCCESS || *str == '?')
		{
			if (*str == '0')
			{
				free(cur->data);
				cur->data = ft_strdup("minishell");
			}
			else if (*str > '0' && *str <= '9')
			{
				free(cur->data);
				cur->data = ft_strdup("\n");
			}
			else
			{
				free(cur->data);
				cur->data = ft_strdup("Error code bro!");
			}
		}
		else
		{
			str = NULL;
			str = ft_expand_dollar(cur->data, env);
			free(cur->data);
			cur->data = ft_strdup(str);
			free(str);
		}
	}
}

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

int	ft_see_inst_char(char *str, char c)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (*str != c)
		i++;
	while (*str)
	{
		if (*str == c)
			i++;
		str++;
	}
	return (i);
}


t_env	*ft_get_content(t_env *env, char *title)
{
	t_env	*cur;

	cur = env;
	while (cur)
	{
		if (ft_strcmp(cur->title, title) == SUCCESS)
			return (cur);
		cur = cur->next;
	}
	return (NULL);
}

char	*expand_variables(char *str, t_env *env)
{
	char	*result;
	char	*env_value;
	int		i;
	int		j;
	int		var_start;
	t_env	*content;
	char *var_name;

	if (str[0] == '\'')
		return (ft_strdup(str));
	result = (char *)ft_calloc(500, sizeof(char));
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			var_start = i + 1;
			while (str[i + 1] != ' ' && str[i + 1] != '\0' && str[i + 1] != '"' && str[i + 1] != '$')
				i++;
			var_name = ft_fine_strdup(str, var_start, i);
			content = ft_get_content(env, var_name);
			if (content)
			{
				env_value = content->content;
				while (*env_value)
					result[j++] = *env_value++;
			}
			free(var_name);
		}
		else
			if (str[i] != '\"')
				result[j++] = str[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}





/*
char	*ft_see_expand(char *str, t_env *env)
{
	int		c;
	char	**temp;
	char	*joined;

	if (*str == '\"')
		str++;

	str++;

	c = 0;

	while (env->next)
	{
		if (ft_strncmp(str, env->title, ft_strlen(str) - 1) == 0)
			return (env->content);
		env = env->next;
	}
	return (NULL);
}
*/