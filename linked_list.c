#include "linked_list.h"
#include <stdio.h>
#include "common_defs.h"

void list_init(Node** head)
{

}

void list_insert(Node** head, int data)
{

}

void list_insert_after(Node** prev_node, int data)
{

}

void list_insert_before(Node** head, Node* next_to, int data)
{

}

void list_delete(Node** head, int data)
{

}

Node* list_search(Node** head, int data)
{

}

void list_display(Node** head)
{

}

void list_display_range(Node** head, Node* start_node, Node* end_node)
{

}

int list_count_nodes(Node** head)
{

}

void list_cleanup(Node** head)
{
    mem_free(*head);
}