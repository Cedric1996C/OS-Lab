#include "queue.h"
QueueDef* NewQueue(){
     QueueDef *QueuePtr = (QueueDef*)malloc(sizeof(QueueDef));
     if(QueuePtr == NULL){
         printf("Memory wrong!\n");
         exit(-1);
      }
     QueuePtr->Head = QueuePtr->Tail = NULL;
     QueuePtr->length = 0;

}

void InsertQueue(QueueDef* Q,int Element){
    Node *NewNode = (Node *)malloc(sizeof(Node));
    NewNode->link = NULL;
    NewNode->content = Element;
    if(Q->length == 0){
         Q->Head = NewNode;
         Q->Tail = NewNode;
         Q->length++;
     }
    else{
         Q->Tail->link = NewNode;
         Q->Tail = NewNode;
         Q->length++;
     }
}

Node *PopQueue(QueueDef *Q){
    if(Q->length == 0){
        printf("Empty Queue!");
        return NULL;
    }
    if(Q->length == 1){
        Node *tmp = Q->Head;
        Q->Head = Q->Tail = NULL;
        Q->length--;
        return tmp;
    }
    Node *tmp = Q->Head;
    Q->Head = Q->Head->link;
    Q->length--;
    return tmp;
}
