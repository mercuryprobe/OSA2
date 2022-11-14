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


int ThrA() {
  struct timespec start;
  struct timespec stop;
  
  pthread_setschedparam(pthread_self(), SCHED_FIFO, NULL);
  puts("Thread A created.");
  
  clock_gettime(CLOCK_REALTIME, &start);
  countA();
  clock_gettime(CLOCK_REALTIME, &stop);
  time_t duration = stop.tv_sec - start.tv_sec;

  printf("Thread A runtime: %lld\n", (long long) duration(NULL));
  return 0;
}

int ThrB() {
  struct timespec start;
  struct timespec stop;
  
  pthread_setschedparam(pthread_self(), SCHED_RR, NULL);
  puts("Thread B created.");
  
  clock_gettime(CLOCK_REALTIME, &start);
  countB();
  clock_gettime(CLOCK_REALTIME, &stop);
  time_t duration = stop.tv_sec - start.tv_sec;

  printf("Thread A runtime: %lld\n", (long long) duration(NULL));
  return 0;
}

int ThrC() {
  struct timespec start;
  struct timespec stop;
  
  pthread_setschedparam(pthread_self(), SCHED_OTHER, NULL);
  puts("Thread C created.");
  
  clock_gettime(CLOCK_REALTIME, &start);
  countC();
  clock_gettime(CLOCK_REALTIME, &stop);
  time_t duration = stop.tv_sec - start.tv_sec;

  printf("Thread A runtime: %lld\n", (long long) duration(NULL));
  return 0;
}


int main() {
  pthread_t thrAid;
  pthread_t thrBid;
  pthread_t thrCid;

  pthread_create(&thrAid, NULL, &ThrA, NULL);
  pthread_create(&thrBid, NULL, &ThrB, NULL);
  pthread_create(&thrCid, NULL, &ThrC, NULL);

  pthread_join(thrAid, NULL);
  pthread_join(thrBid, NULL);
  pthread_join(thrCid, NULL);
  return 0;
}