#include <stdio.h>

void solve(char *s, int pos, int left_rem, int right_rem, char *result, int len)
{
    if (!s[pos])
    {
        if (!left_rem && !right_rem)
        {
            result[len] = 0;
            int balance = 0;
            for (int i = 0; result[i]; i++)
            {
                if (result[i] == '(')
                    balance++;
                else if (result[i] == ')')
                    balance--;
                if (balance < 0)
                    return;
            }
            if (!balance)
                puts(result);
        }
        return;
    }

    char ch = s[pos];

    // Remove character
    if ((ch == '(' && left_rem > 0) || (ch == ')' && right_rem > 0))
    {
        result[len] = ' ';
        int new_left_rem = left_rem;
        int new_right_rem = right_rem;
        if (ch == '(')
            new_left_rem = left_rem - 1;
        if (ch == ')')
            new_right_rem = right_rem - 1;
        solve(s, pos + 1, new_left_rem, new_right_rem, result, len + 1);
    }

    // Keep character
    result[len] = ch;
    solve(s, pos + 1, left_rem, right_rem, result, len + 1);
}

int main(int argc, char **argv)
{
    if (argc != 2)
        return 1;

    char *s = argv[1];
    int left = 0, right = 0;

    for (int i = 0; s[i]; i++)
    {
        if (s[i] == '(')
            left++;
        else if (s[i] == ')')
        {
            if (left > 0)
                left--;
            else
                right++;
        }
    }

    char result[1000];
    solve(s, 0, left, right, result, 0);
    return 0;
}
