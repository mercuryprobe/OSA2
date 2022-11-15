#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>


int countA() {
  for (unsigned long int i = 1; i<=4294967296; i++) {
  }
  return 0;
}

int countB() {
  for (unsigned long int i = 1; i<=4294967296; i++) {
  }
  return 0;
}

int countC() {
  for (unsigned long int i = 1; i<=4294967296; i++) {
  }
  return 0;
}


void *ThrA(void *no) {
  struct sched_param param;
  param.sched_priority = 0;

  pthread_setschedparam(pthread_self(), SCHED_OTHER, &param);
  puts("Thread A created.");
  struct timespec start;
  struct timespec stop;
  double billion = 1000000000;
  
  clock_gettime(CLOCK_REALTIME, &start);
  countA();
  clock_gettime(CLOCK_REALTIME, &stop);
  double duration = stop.tv_sec + stop.tv_nsec/billion - (start.tv_sec + start.tv_nsec/billion);

  printf("Thread A runtime: %lf\n", duration);
}

void *ThrB(void *no) {
  struct sched_param param;
  param.sched_priority = 1;
  pthread_setschedparam(pthread_self(), SCHED_RR, &param);
  puts("Thread B created.");
  struct timespec start;
  struct timespec stop;
  double billion = 1000000000;
  
  clock_gettime(CLOCK_REALTIME, &start);
  countB();
  clock_gettime(CLOCK_REALTIME, &stop);
  double duration = stop.tv_sec + stop.tv_nsec/billion - (start.tv_sec + start.tv_nsec/billion);

  printf("Thread B runtime: %lf\n", duration);
}

void *ThrC(void *no) {
  struct sched_param param;
  param.sched_priority = 1;
  pthread_setschedparam(pthread_self(), SCHED_FIFO, &param);
  puts("Thread C created.");
  struct timespec start;
  struct timespec stop;
  double billion = 1000000000;
  
  clock_gettime(CLOCK_REALTIME, &start);
  countC();
  clock_gettime(CLOCK_REALTIME, &stop);
  double duration = stop.tv_sec + stop.tv_nsec/billion - (start.tv_sec + start.tv_nsec/billion);

  printf("Thread C runtime: %lf\n", duration);
}


int main() {
  pthread_t thrAid;
  pthread_t thrBid;
  pthread_t thrCid;

  pthread_create(&thrAid, NULL, ThrA, NULL);
  pthread_create(&thrBid, NULL, ThrB, NULL);
  pthread_create(&thrCid, NULL, ThrC, NULL);

  pthread_join(thrAid, NULL);
  pthread_join(thrBid, NULL);
  pthread_join(thrCid, NULL);
  return 0;
}