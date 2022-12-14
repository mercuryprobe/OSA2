#include <stdio.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <linux/kernel.h>
#include <unistd.h>
#define kernel_2d_memcpy 451


int main() {
    int nArr = 8;
    int arrDepth = 8;
    int array[nArr][arrDepth];
    int target[nArr][arrDepth];
    int k = 0;
    for (int i = 0; i<nArr; i++) {
        for (int j = 0; j<arrDepth; j++) {
            array[i][j] = k++;
        }
    }

    puts("Original Target: ");
    for (int i = 0; i<nArr; i++) {
        for (int j = 0; j<arrDepth; j++) {
            printf("%d ", target[i][j]);
        }
        printf("\n");
    }
    puts("");

    int callResult;
    int fail = 0;
    callResult = syscall(451, array, target, 8, 8);
    if (callResult==0) {
        for (int i = 0; i<nArr; i++) {
            for (int j = 0; j<arrDepth; j++) {
                if (array[i][j] != target[i][j]) {
                    fail = 1;
                    break;
                }
            }
        }

        if (fail==0) {
            puts("Copy successful!");
            for (int i = 0; i<nArr; i++) {
                for (int j = 0; j<arrDepth; j++) {
                    printf("%d ", target[i][j]);
                }
                printf("\n");
            }

        } else {
            puts("Copy failed!");
        }

    } else if (callResult==-1) {
        puts("Syscall failed: __copy_to_user error!");
    } else {
        puts("Syscall failed: __copy_from_user error!");
    }

    
    
    return 0;
}