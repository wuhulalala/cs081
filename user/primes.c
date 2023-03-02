#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void child(int *p) {
    if (fork() == 0) {
        int num = 0, temp = 0;
        if (!read(p[0], &num, sizeof(int))) exit(0);
        temp = num;
        printf("prime %d\n", num);
        int child_p[2];
        pipe(child_p);
        while (read(p[0], &num, sizeof(int)) > 0) {
            if (num % temp) write(child_p[1], &num, sizeof(int));
        }
        close(child_p[1]);
        child(child_p);
        

    }
    wait((int *) 0);
}
int main(int argc, char* argv[]) {
    int p[2];
    pipe(p);
    for (int i = 2; i <= 35; i += 1) {
        write(p[1], &i, sizeof(int));
    }
    close(p[1]);
    child(p);
    exit(0);
}