/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junlee <junlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 20:19:51 by junlee            #+#    #+#             */
/*   Updated: 2024/12/17 20:22:55 by junlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	handle_red_exec(t_tree *root, t_envp *master, int s_stdin, int s_stdout)
{
	int	i;

	set_all_heredoc(root, master);
	i = 0;
	while (i < root->child_count)
	{
		if (root->children[i]->type == NODE_RED || \
			root->children[i]->type == NODE_HEREDOC)
		{
			if (setup_redirection(root->children[i], 0, i) < 0)
			{
				perror("minishell: failed to set redirection");
				restore_stdio(s_stdin, s_stdout);
				exit(1);
			}
		}
		i++;
	}
	restore_stdio(s_stdin, s_stdout);
}

void	handle_execve_exec(t_tree *root, t_envp *master)
{
	char	*les;
	int		status;
	int		sig;

	set_all_heredoc(root, master);
	signal_all_ign();
	signal_all_dfl();
	signal_handle_execve();
	if (fork() == 0)
		execute_command(root, master, 0);
	wait(&status);
	if (WIFEXITED(status))
	{
		les = ft_itoa(WEXITSTATUS(status));
		strerror(errno);
		replace_content(master->u_envp, "LAST_EXIT_STATUS", les);
		free(les);
	}
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		les = ft_itoa(sig + 128);
		replace_content(master->u_envp, "LAST_EXIT_STATUS", les);
		free(les);
	}
}

void	execute_exec(t_tree *root, t_envp *master, int s_stdin, int s_stdout)
{
	t_tree	*cmd_node;
	char	*les;

	cmd_node = find_cmd_node(root);
	if (cmd_node == NULL)
	{
		handle_red_exec(root, master, s_stdin, s_stdout);
		return ;
	}
	if (is_bulitin(cmd_node->value) == 0)
	{
		les = ft_itoa(builtin_cmd(root, master, 0));
		replace_content(master->u_envp, "LAST_EXIT_STATUS", les);
		free(les);
	}
	else
		handle_execve_exec(root, master);
}
