#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
/*
swap,
is_sorted,
next_perm,
main,
*/

void swap(char *a, char *b)
{
    char temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

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

int  next_perm(char *str, int len)
{
    int pivot = len - 2;
    while (pivot >= 0 && str[pivot] >= str[pivot + 1])
        pivot--;
    
    if (pivot < 0)
        return 0;
    
    int sucessor = len - 1;
    while (str[sucessor] <= str[pivot])
        sucessor--;
    
    swap(&str[pivot], &str[sucessor]);

    int left = pivot + 1;
    int right = len - 1;
    while (left < right)
    {
        swap(&str[left], &str[right]);
        left++;
        right--;
    }
    return 1;
}

int main(int argc, char **argv)
{
    if (argc != 2)
        return 1;
    int len = 0;
    while (argv[1][len])
        len++;
    char *str;
    str = malloc(len + 1);
    if(!str)
        return 0;
    str = argv[1];
    str[len] = '\0';
    while (1)
    {
        if (is_sorted(str, len))
        {
            break ;
        }
        int i = 0;
        while (i < len - 1)
        {
            if (str[i] > str[i + 1])
            {
                swap(&str[i], &str[i + 1]);
                i++;
            }
            else
                i++;
        }
    }
    puts(str);
    while (next_perm(str, len))
        puts(str);
    return 0;
}