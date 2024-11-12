#include "../kernel/types.h"
#include "../kernel/stat.h"
#include "user.h"

#define PAGE_SIZE 4096

int main() 
{
    int size = PAGE_SIZE; 
    void *addr = sbrk(size);
    if (addr == (void *)-1) {
      printf("sbrk failed\n");
      exit(1);
    }
    char *p = (char *)addr;
    for (int i = 0; i < size; i++) {
        p[i] = 'A';
    }

    if (mprotect(addr, 1) < 0) {
        printf("mprotect failed\n");
        exit(1);
	}
    int success = 1;
    if (fork() == 0) {
        p[0] = 'B';
        success = 0;
        exit(0);
    } else {
        wait(0);
    }

    if (success) {
        printf("mprotect ha funcionado\n");
    } else {
        printf("mprotect test failed: write succeeded on protected memory\n");
    }
    if (munprotect(addr, 1) < 0) {
        printf("munprotect failed\n");
        exit(1);
    }
    p[0] = 'C';
    printf("munprotect ha funcionado\n");
    exit(0);
}
