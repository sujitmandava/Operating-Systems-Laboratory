// Test that fork fails gracefully.
// Tiny executable so that the limit can be filling the proc table.

#include "types.h"
#include "stat.h"
#include "user.h"

#define N  1000

// void
// printf(int fd, const char *s, ...)
// {
//   write(fd, s, strlen(s));
// }

void
forktest(void)
{
  int n, pid=1;

  printf(1, "fork test\n");

  for(n=0; n<N; n++){
    // pid = flexsc_fork();
    if(pid < 0)
      break;
    if(pid == 0)
      exit();
  }

  if(n == N){
    printf(1, "fork claimed to work N times!\n", N);
    exit();
  }

  for(; n > 0; n--){
    if(wait() < 0){
      printf(1, "wait stopped early\n");
      exit();
    }
  }

  if(wait() != -1){
    printf(1, "wait got too many\n");
    exit();
  }

  printf(1, "fork test OK\n");
}

int
main(void)
{
//   forktest();
  sys_flexsc_register();
  int pid = fork();
  if(pid == 0)
  {
    exit();
  }
  //Now add some fork system calls to the syscall page;
  // test again.
  exit();
}