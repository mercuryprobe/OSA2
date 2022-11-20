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

        execvp("./runnerA.sh", NULL);

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