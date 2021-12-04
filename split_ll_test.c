#include "split_linked_list.h"


void split_ll_example(int size)
{   
    NODE *H = __init_list();
    __append_list(H, size);
    __insert_list(-7777, size * 4/5, H, &size);
    __traverse_list(H);
    __delete_list(size * 4/5, H, &size);

    printk("After node deletion " );
    display_node(H);

    __clear_list(H, &size);
}


/* Initialize the starting node. */
NODE* __init_list()
{
    NODE *head_node = (NODE *)kmalloc(sizeof(NODE), GFP_KERNEL);
    head_node->key  = NULL;
    head_node->next = head_node;
    head_node->prev = head_node;
    return head_node;
}


/* Append nodes to the list sequentially */
void __append_list(NODE *_node, int size)
{
    int i;
    for (i = 0; i < size; i++) {    
        ktime_get_ts64(&spclock[0]);
        insert_node(&_node, i);
        ktime_get_ts64(&spclock[1]);
        calclock3(spclock, &append_list_time, &append_list_count);
    }
}


/* Insert node at certain point of the list */
void __insert_list(int key, int position, NODE *_node, int *size)
{
	ktime_get_ts64(&spclock[0]);
    NODE* insert_point = split_search(_node, position, *size);
   	insert_node( &insert_point, key);
    (*size)++;
	ktime_get_ts64(&spclock[1]);
	calclock3(spclock, &insert_list_time, &insert_list_count);
}


/* Traverse all the nodes in the list */
void __traverse_list(NODE *_node)
{
	ktime_get_ts64(&spclock[0]);
    display_node(_node);
	ktime_get_ts64(&spclock[1]);
	calclock3(spclock, &traverse_list_time, &traverse_list_count);
}


/* Delete specific node */
void __delete_list(int position, NODE *_node, int *size)
{
	ktime_get_ts64(&spclock[0]);
    delete_node_at(_node, position, size);
	ktime_get_ts64(&spclock[1]);
	calclock3(spclock, &delete_at_list_time, &delete_at_list_count);
}


/* Delete every nodes and clear the list. */
void __clear_list(NODE *_head, int *size)
{
    if (_head == NULL) {
        return;
    }
    NODE *temp, *cursor = _head->next;

    while( cursor != _head) {
        temp = cursor->next;
        delete_node_at(cursor, 0, size);
        cursor = temp;
    }
    if (_head != NULL)
        kfree(_head);
}


unsigned long long append_list_time = 0;
unsigned long long append_list_count = 0;

unsigned long long insert_list_time = 0;
unsigned long long insert_list_count = 0;

unsigned long long traverse_list_time = 0;
unsigned long long traverse_list_count = 0;

unsigned long long delete_at_list_time = 0;
unsigned long long delete_at_list_count = 0;