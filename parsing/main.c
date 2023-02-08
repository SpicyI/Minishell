/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 14:53:59 by azakariy          #+#    #+#             */
/*   Updated: 2023/02/08 17:17:42 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_global(char **envp)
{
	g_gfl = malloc(sizeof(t_line));
	g_gfl->exit = 0;
	g_gfl->env = ft_link(envp);
	g_gfl->syntax_error = 0;
	g_gfl->pipeline_error = NULL;
	g_gfl->p_error_index = -1;
}

void	ft_reset(char *line)
{
	g_gfl->syntax_error = 0;
	g_gfl->p_error_index = -1;
	// if (g_gfl->pipeline_error)
	// 	free(g_gfl->pipeline_error);
	g_gfl->pipeline_error = NULL;
	free(line);
	line = NULL;
}

void	ft_read_loop(void)
{
	int		nl;
	t_cmds	*cmds;
	char	*line;

	nl = 0;
	while (1)
	{
		if (nl)
			line = ft_strjoin(line, ft_strtrim(readline("> "), " "));
		else
			line = ft_strtrim(readline("WEIRDOO$ "), " ");
		add_history(line);
		ft_pipe_syntax(line, 0, 0, 0);
		if (line[ft_strlen(line) - 1] == '|')
			nl = 1;	
		else if (line[0] == '|' && nl == 0)
			ft_throw_error(line, 0);
		else if (ft_strlen(line))
		{
			cmds = ft_parsing(line, 0);
			executor(cmds);
			ft_reset(line);
			nl = 0;
			
		}
	}
}

t_cmds	*ft_parsing(char *line, int i)
{
	t_cmds	*cmds;
	char	***parts;

	cmds = ft_calloc(sizeof(t_cmds), 1);
	parts = ft_double_spit(line, cmds);
	while (parts[i] && i != g_gfl->p_error_index)
	{
		cmds->line[i] = malloc(sizeof(t_cmd));
		ft_init_struct(cmds->line[i]);
		ft_prod_line(parts[i], cmds->line[i], !parts[i + 1]);
		ft_print_struct(cmds->line[i]);
		printf("\n");
		i++;
	}
	ft_doc_doc(cmds->line, i);
	return (cmds);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	ft_init_global(envp);
	ft_read_loop();
	return (0);
}
