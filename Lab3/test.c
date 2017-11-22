#include <sys/syscall.h>
#include <stdio.h>
#include <unistd.h>
int main(){
    long ret = syscall(323, 100, "this is a new system call!"); //syscall 参数1 调用号 之后为系统调用的参数列表
    printf("result is %ld\n", ret);
    return 0;
}