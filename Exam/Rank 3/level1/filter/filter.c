#define _GNU_SOURCE
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

int main(int argc, char **argv)
{
    if (argc != 2 || !argv[1] || !argv[1][0])
        return 1;

    char *pattern = argv[1];
    int pattern_len = strlen(pattern);
    char *buffer = NULL;
    char *result = NULL;
    int capacity = 1024;
    int total_size = 0;

    buffer = malloc(capacity);
    if (!buffer)
    {
        perror("Error");
        return 1;
    }

    int bytes_read;
    while ((bytes_read = read(0, buffer + total_size, capacity - total_size)) > 0)
    {
        total_size += bytes_read;
        if (total_size >= capacity - 1)
        {
            capacity *= 2;
            buffer = realloc(buffer, capacity);
            if (!buffer)
            {
                perror("Error");
                return 1;
            }
        }
    }

    if (bytes_read < 0)
    {
        perror("Error");
        free(buffer);
        return 1;
    }

    result = malloc(total_size + 1);
    if (!result)
    {
        perror("Error");
        free(buffer);
        return 1;
    }

    int result_pos = 0;
    int i = 0;

    while (i < total_size)
    {
        char *found = memmem(buffer + i, total_size - i, pattern, pattern_len);

        if (found && found == buffer + i)
        {
            for (int j = 0; j < pattern_len; j++)
                result[result_pos++] = '*';
            i += pattern_len;
        }
        else
            result[result_pos++] = buffer[i++];
    }

    write(1, result, result_pos);

    free(buffer);
    free(result);
    return 0;
}
