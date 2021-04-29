#include <iostream>
#include <string.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std; 

struct Queue {
    int front, rear, size;
    unsigned capacity;
    int* array;
};
 
struct Queue* createQueue(unsigned capacity)
{
    struct Queue* queue = (struct Queue*)malloc(
        sizeof(struct Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
 
    queue->rear = capacity - 1;
    queue->array = (int*)malloc(
        queue->capacity * sizeof(int));
    return queue;
}
 
int isFull(struct Queue* queue)
{
    return ( (unsigned) queue->size == queue->capacity);
}
 
int isEmpty(struct Queue* queue)
{
    return (queue->size == (unsigned) 0);
}
 
void enqueue(struct Queue* queue, int item)
{
    if (isFull(queue)){
        return;
    }
    queue->rear = (queue->rear + 1)
                  % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size = queue->size + 1;
    // printf("%d enqueued to queue\n", item);
}
 
int dequeue(struct Queue* queue)
{
    if (isEmpty(queue)){
        free(queue);
        return INT_MIN;
    }
    int item = queue->array[queue->front];
    queue->front = (queue->front + 1)
                   % queue->capacity;
    queue->size = queue->size - 1;
    return item;
}
 
int front(struct Queue* queue)
{
    if (isEmpty(queue))
        return INT_MIN;
    return queue->array[queue->front];
}
 
int rear(struct Queue* queue)
{
    if (isEmpty(queue))
        return INT_MIN;
    return queue->array[queue->rear];
}




// struct Queue* elementos[10000000];   
int main(int argc, char **argv)
{    
    int t, v, p, k = 1;
    string in;
    while(scanf("%d",&t),t){

        struct Queue* teamQueue[t];
        struct Queue** elementos= (Queue**) malloc(10000000*sizeof(struct Queue));
        while(t--){ 
            cin >> v;
            struct Queue* queue = createQueue(v);
            for(int i=0;i<v;i++){
                cin >> p;
                elementos[p] = queue;
            }
        }
        cout << "Scenario #" << k++ << endl;
        int iterator = 0;
        int aux = 0;
        while(cin >> in, in != "STOP"){
            if(in == "ENQUEUE"){
                cin >> p;
                enqueue(elementos[p], p);   

                
                if(elementos[p]->size == (unsigned) 1) {
                    teamQueue[aux] = elementos[p];
                    // cout << "Endereço de memória do elemento " << p << " " << elementos[p] << endl; 
                    // cout << "Front do elemento " << p << ": " << front(elementos[p]) <<endl;
                    // cout << "Rear do elemento " << p << ": " << rear(elementos[p]) <<endl;
                    // cout << "Size do elemento " << p << ": " << elementos[p]->size << endl;
                    aux++;
                }
            }else {
                // if(k == 4){
                // cout << "Endereço do iterator " << iterator << ": " << teamQueue[iterator] << endl;
                // cout << "size do elemento atual: " << teamQueue[iterator]->size << " " << "iterator: " << iterator << endl;
                // cout << "top: " << front(teamQueue[iterator]) << endl;
                // cout << "vale: " << rear(teamQueue[iterator]) << endl;
                // cout << "Teste de acesso ao array: " << teamQueue[iterator]->array << endl;
                // }

                // cout << "Checkpoint: " << rear(teamQueue[iterator]) << endl;
                cout << dequeue(teamQueue[iterator]) << endl;
                if(isEmpty(teamQueue[iterator])) {
                    iterator++;
                }
            }
        }
        cout << endl;
        free(elementos);
        free(teamQueue);
    }
	return 0;
}



