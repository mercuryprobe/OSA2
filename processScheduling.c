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

        char *arr1[48] = {"cd", "kernel1build/linux-5.19.81/linux-5.19.8", NULL};
        char *arr7[8] = {"pwd", NULL};
        char *arr2[16] = {"make", "mrproper", NULL};
        char *arr3[8] = {"cd", "..", NULL};
        char *arr4[48] = {"cp", ".config", "linux-5.19.81/linux-5.19.8", NULL};
        char *arr5[48] = {"cd", "linux-5.19.81/linux-5.19.8", NULL};
        char *arr6[8] = {"make", NULL};
        execvp("cd", arr1);
        execvp("pwd", arr7);
        execvp("make", arr2);
        execvp("cd", arr3);
        execvp("cp", arr4);
        execvp("cd", arr5);
        execvp("make", arr6);

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