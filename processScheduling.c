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
        int setRes =  1;
        setRes = sched_setscheduler(0, SCHED_OTHER, &paramA);
        if (setRes!=0) {perror("A: Error");}
        
        char *arr[16] = {"./runnerA.sh", NULL};
        execvp("./runnerA.sh", arr);

    } else if(pid>0) {
        waitpid(pid, &stat, 0);
        clock_gettime(CLOCK_REALTIME, &stop);

        double duration = stop.tv_sec + stop.tv_nsec/billion - (start.tv_sec + start.tv_nsec/billion);

        printf("Process A runtime: %lf\n", duration);

    } else {
        puts("Process A failed to fork!");
    }
}

void processB() {
    struct timespec start;
    struct timespec stop;
    double billion = 1000000000;
  
    clock_gettime(CLOCK_REALTIME, &start);
    pid_t pid = fork();
    int stat;
    if (pid==0) {
        struct sched_param paramB;
        paramB.sched_priority = 0;
        int setRes =  1;
        setRes = sched_setscheduler(0, SCHED_OTHER, &paramB);
        if (setRes!=0) {perror("B: Error");}
        
        char *arr[16] = {"./runnerB.sh", NULL};
        execvp("./runnerB.sh", arr);

    } else if(pid>0) {
        waitpid(pid, &stat, 0);
        clock_gettime(CLOCK_REALTIME, &stop);

        double duration = stop.tv_sec + stop.tv_nsec/billion - (start.tv_sec + start.tv_nsec/billion);

        printf("Process B runtime: %lf\n", duration);

    } else {
        puts("Process B failed to fork!");
    }
}

void processC() {
    struct timespec start;
    struct timespec stop;
    double billion = 1000000000;
  
    clock_gettime(CLOCK_REALTIME, &start);
    pid_t pid = fork();
    int stat;
    if (pid==0) {
        struct sched_param paramC;
        paramC.sched_priority = 0;
        int setRes =  1;
        setRes = sched_setscheduler(0, SCHED_OTHER, &paramC);
        if (setRes!=0) {perror("C: Error");}
        
        char *arr[16] = {"./runnerC.sh", NULL};
        execvp("./runnerC.sh", arr);

    } else if(pid>0) {
        waitpid(pid, &stat, 0);
        clock_gettime(CLOCK_REALTIME, &stop);

        double duration = stop.tv_sec + stop.tv_nsec/billion - (start.tv_sec + start.tv_nsec/billion);

        printf("Process C runtime: %lf\n", duration);

    } else {
        puts("Process C failed to fork!");
    }
}

int main() {
    processA();
    processB();
    processC();
    return 0;
}