/******************************************************************************
 * File:         main.c
 * Version:      1.0
 * Date:         2018-01-17
 * Author:       Reinier van Leeuwen
 * Description:  OPS excercise 9
 ******************************************************************************/


#define _XOPEN_SOURCE 500
#define _POSIX_C_SOURCE 199309L

#include "sys/mman.h"
#include "fcntl.h"
#include "string.h"
#include "Queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>

void *producer(void *msg);
void *consumer(void *msg);
void newHandler();

data_t data1 = {1,"Hello Queue  "};
data_t data2 = {2, "Hello thread2"};
data_t data3 = {3, "Hello thread3"};
data_t data4 = {4, "Hello thread4"};
queue_t queue = {NULL};
pthread_mutex_t MutexQ = PTHREAD_MUTEX_INITIALIZER;

int wait15 = 15;
int fd;
int looping = 1;

int main() {

  struct sigaction act, oldact;

  memset(&act, '\0', sizeof(act));
  act.sa_handler = newHandler;
  act.sa_flags = 0;
  sigemptyset(&act.sa_mask);

  sigaction(SIGINT, &act, &oldact);

  pthread_t ThreadID_2, ThreadID_3, ThreadID_4, ThreadID_15;

  if(pthread_create(&ThreadID_2, NULL, producer, (void *)&data2)) {
    fprintf(stderr, "No thread A\n");
    exit(EXIT_FAILURE);
  }

  if(pthread_create(&ThreadID_3, NULL, producer, (void *)&data3)) {
    fprintf(stderr, "No thread A\n");
    exit(EXIT_FAILURE);
  }

  if(pthread_create(&ThreadID_4, NULL, producer, (void *)&data4)) {
    fprintf(stderr, "No thread A\n");
    exit(EXIT_FAILURE);
  }

  if(pthread_create(&ThreadID_15, NULL, consumer, (void *)&wait15)) {
    fprintf(stderr, "No thread A\n");
    exit(EXIT_FAILURE);
  }

  pthread_join(ThreadID_2, NULL);
  pthread_join(ThreadID_3, NULL);
  pthread_join(ThreadID_4, NULL);
  pthread_join(ThreadID_15, NULL);

  return 0;
}

void newHandler() {
  looping = 0;
}

void *producer(void *msg) {
  while(looping){
    data_t message = *(data_t*)msg;
    sleep(message.intVal);
    pthread_mutex_lock(&MutexQ);
    printf("\ncase %d:\n",message.intVal);
    pushQueue(&queue, message);
    pthread_mutex_unlock(&MutexQ);
  }
}

void *consumer(void *msg) {
while(looping){
    data_t message = *(data_t*)msg;
    pthread_mutex_lock(&MutexQ);
    printf("\ncase %d:\n",message.intVal);
    showQueue(&queue);
    printQueue(&queue);
    deleteQueue(&queue);
    createQueue(&queue, data1);
    pthread_mutex_unlock(&MutexQ);
    sleep(message.intVal);
  }
}
