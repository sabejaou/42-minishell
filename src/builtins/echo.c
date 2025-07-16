/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:15:43 by anfichet          #+#    #+#             */
/*   Updated: 2024/06/24 19:15:44 by anfichet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_option(char *str);

int	builtin_echo(t_pipesep *seps, t_elem *elems, char **cmd)
{
	int		flag;

	(void)elems;
	(void)seps;
	flag = 0;
	cmd++;
	while ((check_option(*cmd)) == 0)
	{
		cmd++;
		flag = 1;
	}
	if (*cmd)
		ft_printf("%s", *cmd++);
	while (*cmd)
		ft_printf(" %s", *cmd++);
	if (flag != 1)
		ft_printf("\n");
	return (0);
}

static int	check_option(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	if (str[0] == '-')
		i++;
	else
		return (1);
	if (!str[i])
		return (1);
	while (str[i])
	{
		if (str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}
