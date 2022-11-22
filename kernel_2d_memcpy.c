#include <linux/syscalls.h>
#include <linux/kernel.h>

SYSCALL_DEFINE4(kernel_2d_memcpy, int**, source, int**, destination, int, nArr, int, arrDepth) {
    // nArr: number of arrays
    // arrDepth: depth of arrays

    int buffer[nArr][arrDepth];

    int copy2kRes;
    copy2kRes = __copy_from_user(buffer, source, sizeof(int)*arrDepth*nArr);
    if (copy2kRes!=0) {
        return 1;
    }

    int copy2uRes;
    copy2uRes = __copy_to_user(destination, buffer, sizeof(int)*arrDepth*nArr);
    if (copy2uRes!=0) {
        return -1;
    }

    return 0;

}