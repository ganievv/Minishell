/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_exit_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:59:38 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/10 20:20:28 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* this function checks if a given string
*  is a number						   */
int	is_nbr(char *arg)
{
	if (!arg)
		return (0);
	while (ft_isspace(*arg))
		arg++;
	if ((*arg == '+') || (*arg == '-'))
		arg++;
	if (*arg == '\0')
		return (0);
	while (*arg)
	{
		if (!ft_isdigit(*arg))
			return (0);
		arg++;
	}
	return (1);
}

/* this function convert a number from
* 'char*' to 'long long'			*/
long long	ft_atoll(char *arg)
{
	long long	nbr;
	int			sign;

	nbr = 0;
	sign = 1;
	while (ft_isspace(*arg))
		arg++;
	if (*arg == '-')
		sign = -1;
	if ((*arg == '+') || (*arg == '-'))
		arg++;
	while (ft_isdigit(*arg))
		nbr = (nbr * 10) + (*arg++ - '0');
	return (nbr * sign);
}

/* 9,223,372,036,854,775,807   -> LLONG_MAX |
*  -9,223,372,036,854,775,808  -> LLONG_MIN |-> 19 characters is MAX
*
*  if nbr > 999,999,999,999,999,999  -> valid range |
*  if nbr < -999,999,999,999,999,999 -> valid range |-> 18 characters is MAX
**/

/* this function checks if a given number 
*  is in correct range				   */
int	is_valid_exit_range(char *nbr)
{
	int	i;

	i = 0;
	while (ft_isspace(nbr[i]))
		i++;
	if ((nbr[i] == '+') || (nbr[i] == '-'))
		i++;
	if (ft_strlen(nbr + i) > 18)
		return (0);
	else
		return (1);
}

void	cleanup_for_exit_builtin(t_msh *info)
{
	if (info->cmds_num == 1)
	{
		free_all_prog_vars(info);
		free_arr_str(info->envp);
		rl_clear_history();
	}
}
