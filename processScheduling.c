#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sched.h>
#include <time.h>

void processA() {
    struct timespec start;
    struct timespec stop;
    double billion = 1000000000;
  
    clock_gettime(CLOCK_REALTIME, &start);
    pid_t pid = fork();
    int stat;
    if (pid==0) {
        struct sched_param paramA;
        paramA.sched_priority = 0;
        int setRes = sched_setscheduler(0, SCHED_OTHER, &paramA);
        if (setRes!=0) {perror("A: Error");}

        char *arr1[48] = {"kernelbuild/linux-5.19.81/linux-5.19.8"};
        char *arr7[8] = {"pwd"};
        char *arr2[16] = {"mrproper"};
        char *arr3[8] = {".."};
        char *arr4[48] = {".config", "linux-5.19.81/linux-5.19.8"};
        char *arr5[48] = {"linux-5.19.81/linux-5.19.8"};
        // char *arr6[8] = {"make"};
        execvp("/bin/cd", arr1);
        execvp("/bin/pwd", arr7);
        execvp("/bin/make", arr2);
        execvp("/bin/cd", arr3);
        execvp("/bin/cp", arr4);
        execvp("/bin/cd", arr5);
        execvp("/bin/make", NULL);

    } else if(pid>0) {
        waitpid(pid, &stat, 0);
        clock_gettime(CLOCK_REALTIME, &stop);

        double duration = stop.tv_sec + stop.tv_nsec/billion - (start.tv_sec + start.tv_nsec/billion);

        printf("Process A runtime: %lf\n", duration);

    } else {
        puts("Process A failed to fork!");
    }
}

int main() {
    processA();
    return 0;
}