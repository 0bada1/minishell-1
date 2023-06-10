/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalshaer <kalshaer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 13:32:12 by kalshaer          #+#    #+#             */
/*   Updated: 2023/06/07 17:16:05 by kalshaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
counter struct used to declare the counter variables to save space in functions
*/
typedef struct counter
{
	int	i;
	int	infile_i;
	int	append_i;
	int	outfile_i;
	int	hd_i;
}	t_cont;

int	handle_infile(t_cont *c, t_files *files)
{
	c->infile_i = c->infile_i + 1;
	if (files->infile_name[c->infile_i] == NULL)
	{
		ft_putstr_fd("minishell: ambiguous redirect\n", STDERR_FILENO);
		return (-1);
	}
	if (access(files->infile_name[c->infile_i], F_OK) != 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(files->infile_name[c->infile_i], STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		return (-1);
	}
	if (open_infile(files, c->infile_i) == -1)
		return (-1);
	return (0);
}

/*
this function have 2 roles:
1- call the heredoc function first to excute the heredoc at the begen
2- calles the open_functoin for each redirection to open / 
close the files (if onther files with the same type is provided)
it will return -1 if no access to infile 
*/
int	open_files(t_files *files)
{
	t_cont	c;

	c.infile_i = -1;
	c.append_i = -1;
	c.outfile_i = -1;
	c.i = -1;
	while (files->redirect_type[++c.i])
	{
		if (files->redirect_type[c.i] == '>')
		{
			if (open_outfile(files, ++c.outfile_i) == -1)
				return (-1);
		}
		else if (files->redirect_type[c.i] == 'a')
		{
			if (open_appendfile(files, ++c.append_i) == -1)
				return (-1);
		}
		else if (files->redirect_type[c.i] == '<')
			if (handle_infile(&c, files) == -1)
				return (-1);
	}
	return (0);
}

/*
to minimise the init_redir function 
*/
static void	init_redir2(t_execute *cmd, t_cont *c)
{
	if (cmd->files->redirect_type[c->i] == '>')
	{
		dup2(cmd->files->outfile_fd, STDOUT_FILENO);
		if (++c->outfile_i == ft_strstrlen(cmd->files->outfile_name))
			close(cmd->files->outfile_fd);
	}
	else if (cmd->files->redirect_type[c->i] == 'a')
	{
		dup2(cmd->files->append_fd, STDOUT_FILENO);
		if (++c->append_i == ft_strstrlen(cmd->files->append_name))
			close(cmd->files->append_fd);
	}
	else if (cmd->files->redirect_type[c->i] == '<')
	{
		dup2(cmd->files->infile_fd, STDIN_FILENO);
		if (++c->infile_i == ft_strstrlen(cmd->files->infile_name))
			close(cmd->files->infile_fd);
	}
}

/*
this function used to call the open fds and then duplicate the fd
accourding to the order of redir in cmd_block and closes the fd in the
final match of each redir_type
it will return -1 if no access to infile
*/
int	init_redir(t_execute *cmd)
{
	t_cont	c;

	c.i = -1;
	c.infile_i = 0;
	c.outfile_i = 0;
	c.append_i = 0;
	c.hd_i = 0;
	if (open_files(cmd->files) == -1)
		return (-1);
	while (cmd->files->redirect_type[++c.i])
	{
		init_redir2(cmd, &c);
		if (cmd->files->redirect_type[c.i] == 'h')
		{
			cmd->files->heredoc_fd = open(".temp", O_RDONLY);
			if (cmd->files->heredoc_fd == -1)
				return (-1);
			dup2(cmd->files->heredoc_fd, STDIN_FILENO);
			if (++c.hd_i == ft_strstrlen(cmd->files->limiter))
				close(cmd->files->heredoc_fd);
		}
	}
	return (0);
}
