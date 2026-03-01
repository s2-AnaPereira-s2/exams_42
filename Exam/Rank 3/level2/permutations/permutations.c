#include <stdio.h>
#include <stdlib.h>

void swap(char *a, char *b)
{
    char t = *a;
    *a = *b;
    *b = t;
}

int next_perm(char *s, int len)
{
    int i = len - 2;
    while (i >= 0 && s[i] >= s[i + 1])
        i--;
    if (i < 0)
        return 0;

    int j = len - 1;
    while (s[j] <= s[i])
        j--;
    swap(&s[i], &s[j]);

    int start = i + 1, end = len - 1;
    while (start < end)
    {
        swap(&s[start], &s[end]);
        start++;
        end--;
    }

    return 1;
}

int main(int argc, char **argv)
{
    if (argc != 2)
        return 1;

    char *str = argv[1];
    int len = 0;
    while (str[len])
        len++;

    char *s = malloc(len + 1);
    if (!s)
        return 1;

    for (int i = 0; i <= len; i++)
        s[i] = str[i];
    for (int i = 0; i < len - 1; i++)
        for (int j = i + 1; j < len; j++)
            if (s[i] > s[j])
                swap(&s[i], &s[j]);

    do
    {
        puts(s);
    } while (next_perm(s, len));

    free(s);
    return 0;
}
