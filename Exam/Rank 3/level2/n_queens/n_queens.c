#include <stdio.h>
#include <stdlib.h>

int is_safe(int *board, int row, int col)
{
    for (int i = 0; i < col; i++)
    {
        if (board[i] == row || 
            board[i] - row == i - col || 
            board[i] - row == col - i)
            return 0;
    }
    return 1;
}

void solve(int *board, int col, int n)
{
    if (col == n)
    {
        for (int i = 0; i < n; i++)
        {
            fprintf(stdout, "%d", board[i]);
            if (i < n - 1)
                fprintf(stdout, " ");
        }
        fprintf(stdout, "\n");
        return;
    }
    
    for (int row = 0; row < n; row++)
    {
        if (is_safe(board, row, col))
        {
            board[col] = row;
            solve(board, col + 1, n);
        }
    }
}

int main(int argc, char **argv)
{
    if (argc != 2)
        return 1;
    
    int n = atoi(argv[1]);
    if (n <= 0)
        return 1;
    
    int *board = calloc(n, sizeof(int));
    if (!board)
        return 1;
    
    solve(board, 0, n);
    free(board);
    
    return 0;
}
