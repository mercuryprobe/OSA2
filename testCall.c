#include <stdio.h>
#include <stdlib.h>
#include <linux/syscalls.h>
#include <linux/kernel.h>
#define kernel_2d_memcpy 451

int checker(int** given, int** actual, int nArr, int arrDepth) {
    for (int i = 0; i<nArr; i++) {
        for (int j = 0; j<arrDepth; j++) {
            if (given[i][j] != actual[i][j]) {
                return -1;
            }
        }
    }

    return 0;
}

int main() {
    int array[8][8];
    int target[8][8];
    int k = 0;
    for (int i = 0; i<8; i++) {
        for (int j = 0; j<8; j++) {
            array[i][j] = k++;
        }
    }


    int callResult;
    callResult = syscall(451, array, target, 8, 8);
    if (callResult==0) {
        if (checker(target, array, 8, 8)==0) {
            puts("Copy successful!");
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