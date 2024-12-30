#include <stdio.h>
#include <unistd.h>
int main()
{
  char *args[1];
  args[0] = 0;
  int pid = fork();
  if (!pid)
    execve("test\0", args, 0);
  wait(0);
  return (0);
}
