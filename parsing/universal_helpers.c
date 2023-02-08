/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   universal_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 16:28:32 by azakariy          #+#    #+#             */
/*   Updated: 2023/02/08 17:07:41 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_struct(t_cmd *cmd)
{
	int	i;

	i = 0;
	printf("| Is built in : %s |\n", cmd->is_built_in ? "yes": "no");
	printf("| cmd array : ");
	while (cmd->cmd && cmd->cmd[i])
	{
		printf("%s ", cmd->cmd[i]);
		i++;
	}
	i = 0;
	printf("|\n| append array : ");
	while (cmd->append && cmd->append[i])
	{
		printf("%s ", cmd->append[i]);
		i++;
	}
	i = 0;
	printf("|\n| delimiter array : ");
	while (cmd->delimiter && cmd->delimiter[i])
	{
		printf("%s ", cmd->delimiter[i]);
		i++;
	}
	i = 0;
	printf("|\n| output array : ");
	while (cmd->output && cmd->output[i])
	{
		printf("%s ", cmd->output[i]);
		i++;
	}
	i = 0;
	printf("|\n| input array : ");
	while (cmd->input && cmd->input[i])
	{
		printf("%s ", cmd->input[i]);
		i++;
	}
	printf("|\n| is syntax error: %s", g_gfl->syntax_error ? "yes":"no");
	printf("|\n|");
}


char	**ft_destructor(char **array, char **array2)
{
	int		i;
	int		j;
	char	**new_array;

	i = 0;
	while (array && array[i])
		i++;
	j = 0;
	while (array2 && array2[j])
		j++;
	new_array = malloc(sizeof(char *) * (i + j + 1));
	i = 0;
	while (array && array[i])
	{
		new_array[i] = array[i];
		i++;
	}
	j = 0;
	while (array2 && array2[j])
	{
		new_array[i + j] = array2[j];
		j++;
	}
	new_array[i + j] = NULL;
	return (new_array);
}

char	*ft_append_char(char *str, char c)
{
	int		i;
	char	*new_str;
	int		j;

	i = 0;
	if (str)
		j = ft_strlen(str);
	else
		j = 0;
	new_str = malloc(sizeof(char) * (j + 2));
	new_str[j + 1] = '\0';
	while (str && str[i])
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = c;
	if (str)
		free(str);
	return (new_str);
}

char	*ft_remove_quotes(char *str)
{
	int		i;
	int		in_d;
	int		in_s;
	char	*new_str;

	i = 0;
	in_d = 0;
	in_s = 0;
	new_str = NULL;
	while (str[i])
	{
		if (str[i] == '"' && !in_s)
			in_d = !in_d;
		else if (str[i] == '\'' && !in_d)
			in_s = !in_s;
		else if ((!in_d && in_s) || (in_d && !in_s))
			new_str = ft_append_char(new_str, str[i]);
		else if (!in_d && !in_s)
			new_str = ft_append_char(new_str, str[i]);
		i++;
	}
	free(str);
	return (new_str);
}

int	ft_skip(char *line, int i, char c)
{
	int	in_d;
	int	in_s;

	in_d = 0;
	in_s = 0;
	while (line[i])
	{
		if (line[i] == c && !in_d && !in_s)
			break ;
		if (line[i] == '\'' && !in_d)
			in_s = !in_s;
		else if (line[i] == '"' && !in_s)
			in_d = !in_d;
		i++;
	}
	return (i);
}
