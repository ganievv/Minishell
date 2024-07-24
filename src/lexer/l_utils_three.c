/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_utils_three.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 14:39:49 by tnakas            #+#    #+#             */
/*   Updated: 2024/07/24 16:43:12 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// how to count the words from the split
// how to free the double dimentional array
//echo "hello  $USER " > file | grep h | cat << eof | cat >> file | echo 'done'
//I need a way for single and double quotes and also for $
//If is not double quoted or single quoted I'must have an indicator
// ex. echo "make      $HOME | grep h | echo 'done $USER making progress
// I'm expecting "echo" "/"make"      "$HOME" "|" "grep" "h" "|" "echo" 
//"/'done" "$USER" "making" "progress"
// if non quoted stop on the space 
// ex. "echo" "/"make       $HOME test/"" "|" "grep" "h" "|" "echo"
//"/'done $USER making progress/'"

//Simple_Seperators: "|, <, >, isspace"
// len 0
// redir: >>, <<
// len 1
// VAR: $
// len while(!ft_isspace)
// '' || "" (I must handle it when I have a dollar)
int	update_i_on_quoted(char *rl, int *i)
{
	if (ft_is_quoted(rl, *i) || ft_is_dquoted(rl, *i))
	{
		*i++;
		if (ft_is_quoted(rl, *i))
			while (rl[*i] != '\'')
				*i++;
		else
			while (rl[*i] != '\"')
				*i++;
		return ;
	}
	while (!ft_isspace(rl[*i]))
		*i++;
}

// words
int	update_i_on_words(char *rl, int *i)
{
	while (!ft_isspace(rl[*i]))
		*i++;
}

//if it's a normal word pass if they are double 
//quotes pass until to find doulbe quotes or single quotes or \0

int	update_i_on_var(char *rl, int *i)
{
	if (rl[*i] == '$')
		while (!ft_isspace(rl[*i]))
			*i++;
}

int	number_of_tokens(char *rl)
{
	int	i;

	i = 0;
	if (rl[i] && ft_isspace(rl[i]))
		while (rl[i] && ft_isspace(rl[i]))
			i++;
	i--;
	while (rl[++i])
	{
		if(ft_issingle_pipe)
	}
	while ()
}