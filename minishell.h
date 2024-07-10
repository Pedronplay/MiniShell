/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogosan <diogosan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 10:37:41 by diogosan          #+#    #+#             */
/*   Updated: 2024/07/10 15:59:24 by diogosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libraries/libft/libft.h"
# include "libraries/printf/ft_printf.h"

# include <readline/readline.h>
# include <readline/history.h>

typedef enum e_exit
{
	SUCCESS,
	FAILURE,
}	t_exit;

typedef enum e_type
{
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT,
	WORDS,
	FLAG,
	MATH,
	PIPE
}	t_type;

typedef struct s_token
{
	char			*data;
	t_type			type;
	struct s_token	*next;
}	t_token;

void	hello_print(t_type name);
void	ft_print_info(t_token *token);

void	ft_init_token(t_token *token, char *data);
void	ft_data_type(t_token *token);
int		ft_syntax_checker(char *input);
char	*ft_pipe_spliter(char *str);

int		ft_strcmp(const char *s1, const char *s2);
#endif
