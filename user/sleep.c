#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: sleep <time>\n");
    exit(1);
  }

  // 将字符串参数转换为整数
  int time = atoi(argv[1]);
  if (time <= 0) {
    printf("Invalid sleep time.\n");
    exit(1);
  }

  // 调用系统调用sleep
  sleep(time);
  
  // 正常退出
  exit(0);
}
