#include <stdio.h>

int main (int ac, char **av, char **envp)
{
    int i;

	i = 0;
    while (envp[i])
    {
        printf("IS--- %s\n", envp[i]);
        i++;
    }

    return 0;
}
