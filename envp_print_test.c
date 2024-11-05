#include <stdio.h>

int main(int ac, char **av, char **envp)
{
	for (int i = 0; envp[i]; i++)
	{
		printf("%d : %s\n", i, envp[i]);
	}
}