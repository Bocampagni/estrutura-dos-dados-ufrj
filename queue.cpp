#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
using namespace std;

struct Node {
    int data;
    struct Node* next;
};

/* Given a reference (pointer to pointer) to the head of a list
   and an int,  inserts a new node on the front of the list. */
void push(struct Node** head_ref, int new_data)
{
    /* 1. allocate node */
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
   
    /* 2. put in the data  */
    new_node->data  = new_data;
   
    /* 3. Make next of new node as head */
    new_node->next = (*head_ref);
   
    /* 4. move the head to point to the new node */
    (*head_ref) = new_node;
}

/* Given a node prev_node, insert a new node after the given 
prev_node */
void insertAfter(struct Node* prev_node, int new_data) 
{ 
    /*1. check if the given prev_node is NULL */
    if (prev_node == NULL) 
    { 
    printf("the given previous node cannot be NULL");     
    return; 
    } 
          
    /* 2. allocate new node */
    struct Node* new_node =(struct Node*) malloc(sizeof(struct Node)); 
  
    /* 3. put in the data */
    new_node->data = new_data; 
  
    /* 4. Make next of new node as next of prev_node */
    new_node->next = prev_node->next; 
  
    /* 5. move the next of prev_node as new_node */
    prev_node->next = new_node; 
}

/* Given a node prev_node, insert a new node after the given 
prev_node */
Node* insertAfterThatReturnsNode(struct Node* prev_node, int new_data) 
{ 
    if (prev_node == NULL) 
    { 
    printf("the given previous node cannot be NULL");     
    return NULL; 
    } 
    /* 1. allocate new node */
    struct Node* new_node =(struct Node*) malloc(sizeof(struct Node)); 
  
    /* 2. put in the data */
    new_node->data = new_data; 
  
    /* 3. Make next of new node as next of prev_node */
    new_node->next = prev_node->next; 
  
    /* 4. move the next of prev_node as new_node */
    prev_node->next = new_node; 

    return new_node;
}

/* Given a reference (pointer to pointer) to the head
   of a list and an int, appends a new node at the end  */
void append(struct Node** head_ref, int new_data)
{
    /* 1. allocate node */
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
  
    struct Node *last = *head_ref;  /* used in step 5*/
  
    /* 2. put in the data  */
    new_node->data  = new_data;
  
    /* 3. This new node is going to be the last node, so make next of
          it as NULL*/
    new_node->next = NULL;
  
    /* 4. If the Linked List is empty, then make the new node as head */
    if (*head_ref == NULL)
    {
       *head_ref = new_node;
       return;
    }
  
    /* 5. Else traverse till the last node */
    while (last->next != NULL)
        last = last->next;
  
    /* 6. Change the next of last node */
    last->next = new_node;
    return;
}

Node* appendThatReturnsNode(struct Node** head_ref, int new_data)
{
    /* 1. allocate node */
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
  
    struct Node *last = *head_ref;  /* used in step 5*/
  
    /* 2. put in the data  */
    new_node->data  = new_data;
  
    /* 3. This new node is going to be the last node, so make next of
          it as NULL*/
    new_node->next = NULL;
  
    /* 4. If the Linked List is empty, then make the new node as head */
    if (*head_ref == NULL)
    {
       *head_ref = new_node;
       return new_node;
    }
  
    /* 5. Else traverse till the last node */
    while (last->next != NULL)
        last = last->next;
  
    /* 6. Change the next of last node */
    last->next = new_node;
    return new_node;
}
// This function prints contents of linked list starting from head
void printList(struct Node *node)
{
  while (node != NULL)
  {
     printf(" %d ", node->data);
     node = node->next;
  }

  printf("\n");
}
/* Driver program to test above functions*/

// int main()
// {
//   /* Start with the empty list */
//   struct Node* head = NULL;
  
//   // Insert 6.  So linked list becomes 6->NULL
//   append(&head, 6);
  
//   // Insert 7 at the beginning. So linked list becomes 7->6->NULL
//   push(&head, 7);
  
//   // Insert 1 at the beginning. So linked list becomes 1->7->6->NULL
//   push(&head, 1);
  
//   // Insert 4 at the end. So linked list becomes 1->7->6->4->NULL
//   append(&head, 4);
  
//   // Insert 8, after 7. So linked list becomes 1->7->8->6->4->NULL
//   insertAfter(head->next, 8);
  
//   printf("\n Created Linked list is: ");
//   printList(head);
  
//   return 0;
// }

/* Given a reference (pointer to pointer) to the head of a list
   and a position, deletes the node at the given position */
void deleteNode(struct Node **head_ref, int position)
{
   // If linked list is empty
   if (*head_ref == NULL)
      return;
 
   // Store head node
   struct Node* temp = *head_ref;
 
    // If head needs to be removed
    if (position == 0)
    {   
        cout << temp->data << endl;
        *head_ref = temp->next;   // Change head
        free(temp);               // free old head
        return;
    }
 
    // Find previous node of the node to be deleted
    for (int i=0; temp!=NULL && i<position-1; i++)
         temp = temp->next;
 
    // If position is more than number of nodes
    if (temp == NULL || temp->next == NULL)
         return;
 
    // Node temp->next is the node to be deleted
    // Store pointer to the next of node to be deleted
    struct Node *next = temp->next->next;
 
    // Unlink the node from linked list
    free(temp->next);  // Free memory
 
    temp->next = next;  // Unlink the deleted node from list
}

int main() {
    int t, v, p, k = 1;
    string in;
    while(scanf("%d",&t),t){
        struct Node* head = NULL;
        int* array = (int*) malloc(1000000 * sizeof(int)); //Array de times
        struct Node* times[t] = {(struct Node*) NULL};
        while(t--){ 
            cin >> v;
            for(int i=0;i<v;i++){
                cin >> p;
                array[p] = t; //Elemento p pertence ao grupo v.
            }
        }
        cout << "Scenario #" << k++ << endl;
        while(cin >> in, in != "STOP"){
            if(in == "ENQUEUE"){
                cin >> p;
                if(head == NULL){
                    times[array[p]] = appendThatReturnsNode(&head,p); //A posição array[p] = numero de time aponta para o último elemento da lista
                }else{
                    //Se a lista não tiver vazia, é preciso verificar onde vamos colocar o elemento.
                    //Como verificar ??
                    //O certo seria olhar no array com menor index pra ver pra onde ele aponta.
                    //Olhar no ponteiro do time do elemento pra ver se ele aponta para algum lugar, se sim, insertAfter nele.
                    //Caso contrário, ele entra no final da fila.
                    if(times[array[p]] == NULL){
                        times[array[p]] = appendThatReturnsNode(&head, p);
                    }else{
                        times[array[p]] = insertAfterThatReturnsNode(times[array[p]], p);
                    }
                }
            } else {
                deleteNode(&head, 0);
                //Lógica de remoção do primeiro item da fila.
                // printList(head);
            }
        }
        cout << endl;
    }
}