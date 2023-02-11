/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 14:53:59 by azakariy          #+#    #+#             */
/*   Updated: 2023/02/11 20:20:20 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_global(char **envp)
{
	g_gfl.exit = 0;
	g_gfl.env = ft_link(envp);
	g_gfl.syntax_error = 0;
	g_gfl.pipeline_error = NULL;
	g_gfl.p_error_index = -1;
	g_gfl.not_env = NULL;
	g_gfl.pid = NULL;
	g_gfl.crp = 0;
}

void	ft_reset(char *line, t_cmds *cmds)
{
	g_gfl.syntax_error = 0;
	g_gfl.p_error_index = -1;
	g_gfl.pipeline_error = NULL;
	free(line);
	line = NULL;
	ft_free_struct(cmds);
}

void	ft_read_loop(int nl)
{
	t_cmds	*cmds;
	char	*line;

	signal(SIGINT, sigint_handler);
	while (1)
	{
		if (nl)
			line = ft_strjoin(line, ft_trim(ft_color(0), " "));
		else
			line = ft_trim(ft_color(1), " ");
		add_history(line);
		ft_pipe_syntax(line, 0, 0, 0);
		if (line[ft_strlen(line) - 1] == '|' && !g_gfl.pipeline_error)
			nl = 1;
		else if (line[0] == '|' && nl == 0)
			ft_throw_error(line, 0);
		else if (ft_strlen(line))
		{
			cmds = ft_parsing(line, 0);
			if (!g_gfl.syntax_error && g_gfl.p_error_index == -1)
				executor(cmds);
			ft_reset(line, cmds);
			nl = 0;
		}
	}
	free(line);
}

t_cmds	*ft_parsing(char *line, int i)
{
	t_cmds	*cmds;
	char	***parts;

	cmds = ft_calloc(sizeof(t_cmds), 1);
	parts = ft_double_spit(line, cmds);
	while (parts[i] && i != g_gfl.p_error_index)
	{
		ft_init_struct(cmds->line + i);
		ft_prod_line(parts[i], cmds->line + i, !parts[i + 1]);
		i++;
	}
	while (i < cmds->size)
	{
		ft_free_double(parts[i]);
		i++;
	}
	free(parts);
	ft_doc_doc(cmds->line, i);
	return (cmds);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	ft_init_global(envp);
	ft_read_loop(0);
	return (0);
}
