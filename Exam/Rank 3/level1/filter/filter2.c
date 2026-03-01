#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int ft_strncmp(char *s1, char *s2, int len)
{
    int i = 0;
    while (i < len)
    {
        if (s1[i] != s2[i])
            return 0;
        i++;
    }
    return 1;
}

int main(int argc, char **argv)
{
    if (argc != 2 || !argv[1] || !argv[1][0])
        return 1;
    int capacity = 1024;
    char *buffer;
    buffer = malloc(capacity);
    if (!buffer)
        return (perror("Error"), 1);
    int total_len = 0;
    int bytes_read;
    while ((bytes_read = read(0, buffer + total_len, capacity - total_len)) > 0)
    {
        total_len += bytes_read;
        if (total_len >= capacity - 1)
        {
            buffer = realloc(buffer, capacity);
            if (!buffer)
            {
                free(buffer);
                return (perror("Error"), 1);
            }
        }
    }
    if (bytes_read < 0)
        return (perror("Error"), 1);
    int len = strlen(argv[1]);
    buffer[total_len] = '\0';
    int i = 0;
    while (i < total_len)
    {
        if (ft_strncmp(buffer + i, argv[1], len))
        {
            int j = 0;
            while (j < len)
            {
                buffer[i] = '*';
                j++;
                i++;
            }
        }
        else
            i++;
    }
    printf("%s", buffer);
    free(buffer);
    return 0;
}