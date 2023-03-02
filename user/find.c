#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include <cstring>


void find(char *path, char *filename) {
    char buf[512];
    int fd;
    struct stat st;
    struct dirent de;
    if ((fd = open(path, 0)) < 0) {
        fprintf("find: cannot open %s\n", path);
        return;
    }

    if (fstat(fd, &st) < 0) {
        fprintf(2, "find: cannot stat %s\n", path);
        close(fd);
        return;
    }

    switch (st.type) {
    case T_FILE:
        printf("path could not contain file!\n");
        break;
    
    case T_DIR:
        if (strlen(path) + 1 + DIRSIZ + 1 > sizeof buf) {
        printf("ls: path too long\n");
        break;
        }
        strcpy(buf, path);
        p = buf + strlen(buf);
        *p++ = '/';
            break;
    }
    
    
    
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        prinf("find <path> <file name>\n");
        exit(1);
    }
    char *path = argv[1];
    char *filename = argv[2];
    find(path, filename);
    exit(0);
    

}