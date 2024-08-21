/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_io_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 13:19:57 by sganiev           #+#    #+#             */
/*   Updated: 2024/08/21 13:57:45 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	print_error_io_open(char *file)
{
	write(STDERR_FILENO, "msh: ", 5);
	write(STDERR_FILENO, file, ft_strlen(file));
	write(STDERR_FILENO, ": ", 2);
	perror("");
}

int	process_in_files(t_redir_files *f_in)
{
	int	fd;

	while (f_in)
	{
		fd = open(f_in->file, f_in->mode);
		if (fd == -1)
			return (print_error_io_open(f_in->file), 0);
		dup2(fd, f_in->redir_type);
		close(fd);
		f_in = f_in->next;
	}
	return (1);
}

int	process_out_files(t_redir_files *f_out)
{
	int	fd;

	while (f_out)
	{
		fd = open(f_out->file, f_out->mode, 0666);
		if (fd == -1)
			return (print_error_io_open(f_out->file), 0);
		dup2(fd, f_out->redir_type);
		close(fd);
		f_out = f_out->next;
	}
	return (1);
}
