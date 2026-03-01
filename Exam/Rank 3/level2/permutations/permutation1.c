#include <unistd.h>
#include <stdio.h>

void ft_swap(char *a, char *b)
{
	char temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

int is_sorted(char *argv, int len)
{
	int i = 0;
	while (i < len - 1)
	{	
		if (argv[i] < argv[i + 1])
			i++;
		else
			return 1;
	}
	return 0;
}

int next_permutation(char *str, int len)
{
    // Step 1: Find pivot (rightmost character smaller than its right neighbor)
    int pivot = len - 2;
    while (pivot >= 0 && str[pivot] >= str[pivot + 1])
        pivot--;
    
    // If no pivot found, this is the last permutation
    if (pivot == -1)
        return 0;
    
    // Step 2: Find successor (rightmost character larger than pivot)
    int successor = len - 1;
    while (str[successor] <= str[pivot])
        successor--;
    
    // Step 3: Swap pivot and successor
    ft_swap(&str[pivot], &str[successor]);
    
    // Step 4: Reverse the suffix after pivot
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
	if (argc < 2)
		return 0;
	int i;
	int j;
	int len = 0;
	while (argv[1][len])
		len++;
	char str[len + 1];
	i = 0;
	while (argv[1][i])
	{
		str[i] = argv[1][i];
		i++;
	}
	str[i] = '\0';
	
	while (is_sorted(str, len) != 0)
	{
		j = 0;
		while (j < len - 1)
		{
			if (str[j] > str[j + 1])
			{
				ft_swap(&str[j], &str[j + 1]);
				j++;
			}
			else
				j++;
		}
	}
	i = 0;
    while (str[i] != '\0')
    {
    	write(1, &str[i], 1);
            i++;
    }
	write(1, "\n", 1);
	i = 0;
	while (next_permutation(str, len))
	{
		j = 0;
		while (str[j] != '\0')
		{
			write(1, &str[j], 1);
			j++;
		}
		write(1, "\n", 1);
	}
	return 0;
}
