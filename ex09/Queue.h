/******************************************************************************
 * File:         Queue.h
 * Version:      1.1
 * Date:         2016-03-31
 * Author:       M. van der Sluys, J. Onokiewicz
 * Description:  OPS excercise 5: Queues
 ******************************************************************************/


#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>
#include <pthread.h>
#define TEXT_SIZE 20


typedef struct {
  int intVal;
  char text[TEXT_SIZE];
} data_t;

typedef struct node {
  data_t data;
  struct node* nextNode;
} node_t;

typedef struct {
  node_t* lastNode;
} queue_t;

void createQueue(queue_t* queue, data_t data);
int emptyQueue(const queue_t* queue);
size_t sizeQueue(const queue_t* queue);
data_t* frontQueue(const queue_t* queue);
data_t* backQueue(const queue_t* queue);
void pushQueue(queue_t* queue, data_t data);
void popQueue(queue_t* queue);
void deleteQueue(queue_t* queue);
void showQueue(const queue_t* queue);
void printQueue(const queue_t* queue);
#endif
