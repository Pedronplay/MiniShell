
#include "minishell.h"

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
