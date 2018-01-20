/******************************************************************************
 * File:         Queue.c
 * Version:      1.0
 * Date:         2018-01-17
 * Author:       Reinier van Leeuwen
 * Description:  OPS excercise 9
 ******************************************************************************/


#include "Queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void createQueue(queue_t* queue, data_t data) {
  if(queue->lastNode != NULL) deleteQueue(queue);

  node_t* newNode = (node_t*) malloc(sizeof(node_t));
  queue->lastNode = newNode;
  if(newNode != NULL) {
    newNode->data = data;
    newNode->nextNode = newNode;
  }
}

  int emptyQueue(const queue_t* queue) {
  return (queue->lastNode == NULL);
}


size_t sizeQueue(const queue_t* queue) {
  size_t size = 1;
  node_t* currentNode;

  if(emptyQueue(queue)) return 0;

  // Loop until circle is complete (nextNode equals last node):
  for(currentNode = queue->lastNode;
      currentNode != NULL && currentNode->nextNode != queue->lastNode;
      currentNode = currentNode->nextNode) {
    size++;
  }

  return size;
}


data_t* frontQueue(const queue_t* queue) {
  return &(queue->lastNode->nextNode->data);
}


data_t* backQueue(const queue_t* queue) {
  return &(queue->lastNode->data);
}

void pushQueue(queue_t* queue, data_t data) {
if(emptyQueue(queue)){
  printf("\nQueue is emty. Create a new queue!\n\n");
}
else{
  node_t* newNode = (node_t*) malloc(sizeof(node_t));
  if(newNode != NULL) {
    newNode->data = data;
    newNode->nextNode = queue->lastNode->nextNode;
    queue->lastNode->nextNode = newNode;
    queue->lastNode = newNode;
  }
}
}

void popQueue(queue_t* queue) {
  if(queue->lastNode != NULL) {
    node_t* pDelete = queue->lastNode->nextNode;
    if(pDelete == queue->lastNode) {
      queue->lastNode = NULL;
    } else {
      queue->lastNode->nextNode = pDelete->nextNode;
    }
    free(pDelete);
  }
}

void deleteQueue(queue_t* queue) {
  node_t* currentNode = queue->lastNode, * nextN = NULL;

  do {
    if(currentNode == NULL) break;
    nextN = currentNode->nextNode;
    free(currentNode);
    currentNode = nextN;
  } while(currentNode != queue->lastNode);

  queue->lastNode = NULL;
}

void showQueue(const queue_t* queue) {
  const node_t* nextN = queue->lastNode;
  if(nextN == NULL) {
    printf("Queue is empty, last node is %p\n", (void*) queue->lastNode);
  } else {
    printf("Queue contains %ld nodes:\n", sizeQueue(queue));
    do {
      nextN = nextN->nextNode;
      printf("pNode = %p  Data = '%d' '%s'  nextN = %p\n",
             (void*)nextN, nextN->data.intVal, nextN->data.text, (void*)nextN->nextNode);
    } while(nextN != queue->lastNode);
  }
}

void printQueue(const queue_t* queue) {
  FILE *fd = fopen("\\showQ.txt","w");
  if(fd == NULL){
    printf("\n\nERROR FILE CREATE\n\n");
  }
  const node_t* nextN = queue->lastNode;
  if(nextN == NULL) {
    fprintf(fd,"Queue is empty, last node is %p\n", (void*) queue->lastNode);
  } else {
    fprintf(fd,"Queue contains %ld nodes:\n", sizeQueue(queue));
    fprintf(fd,"Last node: %p\n", (void*) queue->lastNode);
    do {
      nextN = nextN->nextNode;
      fprintf(fd,"pNode = %p  Data = '%d' '%s'  nextN = %p\n",
             (void*)nextN, nextN->data.intVal, nextN->data.text, (void*)nextN->nextNode);
    } while(nextN != queue->lastNode);
  }
  fclose(fd);
}
