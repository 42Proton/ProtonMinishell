#include <signal.h>
#include <stdio.h>


void heandler(int signal)
{
        printf("%d\n", getpid());
        return (0);
}

int     main(void)
{
        signal(SIGINT, heandler);
        return (0);
}