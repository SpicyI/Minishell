/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 14:53:59 by azakariy          #+#    #+#             */
/*   Updated: 2023/02/18 19:18:58 by del-khay         ###   ########.fr       */
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
	g_gfl.pid = 0;
	g_gfl.crp = 0;
}

void	ft_reset(char *line, t_cmds *cmds, int nl)
{
	ft_set_signals();
	signal(SIGQUIT, sigquit_handler);
	signal(SIGINT, sigint_handler);
	g_gfl.syntax_error = 0;
	g_gfl.p_error_index = -1;
	g_gfl.pipeline_error = NULL;
	if (line && nl == 0)
		free(line);
	if (cmds)
	{
		ft_free_struct(cmds);
		if (cmds->line)
			free(cmds->line);
		free(cmds);
	}
}

void	ft_read_loop(int nl, char *line, t_cmds *cmds)
{
	struct termios	oldterm[2];

	ft_signals(oldterm);
	while (1)
	{
		tcsetattr(0, TCSANOW, &oldterm[0]);
		line = ft_get_line(nl, line);
		tcsetattr(0, TCSANOW, &oldterm[1]);
		ft_pipe_syntax(line, 0);
		if (line[ft_strlen(line) - 1] == '|' && !g_gfl.pipeline_error)
			nl = 1;
		else if (line[0] == '|' && nl == 0)
			ft_throw_error(line, 0);
		else if (ft_strlen(line))
		{
			cmds = ft_parsing(line, 0);
			if (!g_gfl.syntax_error && g_gfl.p_error_index == -1)
				executor(cmds);
			nl = 0;
		}
		ft_reset(line, cmds, nl);
		cmds = NULL;
	}
	free(line);
}

t_cmds	*ft_parsing(char *line, int i)
{
	t_cmds	*cmds;
	char	***parts;
	int		j;

	cmds = ft_calloc(sizeof(t_cmds), 1);
	parts = ft_double_spit(line, cmds);
	while (parts[i] && i != g_gfl.p_error_index)
	{
		ft_init_struct(cmds->line + i);
		ft_prod_line(parts[i], cmds->line + i, !parts[i + 1]);
		i++;
	}
	j = 0;
	while (parts[j])
	{
		ft_free_double(parts[j]);
		j++;
	}
	ft_doc_doc(cmds->line, i);
	free(parts);
	return (cmds);
}

int	main(int argc, char **argv, char **envp)
{
	t_cmds	*cmds;
	char	*line;

	cmds = NULL;
	line = NULL;
	(void)argc;
	(void)argv;
	ft_init_global(envp);
	ft_read_loop(0, line, cmds);
	return (0);
}
