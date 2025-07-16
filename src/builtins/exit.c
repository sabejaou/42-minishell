/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:15:56 by anfichet          #+#    #+#             */
/*   Updated: 2024/06/24 19:15:57 by anfichet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static long	ft_atol(const char *str);
static int	is_numeric_arg(t_pipesep *tmp);

int	builtin_exit(t_pipesep *seps, t_envp *envp, t_exec *exec)
{
	t_pipesep	*tmp;

	tmp = seps;
	if (is_numeric_arg(tmp) == 2)
		envp->exit_status = 2;
	else if (tmp->cmd[0] && tmp->cmd[1] && tmp->cmd[2] != NULL)
	{
		printf("exit\n");
		ft_dprintf(2, "minishell: exit: too many arguments\n");
		envp->exit_status = 1;
		return (envp->exit_status);
	}
	else if (tmp->cmd[0] && tmp->cmd[1])
	{
		envp->exit_status = ft_atoi(tmp->cmd[1]);
		printf("exit\n");
	}
	else if (tmp->cmd[0] && !tmp->cmd[1])
		printf("exit\n");
	rl_clear_history();
	free_dbtab(envp->env_shell);
	free_lst_seps(&seps);
	close_builtin(exec);
	exit (envp->exit_status);
	return (envp->exit_status);
}

static int	is_numeric_arg(t_pipesep *tmp)
{
	int	j;

	j = 0;
	if (tmp->cmd[1] && (tmp->cmd[1][0] == '-' || tmp->cmd[1][0] == '+'))
		j++;
	while (tmp->cmd[1] && tmp->cmd[1][j])
	{
		if (ft_isdigit(tmp->cmd[1][j]) == 0)
		{
			printf("exit\n");
			ft_dprintf(2, "minishell: exit : %s : numeric argument required\n", \
					tmp->cmd[1]);
			return (2);
		}
		j++;
	}
	errno = 0;
	if (tmp->cmd[1] && ft_atol(tmp->cmd[1]) && errno == ERANGE)
	{
		printf("exit\n");
		ft_dprintf(2, "minishell: exit : %s : numeric argument required\n", \
				tmp->cmd[1]);
		return (2);
	}
	return (0);
}

static long	ft_atol(const char *str)
{
	size_t		i;
	long long	nb;
	int			sign;

	i = 0;
	nb = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '-')
		sign = -sign;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (((nb * 10 + str[i] - '0') / 10) != nb)
		{
			errno = ERANGE;
			if (sign < 0)
				return (LONG_MIN);
			return (LONG_MAX);
		}
		nb = nb * 10 + str[i++] - '0';
	}
	return (nb * sign);
}
