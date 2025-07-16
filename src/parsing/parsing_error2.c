/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabejaou <sabejaou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:13:32 by sabejaou          #+#    #+#             */
/*   Updated: 2024/06/24 19:15:29 by sabejaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_err	ft_error(t_err cd)
{
	if (cd == ERR_DBQUOTE)
		return (ft_dprintf(2, "%s\n", ERR_MSG_DBQUOTE));
	else if (cd == ERR_SPQUOTE)
		return (ft_dprintf(2, "%s\n", ERR_MSG_SPQUOTE));
	else if (cd == ERR_SYNTAX_FILE)
		return (ft_dprintf(2, "%s\n", ERR_MSG_SYNTAX_FILE));
	else if (cd == ERR_SPACE || cd == ERR_EMPTY_ARG)
		return (ft_dprintf(2, "%s\n", ERR_MSG_SPACE));
	else if (cd == ERR_BUILTIN_CD)
		return (ft_dprintf(2, "%s\n", ERR_MSG_BUILTIN_CD), 1);
	else if (cd == ERR_BUILTIN_CD_HOME)
		return (ft_dprintf(2, "%s\n", ERR_MSG_BUILTIN_CD_HOME), 1);
	return (NO_ERROR);
}
