#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sched.h>
#include <time.h>

void compile3() {
    struct timespec startA;
    struct timespec stopA;
    struct timespec startB;
    struct timespec stopB;
    struct timespec startC;
    struct timespec stopC;

    double billion = 1000000000;
    int setRes =  1;
    int stat;
    
    pid_t pidA = fork();

    if (pidA==0) {
        clock_gettime(CLOCK_REALTIME, &startA);
        printf("Process A started!\n");
        
        struct sched_param paramA;
        paramA.sched_priority = 0;
        setRes = sched_setscheduler(0, SCHED_OTHER, &paramA);
        if (setRes!=0) {perror("A: Error");}
        
        char *arr[16] = {"./runnerA.sh", NULL};
        execvp("./runnerA.sh", arr);

    } else if (pidA>0) {
        pid_t pidB = fork();

        if (pidB==0) {
            clock_gettime(CLOCK_REALTIME, &startB);
            printf("Process B started!\n");

            struct sched_param paramB;
            paramB.sched_priority = 1;
            setRes = sched_setscheduler(0, SCHED_RR, &paramB);
            if (setRes!=0) {perror("B: Error");}
            
            char *arr[16] = {"./runnerB.sh", NULL};
            execvp("./runnerB.sh", arr);

        } else if (pidB>0) {
            pid_t pidC = fork();
            
            if (pidC==0) {
                clock_gettime(CLOCK_REALTIME, &startC);
                printf("Process C started!");

                struct sched_param paramC;
                paramC.sched_priority = 1;                
                setRes = sched_setscheduler(0, SCHED_FIFO, &paramC);
                if (setRes!=0) {perror("C: Error");}
                
                char *arr[16] = {"./runnerC.sh", NULL};
                execvp("./runnerC.sh", arr);

            } else if (pidC>0) {
                int finishedThreads = 0;
                while (finishedThreads<3) {
                    int curID = waitpid(-1, &stat, 0);
                    
                    if (pidA==curID) {clock_gettime(CLOCK_REALTIME, &stopA);}
                    if (pidB==curID) {clock_gettime(CLOCK_REALTIME, &stopB);}
                    if (pidC==curID) {clock_gettime(CLOCK_REALTIME, &stopC);}
                    finishedThreads +=1;

                }
            } else {
                puts("Process C failed to fork!");
            }
        } else {
            puts("Process B failed to fork!");

        }

        double durationA = stopA.tv_sec + stopA.tv_nsec/billion - (startA.tv_sec + startA.tv_nsec/billion);
        double durationB = stopB.tv_sec + stopB.tv_nsec/billion - (startB.tv_sec + startB.tv_nsec/billion);
        double durationC = stopC.tv_sec + stopC.tv_nsec/billion - (startC.tv_sec + startC.tv_nsec/billion);

        printf("Process A runtime: %lf\n", durationA);
        printf("Process B runtime: %lf\n", durationB);
        printf("Process C runtime: %lf\n", durationC);

    } else {
        puts("Process A failed to fork!");
    }
}

// void processA() {
//     struct timespec start;
//     struct timespec stop;
//     double billion = 1000000000;
  
//     clock_gettime(CLOCK_REALTIME, &start);
//     pid_t pid = fork();
//     int stat;
//     if (pid==0) {
//         puts("Process A started!"); 
//         struct sched_param paramA;
//         paramA.sched_priority = 0;
//         int setRes =  1;
//         setRes = sched_setscheduler(0, SCHED_OTHER, &paramA);
//         if (setRes!=0) {perror("A: Error");}
        
//         char *arr[16] = {"./runnerA.sh", NULL};
//         execvp("./runnerA.sh", arr);

//     } else if(pid>0) {
        
//         waitpid(pid, &stat, 0);
//         clock_gettime(CLOCK_REALTIME, &stop);

//         double duration = stop.tv_sec + stop.tv_nsec/billion - (start.tv_sec + start.tv_nsec/billion);

//         printf("Process A runtime: %lf\n", duration);

//     } else {
//         puts("Process A failed to fork!");
//     }
// }

// void processB() {
//     struct timespec start;
//     struct timespec stop;
//     double billion = 1000000000;
  
//     clock_gettime(CLOCK_REALTIME, &start);
//     pid_t pid = fork();
//     int stat;
//     if (pid==0) {
//         puts("Process B started!");
//         struct sched_param paramB;
//         paramB.sched_priority = 1;
//         int setRes =  1;
//         setRes = sched_setscheduler(0, SCHED_RR, &paramB);
//         if (setRes!=0) {perror("B: Error");}
        
//         char *arr[16] = {"./runnerB.sh", NULL};
//         execvp("./runnerB.sh", arr);

//     } else if(pid>0) {
//         waitpid(pid, &stat, 0);
//         clock_gettime(CLOCK_REALTIME, &stop);

//         double duration = stop.tv_sec + stop.tv_nsec/billion - (start.tv_sec + start.tv_nsec/billion);

//         printf("Process B runtime: %lf\n", duration);

//     } else {
//         puts("Process B failed to fork!");
//     }
// }

// void processC() {
//     struct timespec start;
//     struct timespec stop;
//     double billion = 1000000000;
  
//     clock_gettime(CLOCK_REALTIME, &start);
//     pid_t pid = fork();
//     int stat;
//     if (pid==0) {
//         puts("Process C started!");
//         struct sched_param paramC;
//         paramC.sched_priority = 1;
//         int setRes =  1;
//         setRes = sched_setscheduler(0, SCHED_FIFO, &paramC);
//         if (setRes!=0) {perror("C: Error");}
        
//         char *arr[16] = {"./runnerC.sh", NULL};
//         execvp("./runnerC.sh", arr);

//     } else if(pid>0) {
//         waitpid(pid, &stat, 0);
//         clock_gettime(CLOCK_REALTIME, &stop);

//         double duration = stop.tv_sec + stop.tv_nsec/billion - (start.tv_sec + start.tv_nsec/billion);

//         printf("Process C runtime: %lf\n", duration);

//     } else {
//         puts("Process C failed to fork!");
//     }
// }

int main() {
    compile3();
    return 0;
}