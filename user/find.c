#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

void find(char *path, char *filename) {
    char buf[512], *p;
    int fd;
    struct stat st;
    struct dirent de;
    if ((fd = open(path, 0)) < 0) {
        printf("find: cannot open %s\n", path);
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
        while (read(fd, &de, sizeof(de)) == sizeof(de)) {
            memmove(p, de.name, DIRSIZ);
            p[DIRSIZ] = 0;
            if (de.inum == 0) {
                continue; 
            } 
            if (stat(buf, &st) < 0) {
                printf("find: cannot stat\n");
                continue;
            }
            if (st.type == 1) {
                if (strcmp(de.name, "..") == 0 || strcmp(de.name, ".") == 0) {
                    continue;
                }
                find(buf, filename);
            } else if (st.type == 2) {
                if (strcmp(de.name, filename) == 0) {
                    printf("%s\n", buf);
                }


            }
        }
        break;
    }
    return;
    
    
    
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("find <path> <file name>\n");
        exit(1);
    }
    //char *path = argv[1];
    //char *filename = argv[2];
    find(argv[1], argv[2]);
    exit(0);
    

}