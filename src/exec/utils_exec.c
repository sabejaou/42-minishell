/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:16:28 by anfichet          #+#    #+#             */
/*   Updated: 2024/06/24 19:16:29 by anfichet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	bool_search_cmd(char *str, int c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != (char)c)
		i++;
	if (str[i] == (char)c)
		return (1);
	return (0);
}

char	*ft_join_cmd(char *s1, char *s2)
{
	char	*cmd;
	size_t	len_s1;
	size_t	len_s2;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_protect_strlen(s1);
	len_s2 = ft_protect_strlen(s2);
	cmd = malloc(sizeof(char) * (len_s1 + len_s2 + 2));
	if (!cmd)
		return (NULL);
	ft_strlcpy(cmd, s1, len_s1 + len_s2 + 2);
	ft_strlcat(cmd, "/", len_s1 + len_s2 + 2);
	ft_strlcat(cmd, s2, len_s1 + len_s2 + 2);
	return (cmd);
}
