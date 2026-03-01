#include <unistd.h>

/*
is_sorted
next_permutation
main
*/

int is_sorted(char *str, int len)
{
    int i = 0;
    while (i < len - 1)
    {
        if (str[i] > str[i + 1])
            return 0;
        i++;
    }
    return 1;
}

void ft_swap(char *a, char *b)
{
    char temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

int next_permutation(char *str, int len)
{
    int pivot = len - 2;
    while (pivot >= 0 && str[pivot] >= str[pivot + 1])
        pivot--;
    if (pivot < 0)
        return 0;
    int sucessor = len - 1;
    while (str[sucessor] <= str[pivot])
        sucessor--;
    ft_swap(&str[pivot], &str[sucessor]);
    int left = pivot + 1;
    int right = len - 1;
    while (left < right)
    {
        ft_swap(&str[left], &str[right]);
        left++;
        right--;
    }
    return 1;
}

int main(int argc, char **argv)
{
    if (argc != 2)
        return 0;
    int len = 0;
    while (argv[1][len])
        len++;
    while (1)
    {
        int i = 0;
        if (is_sorted(argv[1], len))
            break ;
        while (i < len - 1 && argv[1][i] < argv[1][i + 1])
            i++;
        ft_swap(&argv[1][i], &argv[1][i + 1]);
    }
    int i = 0;
    while (argv[1][i])
    {
        write(1, &argv[1][i], 1);
        i++;
    }
    write(1, "\n", 1);
    while (next_permutation(argv[1], len))
    {
        int i = 0;
        while (argv[1][i])
        {
            write(1, &argv[1][i], 1);
            i++;
        }
        write(1, "\n", 1);
    }
    return 0;
}

