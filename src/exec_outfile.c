/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_outfile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalshaer <kalshaer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 11:49:49 by kalshaer          #+#    #+#             */
/*   Updated: 2023/06/05 15:09:21 by kalshaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
O_CREAT: This flag specifies that the file should be created if 
it doesn't exist.
O_TRUNC: This flag specifies that the file should be truncated 
(its contents deleted) if it already exists.
O_APPEND flag is used to open the file in append mode
O_WRONLY flag specifies that the file should be opened for writing only
0644: This is the file mode that specifies the permissions for 
the newly created file
*/
int	open_outfile(t_files *files, int i)
{
	files->outfile_fd = open(files->outfile_name[i],
			O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (files->outfile_fd == -1)
	{
		perror("Error");
		return (-1);
	}
	if (i < ft_strstrlen(files->outfile_name) - 1)
		close(files->outfile_fd);
	return (0);
}

int	open_appendfile(t_files *files, int i)
{
	files->append_fd = open(files->append_name[i],
			O_RDWR | O_CREAT | O_APPEND, 0644);
	if (files->append_fd == -1)
	{
		perror("Error");
		return (-1);
	}
	if (i < ft_strstrlen(files->append_name) - 1)
		close(files->append_fd);
	return (0);
}
