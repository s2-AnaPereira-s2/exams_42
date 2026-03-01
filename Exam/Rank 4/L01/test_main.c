#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	picoshell(char **cmds[]);

int main(int argc, char **argv)
{
    int cmds_size = 1;

    for (int i = 1; i < argc; i++)
    {
        if (!strcmp(argv[i], "|"))
            cmds_size++;
    }

    char ***cmds = calloc(cmds_size + 1, sizeof(char **));
    if (!cmds)
    {
        perror("calloc");
        return 1;
    }
    cmds[0] = argv + 1;
    int cmds_i = 1;

    for (int i = 1; i < argc; i++)
    {
        if (!strcmp(argv[i], "|"))
        {
            cmds[cmds_i] = argv + i + 1;
            argv[i] = NULL;
            cmds_i++;
        }
    }
    int ret = picoshell(cmds);
    if (ret)
        perror("picoshell");
    free(cmds);
    return ret;
}
