#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

#ifndef BUFFER_SIZE
 #define BUFFER_SIZE 1024
#endif

char    *get_next_line(int fd)
{
    if (fd < 0 || BUFFER_SIZE == 0)
        return NULL;
    
    static char buffer[BUFFER_SIZE];
    char *line = NULL;
    char *temp;
    static int buffer_pos = 0;
    static int bytes_read = 0;
    int total_len = 0;

    while (1)
    {
        if (buffer_pos >= bytes_read)
        {
            bytes_read = read(fd, buffer, BUFFER_SIZE);
            if (bytes_read <= 0)
                break;
            buffer_pos = 0;
        }
        temp = malloc(total_len + 2);
        if (!temp)
        {
            free(line);
            return line;
        }
        int i = 0;
        while (i < total_len)
        {
            temp[i] = line[i];
            i++;
        }
        temp[total_len] = buffer[buffer_pos];
        temp[total_len + 1] = '\0';
        free(line);
        line = temp;
        total_len++;
        if (buffer[buffer_pos] == '\n')
        {
            buffer_pos++;
            return (line);
        }
        buffer_pos++;
    }
    return line;
}

int main()
{
    int fd = open("infile", O_RDONLY);
    int i = 0;
    char *line;
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    printf("\n");
    free(line);
    close(fd);
    return 0;
}