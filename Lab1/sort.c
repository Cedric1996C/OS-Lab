#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include "queue.h"
#define ArrLen 10

QueueDef* MyQueue;
void SelectSort(int *pData,int size)
{
    int i;
    for( i = 0;i<size-1;++i){
        int index = i;
        int j;
        for(j = i+1;j<size;++j) {
        if(pData[j]<pData[index])
            index = j;
        }
         if(index != i){
            int temp = pData[i];
            pData[i] = pData[index];
            pData[index] = temp;
         }
    }
    pid_t pid;
    int num = 0;
    pid = fork();
    if(pid == 0) {//子进程
        InsertQueue(MyQueue,10);
        unsigned int Addr = MyQueue->Head;
        printf("In Child Process MyQueue Addr is: %x.\n",Addr);
    }
    else{//父进程
        unsigned int Addr = MyQueue->Head;
        printf("In Parent Process MyQueue Addr is： %x.\n Sleep!\n",Addr);
        sleep(5);
        printf(" Wake!\n");
    }
}


int Array[ArrLen] = {6,5,7,1,3,22,45,2,4,9};

int main(){
    MyQueue = NewQueue();
    int ele = 0;
    for(; ele < 10; ele++)
        InsertQueue(MyQueue,ele);
     printf("Before Sort:\n");
     int i;
     for(i = 0; i < ArrLen; i++){
         printf("%u ",Array[i]);
     }
     printf("\n");
     SelectSort(Array,ArrLen);
     printf("After Sort:\n");
     int j;
     for(j = 0; j < ArrLen; j++)
         printf("%u ",Array[j]);
     printf("\n");
     printf("MyQueue (length %u)is: \n",MyQueue->length);
     Node *ptr = MyQueue->Head;
         printf("%u ",ptr->content);
     while(ptr->link != NULL){
         ptr = ptr->link;
         printf("%u ",ptr->content);
     }
     printf("\n");
     return 0;
}
