#include "linked_list.h"
#include <stdio.h>
#include "common_defs.h"

// typedef struct Node{
//     uint16_t data; // Stores the data as an unsigned 16-bit integer
//     struct Node* next; // A pointer to the next node in the List
// }Node;

Node** list;

Node* front = NULL;
size_t nrOfNodes = 0;

void list_init(Node** head, size_t size)
{
    *head = front;
    printf("list initialized successfully!\n");
}

void list_insert(Node** head, uint16_t data)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;

    Node* walker = front;
    if(walker)
    {
        while (walker->next)
        {
            walker = walker->next;
        }
        walker->next = newNode;
            printf("Node inserted successfully! (%d)\n", newNode->data);
                nrOfNodes++;
    }
    else
    {
        front = newNode;
        *head = front;
            printf("Node inserted successfully! (%d)\n", newNode->data);
                nrOfNodes++;
    }
    *head = front;
}

void list_insert_after(Node* prev_node, uint16_t data)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;

    if(prev_node)
    {
        if (prev_node->next)
        {
            newNode->next = prev_node->next;
        }
        else
            newNode->next = NULL;
        prev_node->next = newNode;
        printf("Node inserted successfully after (%d)!", newNode->data);
        nrOfNodes++;
    }
    else
        printf("invalid prev_node");
}

void list_insert_before(Node** head, Node* next_to, uint16_t data)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = next_to;

    if(front == next_to)
        front = newNode;
    else
    {
        Node* walker = front;
        while(walker->next && walker->next != next_to)
        {
            walker = walker->next;
        }
        walker->next = newNode;
    }
    nrOfNodes++;
    printf("Node insterted succesfully before (%d)!", newNode->data);
    *head = front;
}

void list_delete(Node** head, uint16_t data)
{
    Node* toDel;

    printf("DELETE DATA: %d\n", data);

    if(nrOfNodes == 0)
        printf("No nodes to delete!\n");
    else if(front->data == data)
    {
        toDel = front;
        if(nrOfNodes > 1)
            front = front->next;
        else
            front = NULL;

        free(toDel);
        nrOfNodes--;
    }
    else
    {
        Node* walker = front;
        while(walker->next)
        {
            if(walker->next->data != data)
                walker = walker->next;
            printf("walker: %d\n", walker->data);
        }    

        if(walker->next)
        {
            if (walker->next->data == data)
            {
                toDel = walker->next;
                if (toDel->next)
                {
                    walker->next = toDel->next;
                }
                free(toDel);
                nrOfNodes--;
            }  
        }
    }
        *head = front;   
}

Node* list_search(Node** head, uint16_t data)
{
    Node* walker = front;

    while(walker->next && walker->data != data)
    {
        walker = walker->next;
    }

    if(walker->data == data)
        return *head = walker;
    return NULL;
}

void list_display(Node** head)
{
    printf("[");

    Node* walker = front;

    while(walker)
    {
        printf("%d", walker->data);
        if(walker->next)
            printf(", ");
        walker = walker->next;
    }

    printf("]\n");

    *head = front;
}

void list_display_range(Node** head, Node* start_node, Node* end_node)
{
    Node* from = start_node;
    Node* to = end_node;

    printf("From: %d  To: %d\n", from->data, to->data);
    if(!start_node)
        from = front;
    printf("from: %d", from->data);
    printf("[");

    while(from)
    {
        printf("%d", from->data);
        if(to)
            if(from != to)
                printf(", ");
        else
            if(from->next)
                printf(", ");
        from = from->next;
    }

    printf("]\n");


}

int list_count_nodes(Node** head)
{
    return nrOfNodes;
}

void list_cleanup(Node** head)
{
    Node* walker = front;

    while(walker)
    {
        Node* toDel = walker;
        walker = walker->next;

        //printf("Deleting: %d\n", toDel->data);
        free(toDel);
    }
    nrOfNodes = 0;
    front = NULL;
    *head = front;
}


// int main()
// {
//     return 0;
// }