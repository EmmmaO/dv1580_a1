#include "linked_list.h"
#include <stdio.h>
#include "common_defs.h"

//Node* front = NULL;
size_t nrOfNodes = 0;

void list_init(Node** head, size_t size)
{
    mem_init(size);
    *head = NULL;
    printf("List initialized successfully!\n");
}

void list_insert(Node** head, uint16_t data)
{
    Node* newNode = mem_alloc(sizeof(Node));//(Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;

    Node* walker = *head;
    if(walker)
    {
        while (walker->next)
        {
            walker = walker->next;
        }
        walker->next = newNode;
            //printf("Node inserted successfully! (%d)\n", newNode->data);
                nrOfNodes++;
    }
    else
    {
        *head = newNode;
            //printf("Node inserted successfully! (%d)\n", newNode->data);
                nrOfNodes++;
    }
    printf("Node inserted successfully!\n");
}

void list_insert_after(Node* prev_node, uint16_t data)
{
    Node* newNode = mem_alloc(sizeof(Node));//(Node*)malloc(sizeof(Node));
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
        printf("Node inserted successfully!");
        nrOfNodes++;
    }
    else
        printf("invalid prev_node");
}

void list_insert_before(Node** head, Node* next_to, uint16_t data)
{
    Node* newNode = mem_alloc(sizeof(Node));//(Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = next_to;

    if(*head == next_to)
    {
        *head = newNode;
        newNode->next = next_to;   
    }
    else
    {
        Node* walker = *head;
        while(walker->next && walker->next != next_to)
        {
            walker = walker->next;
        }
        walker->next = newNode;
    }
    nrOfNodes++;
    //printf("Node insterted succesfully before (%d)!", newNode->data);
}

void list_delete(Node** head, uint16_t data)
{
    Node* toDel = *head;
    if(nrOfNodes == 0)
        printf("No nodes to delete!");
    
    else if(toDel->data == data)
    {
        if(toDel->next)
            *head = toDel->next;
        else
            *head = NULL;
        mem_free(toDel);
    }
    else
    {
        Node* walker = *head;

        while(walker->next)
            if(walker->next->data == data)
                break;
            walker = walker->next;
        toDel = walker->next;

        if(toDel->next)
            walker->next = toDel->next;
        else
            walker->next = NULL;

        mem_free(toDel);
    }
}

Node* list_search(Node** head, uint16_t data)
{
    Node* walker = *head;

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
    Node* walker = *head;

    printf("[");
    while(walker)
    {
        printf("%d", walker->data);
        if(walker->next)
            printf(", ");
        walker = walker->next;
    }
    printf("]");
}

void list_display_range(Node** head, Node* start_node, Node* end_node)
{
    if(!start_node && !end_node)
        list_display(head);
    else
    {
        Node* from = start_node;
        Node* to = end_node;

        if(!start_node)
            from = *head;

        printf("[");
        while(from)
        {
            printf("%d",from->data);
            if(from == to)
                break;   
            from = from->next;
            if(from)
                printf(", ");
        }
        printf("]");
    }
}

int list_count_nodes(Node** head)
{
    return nrOfNodes;
}

void list_cleanup(Node** head)
{
    if(*head == NULL)
        return;
    else
    {
        Node* walker = *head;

        while (walker)
        {
            Node* next = walker->next;
            
            mem_free(walker);
            walker = next;
        }
    }
    mem_deinit(*head);
    nrOfNodes = 0;
    *head = NULL;
}


// int main()
// {
//     return 0;
// }
