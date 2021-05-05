#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
using namespace std;

struct Node {
    int data;
    struct Node* next;
};

Node* insertAfterThatReturnsNode(struct Node* prev_node, int new_data) 
{ 
    if (prev_node == NULL) 
    { 
        return NULL; 
    } 
    struct Node* new_node =(struct Node*) malloc(sizeof(struct Node)); 
  
    new_node->data = new_data; 
  
    new_node->next = prev_node->next; 
  
    prev_node->next = new_node; 

    return new_node;
}

Node* appendThatReturnsNode(struct Node** head_ref, int new_data)
{
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
  
    struct Node *last = *head_ref;  
  
    new_node->data  = new_data;
  
    new_node->next = NULL;
  
    if (*head_ref == NULL)
    {
       *head_ref = new_node;
       return new_node;
    }
  
    while (last->next != NULL)
        last = last->next;
  
    last->next = new_node;
    return new_node;
}

void deleteNode(struct Node **head_ref, int position)
{
   if (*head_ref == NULL)
      return;
 
   struct Node* temp = *head_ref;
 
    if (position == 0)
    {   
        cout << temp->data << endl;
        *head_ref = temp->next;   
        free(temp);               
        return;
    }  
}

int main() {
    int t, v, p, size, k = 1;
    string in;
    while(scanf("%d",&t),t){
        size = t;
        struct Node* head = NULL;
        int* array = (int*) malloc(1000000 * sizeof(int)); 
        struct Node* times[t] = {(struct Node*) NULL};
        while(t--){ 
            cin >> v;
            for(int i=0;i<v;i++){
                cin >> p;
                array[p] = t; 
            }
        }
        cout << "Scenario #" << k++ << endl;
        while(cin >> in, in != "STOP"){
            if(in == "ENQUEUE"){
                cin >> p;
                if(head == NULL){
                    times[array[p]] = appendThatReturnsNode(&head,p); 
                }else{
                    if(times[array[p]] == NULL){
                        times[array[p]] = appendThatReturnsNode(&head, p);
                    }else{
                        times[array[p]] = insertAfterThatReturnsNode(times[array[p]], p);
                    }
                }
            } else {
                struct Node* aux = head;
                deleteNode(&head, 0);
                for(int i = 0; i < size ; i++){
                    if(aux == times[i]){
                        times[i] = NULL;
                        break;
                    }
                }
            }
        }
        cout << endl;
    }
}