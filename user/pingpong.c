#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char * argv[]) 
{
    int p[2];
    pipe(p);
    char buf[5];
    int n = 0;
    if (fork() == 0) {
        write(p[1], "a", 1);
        close(p[1]);
        n = read(p[0], buf, 1);
        if (n == 1) {
            printf("%d: received ping\n", getpid());
        }
        close(p[0]);
        exit(0);
    } else {
        write(p[1], "b", 1);
        close(p[1]);
        n = read(p[0], buf, 1);
        wait((int *) 0);
        if (n == 1) {
            printf("%d: received pong\n", getpid());
        }
        close(p[0]);
    }
    exit(0);
}