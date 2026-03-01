#include <stdlib.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1024
#endif

char *get_next_line(int fd)
{
    static char buffer[BUFFER_SIZE];
    static int buffer_pos = 0;
    static int buffer_size = 0;
    char *line = NULL;
    int line_len = 0;
    char *temp;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return NULL;

    while (1)
    {
        if (buffer_pos >= buffer_size)
        {
            buffer_size = read(fd, buffer, BUFFER_SIZE);
            if (buffer_size <= 0)
                break;
            buffer_pos = 0;
        }

        temp = malloc(line_len + 2);
        if (!temp)
        {
            free(line);
            return NULL;
        }

        for (int i = 0; i < line_len; i++)
            temp[i] = line[i];

        temp[line_len] = buffer[buffer_pos];
        temp[line_len + 1] = '\0';

        free(line);
        line = temp;
        line_len++;

        if (buffer[buffer_pos] == '\n')
        {
            buffer_pos++;
            return line;
        }

        buffer_pos++;
    }

    if (line_len == 0)
    {
        free(line);
        return NULL;
    }

    return line;
}
