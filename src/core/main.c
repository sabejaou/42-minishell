/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabejaou <sabejaou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:13:34 by sabejaou          #+#    #+#             */
/*   Updated: 2024/06/24 19:24:07 by sabejaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	g_signal = 0;

void	main_utils(char **line, t_pipesep **seps, t_envp *envp, t_exec *exec)
{
	(void)exec;
	if ((*line)[0] && g_signal != SIGINT)
	{
		if (!ft_error(ft_checkline(*line)))
		{
			*seps = ft_pipesep(*line);
			tokeniser(seps);
			expander(seps, envp->env_shell, envp->exit_status);
			elemscat(seps);
			affect_len(*seps);
			createcmd(seps);
			if (*seps && !ft_checkelems(*seps))
			{
				execution(*seps, envp, exec);
				printf("exit status = %d\n", envp->exit_status);
			}
			free_lst_seps(&seps[0]->head);
		}
		else
			envp->exit_status = 2;
	}
	else if (g_signal == SIGINT)
		envp->exit_status = 128 + SIGINT;
}

int	init_env(t_envp *envp, int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	envp->env_shell = NULL;
	envp->exit_status = 0;
	envp->env_shell = init_envp(env);
	if (envp->env_shell == NULL)
		return (-1);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	char		*line;
	t_pipesep	*seps;
	t_envp		envp;
	t_exec		exec;

	if (init_env(&envp, ac, av, env) == -1)
		return (-1);
	while (1)
	{
		init_signal();
		line = readline(
				"\001\033[33m\033[1m\003\002minishell> \001\033[0m\002");
		if (!line)
		{
			write(1, "exit\n", 5);
			break ;
		}
		main_utils(&line, &seps, &envp, &exec);
		if (line[0] != '\0')
			add_history(line);
		free(line);
	}
	rl_clear_history();
	free_dbtab(envp.env_shell);
	return (envp.exit_status);
}
