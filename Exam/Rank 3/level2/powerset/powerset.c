#include <stdio.h>
#include <stdlib.h>

void powerset(int *a, int n, int target, int *sub, int size, int i, int sum)
{
    if (sum == target)
    {
        for (int j = 0; j < size; j++)
        {
            if (j)
                printf(" %d", sub[j]);
            else
                printf("%d", sub[j]);
        }
        printf("\n");
    }

    for (; i < n; i++)
    {
        sub[size] = a[i];
        powerset(a, n, target, sub, size + 1, i + 1, sum + a[i]);
    }
}

int main(int argc, char **argv)
{
    if (argc < 2)
        return 1;
    int target = atoi(argv[1]), n = argc - 2, a[100], sub[100];
    for (int i = 0; i < n; i++)
        a[i] = atoi(argv[i + 2]);
    powerset(a, n, target, sub, 0, 0, 0);
    return 0;
}
