/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   picoshell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrsouz <gabrsouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 21:53:45 by kmaeda            #+#    #+#             */
/*   Updated: 2025/10/29 13:19:48 by gabrsouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int	picoshell(char **cmds[])
{
	int	fd[2];
	int	fd_stdin = 0;
	pid_t pid;
	int	i = 0;
	int	status = 0;

	while (cmds[i])
	{
		if (cmds[i + 1])
		{
			if (pipe(fd) == -1)
			{
				if (fd_stdin != 0)
					close(fd_stdin);
				return (1);
			}
		}
		else
		{
			fd[0] = -1;
			fd[1] = -1;
		}
		pid = fork();
		if (pid == -1)
		{
			if (fd_stdin != 0)
				close(fd_stdin);
			if (fd[1] != -1)
			{
				close(fd[0]);
				close(fd[1]);
			}
			return (1);
		}
		if (pid == 0)
		{
			if (fd_stdin != 0)
			{
				dup2(fd_stdin, 0);
				close(fd_stdin);
			}
			if (fd[1] != -1)
			{
				dup2(fd[1], 1);
				close(fd[1]);
				close(fd[0]);
			}
			execvp(cmds[i][0], cmds[i]);
			exit(1);
		}
		if (fd_stdin != 0)
			close(fd_stdin);
		if (fd[1] != -1)
			close(fd[1]);
		fd_stdin = fd[0];
		i++;
	}
	if (fd_stdin != 0)
		close(fd_stdin);
	while (wait(&status) > 0)
		;
	return (0);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    int cmds_size = 1;

    for (int i = 1; i < argc; i++)
    {
        if (!strcmp(argv[i], "|"))
            cmds_size++;
    }

    char ***cmds = calloc(cmds_size + 1, sizeof(char **));
    if (!cmds)
    {
        dprintf(2, "Malloc error: %m\n");
        return 1;
    }
    cmds[0] = argv + 1;
    int cmds_i = 1;

    for (int i = 1; i < argc; i++)
    {
        if (!strcmp(argv[i], "|"))
        {
            cmds[cmds_i] = argv + i + 1;
            argv[i] = NULL;
            cmds_i++;
        }
    }
    int ret = picoshell(cmds);
    if (ret)
        perror("picoshell");
    free(cmds);
    return ret;
}
