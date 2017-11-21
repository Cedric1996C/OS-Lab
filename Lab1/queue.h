#ifndef __QUEUE_H_
#define __QUEUE_H__
#include <stdlib.h>
#include <stdio.h>
struct QueueNode{
    int content;
    struct QueueNode* link;
};
typedef struct QueueNode Node;
struct Queue{
Node* Head;
Node* Tail;
int length;
};
typedef struct Queue QueueDef;
QueueDef* NewQueue();
     
void InsertQueue(QueueDef* Q,int Element);

Node* PopQueue(QueueDef *Q);
    
#endif
