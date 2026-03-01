/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pico_gab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrsouz <gabrsouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 12:52:57 by gabrsouz          #+#    #+#             */
/*   Updated: 2025/10/31 09:22:11 by gabrsouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int picoshell(char **cmds[])
{
	int fd[2];
	int status = 0;
	int old = 0;
	int i = -1;
	pid_t pid;

	while (cmds[++i])
	{
		if (cmds[i + 1])
		{
			if (pipe(fd) == -1)
			{
				if (old != 0)
					close(old);
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
			if (old != 0)
				close(old);
			if (fd[1] != -1)
			{
				close(fd[1]);
				close(fd[0]);
			}
			return (1);
		}
		if (pid == 0)
		{
			if (old != 0)
			{
				dup2(old, 0);
				close(old);
			}
			if (fd[1] != -1)
			{
				dup2(fd[1], 1);
				close(fd[1]);
				close(fd[0]);
			}
			execvp(cmds[i][0], cmds[i]);
			exit (1);
		}
		if (old != 0)
			close(old);
		if (fd[1] != -1)
			close(fd[1]);
		old = fd[0];
	}
	if (old != 0)
			close(old);
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