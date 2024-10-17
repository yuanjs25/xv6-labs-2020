#include "kernel/types.h"
#include "user/user.h"

int main(void) {
    int pipe1[2]; // 用于父进程向子进程发送字节
    int pipe2[2]; // 用于子进程向父进程发送字节
    char buf[1];  // 用于传输一个字节
    int pid;

    // 创建两个管道
    pipe(pipe1);
    pipe(pipe2);

    if ((pid = fork()) < 0) {
        // fork失败
        printf("fork failed\n");
        exit(1);
    }

    if (pid == 0) {
        // 子进程
        close(pipe1[1]); // 关闭pipe1的写入端
        close(pipe2[0]); // 关闭pipe2的读取端

        // 从父进程接收字节（从pipe1读取）
        read(pipe1[0], buf, 1);
        printf("%d: received ping\n", getpid());

        // 向父进程发送字节（向pipe2写入）
        write(pipe2[1], buf, 1);

        // 关闭管道并退出
        close(pipe1[0]);
        close(pipe2[1]);
        exit(0);

    } else {
        // 父进程
        close(pipe1[0]); // 关闭pipe1的读取端
        close(pipe2[1]); // 关闭pipe2的写入端

        // 向子进程发送字节（向pipe1写入）
        buf[0] = 'X';
        write(pipe1[1], buf, 1);

        // 从子进程接收字节（从pipe2读取）
        read(pipe2[0], buf, 1);
        printf("%d: received pong\n", getpid());

        // 关闭管道并等待子进程结束
        close(pipe1[1]);
        close(pipe2[0]);
        wait(0);
        exit(0);
    }
}
