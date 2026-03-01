/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   popen.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrsouz <gabrsouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 19:46:58 by kmaeda            #+#    #+#             */
/*   Updated: 2025/10/31 09:29:58 by gabrsouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int	ft_popen(const char *file, char *const argv[], char type)
{
	int	fd[2];
	pid_t	pid;

	if (!file || !argv || (type != 'r' && type != 'w'))
		return (-1);
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		if (type == 'r')
			dup2(fd[1], 1);
		if (type == 'w')
			dup2(fd[0], 0);
		close(fd[0]);
		close(fd[1]);
		execvp(file, argv);
		exit(1);
	}
	if (type == 'r')
	{
		close(fd[1]);
		return (fd[0]);
	}
	else
	{
		close(fd[0]);
		return (fd[1]);
	}
}

int main()
{
	int  fd;

	fd = ft_popen("wc", (char *const []){"wc", NULL}, 'w');
	char *line = "Hello world\nThis is a test\nthird line\n";
	write(fd, line, strlen(line));
	close(fd);
	return (0);
}
