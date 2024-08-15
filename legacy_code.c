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


// long expand $~

char	*ft_expand_variables(char *str, t_env *env)
{
	char	*result;
	char	*env_value;
	int		i;
	int		j;
	int		var_start;
	t_env	*content;
	char	*var_name;
	int in_single_quote = 0;
	int in_double_quote = 0;

	result = (char *)ft_calloc(500, sizeof(char));
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (ft_set_quotes_bool(str[i], &in_double_quote, &in_single_quote))
			;
		else if (str[i] == '$' && !in_single_quote)
		{
			var_start = i + 1;
			while (str[i + 1] != ' ' && str[i + 1] != '\0'
				&& str[i + 1] != '"' && str[i + 1] != '\'' && str[i + 1] != '$')
				i++;
			var_name = ft_fine_strdup(str, var_start, i);
			content = ft_get_content(env, var_name);
			if (content || ft_strcmp(var_name, "?") == SUCCESS)
			{
				if (content)
					env_value = content->content;
				else
					env_value = "Error Code";
				while (*env_value)
					result[j++] = *env_value++;
			}
			free(var_name);
		}
		else
			if (i != 0 && i != (int)ft_strlen(str) - 1)
				result[j++] = str[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}

// long input spliter

char	*ft_input_spliter(char *str)
{
	int		size;
	char	*clean_input;
	int		c;
	int		i;

	c = 0;
	i = 0;
	size = ft_clean_size(str);
	clean_input = ft_safe_calloc(size + 1, sizeof(char));
	ft_space_skiper(str, &c);
	while (str[c] != '\0')
	{
		if (str[c] != ' ')
		{
			while (str[c] != ' ' && str[c] != '\0')
			{
				if (str[c] == '"' || str[c] == '\'')
					ft_skip_quotes_w(str, &clean_input, &c, &i);
				if ((str[c] == '|' || str[c] == '<' || str[c] == '>'))
					ft_set_space(str, &clean_input, &c, &i);
				else
				{
					if (str[c] != ' ' && str[c] != '\0')
						clean_input[i] = str[c];
				}
				c++;
				i++;
			}
		}
		else
		{
			clean_input[i++] = str[c++];
			ft_space_skiper(str, &c);
		}
	}
	clean_input[i] = '\0';
	return (clean_input);
}