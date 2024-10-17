#include "kernel/param.h"
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  if(argc < 3){
    fprintf(2, "usage: trace mask program [args...]\n");
    exit(1);
  }

  int mask = atoi(argv[1]);

   trace(mask);

  exec(argv[2], &argv[2]);

  fprintf(2, "exec %s failed\n", argv[2]);
  exit(1);
}
