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
    printf("Node inserted successfully! (%d)\n", newNode->data);
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
        printf("Node inserted successfully after (%d)!", newNode->data);
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
        printf("toDel%d", toDel->data);
        if(toDel->next)
            *head = toDel->next;
        mem_free(*head);
        free(*head);
        *head = NULL;
    }
    else
    {
        Node* walker = *head;

        while(walker->next->data != data)
            walker = walker->next;
        toDel = walker->next;

        if(toDel->next)
            walker->next = toDel->next;
        else
            walker->next = NULL;

        printf("node%d", toDel->data);
        mem_free(toDel);
    }

    //printf("DELETE DATA: %d\n", data);

    // if(nrOfNodes == 0)
    //     printf("No nodes to delete!\n");
    // else if((*head)->data == data)
    // {
    //     toDel = *head;
    //     if(nrOfNodes > 1)
    //         *head = (*head)->next;
    //     else
    //         *head = NULL;

    //     mem_free(toDel);
    //     nrOfNodes--;
    // }
    // else
    // {
    //     Node* walker = *head;
    //     while(walker->next)
    //     {
    //         if(walker->next->data != data)
    //             walker = walker->next;
    //         //printf("walker: %d\n", walker->data);
    //     }    

    //     if(walker->next)
    //     {
    //         if (walker->next->data == data)
    //         {
    //             toDel = walker->next;
    //             if (toDel->next)
    //             {
    //                 walker->next = toDel->next;
    //             }
    //             mem_free(toDel);
    //             nrOfNodes--;
    //         }  
    //     }
    // }
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
    printf("[");

    Node* walker = *head;

    while(walker)
    {
        printf("%d", walker->data);
        if(walker->next)
            printf(", ");
        walker = walker->next;
    }

    printf("]\n");

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

        printf("from: %d", from->data);
        printf("[");

        while(from)
        {
            printf("%d",from->data);

            if(from->next)
            {
                if (from->next != to)
                    printf(", ");
                if(to)
                    if(from == to)
                        from->next = NULL;
                from = from->next;
            }
        }
        

        // while(from)
        // {
        //     printf("%d", from->data);
        //     if(to)
        //         if(from != to)
        //             printf(", ");
        //     else
        //         if(from->next)
        //             printf(", ");
        //     from = from->next;
        // }
        printf("]\n");
    }
}

int list_count_nodes(Node** head)
{
    return nrOfNodes;
}

void list_cleanup(Node** head)
{
    if(*head == NULL)
        mem_deinit(*head);
    else
    {
        Node* walker = *head;

        while (walker)
        {
            Node* next = walker->next;
            list_delete(walker, walker->data);
            walker = next;
        }
    }
    mem_deinit(*head);
    nrOfNodes = 0;
    *head = NULL;
    
    // Node* walker = *head;

    // while(walker)
    // {
    //     Node* toDel = walker;
    //     walker = walker->next;

    //     //printf("Deleting: %d\n", toDel->data);
    //     mem_free(toDel);
    // }
    // nrOfNodes = 0;
    // mem_free(*head);
    // *head = NULL;

}


// int main()
// {
//     return 0;
// }