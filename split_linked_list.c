#include "split_linked_list.h"


/* Insert a key on the back of the linked list. */
void insert_node( NODE **n, int key)
{
    NODE *new_node  = (NODE *)kmalloc(sizeof(NODE), GFP_KERNEL);
    NODE *temp      = *n;
    NODE *temp_prev = temp->prev;

    new_node->next  = temp;
    new_node->key   = key;
    temp->prev      = new_node;

    // printk("[NODE key] %d\n", new_node->key);

    new_node->prev  = temp_prev;
    temp_prev->next = new_node;
}


/* Search nth node in the linked list. */
NODE* split_search(NODE* node, int n, int list_size)
{ 
    // bit operation: divide by 2 (median)
    int median = list_size >> 1;
    int i;

    /* move to next, if n is less than node median */
    if (n <= median) {
        // printk("next -> %d\n",n);
        for (i = 0; i < n; i++)
            node = node->next;
    }              
    /* move to prev, if n is greater than node median */
    else {
        // printk("prev <- %d\n",list_size-n);
        for (i = 0; i < list_size-n; i++)
            node = node->prev;
    }
    return node;
}


/* Display all nodes in the linked list. */
void display_node( NODE *n)
{   
    if (n == NULL) {
        return;
    }

    NODE *temp  = n->next;
    
    /* display all nodes along next. */
    printk(KERN_CONT "<Split-LL nodes>: [ ");
    while( temp != n) {
        printk(KERN_CONT "%d, ", temp->key);
        temp = temp->next;
    }
    printk(KERN_CONT "]\n");
}


/* Delete nth node from list head */
void delete_node_at(NODE* node, int n, int *list_size) {
    NODE* selected_node = node;    // node to delete. Initialized to the starting NODE.

    // if node is not in the list or n is incorrect
    if(node->next == node || n < 0 || (*list_size)-1 < n) {
        return;
    }
    if(n==0) {  /* when deleting the starting head node */
        selected_node = node;
        node->next->prev = node->prev;
        node->prev->next = node->next;
        node = node->next;
    }
    else {      /* deleting normal nodes */
        selected_node = split_search(node, n, *list_size);
        selected_node->prev->next = selected_node->next;
        selected_node->next->prev = selected_node->prev;
    }
    kfree(selected_node);
    (*list_size)--;
}



/*
// 리스트의 마지막 노드를 삭제하는 함수
void delete_last_node(NODE* node) {
    NODE* selectNode = node;

    // 리스트에 노드가 하나인 경우 함수를 종료
    if (node->next == node) return;

    // 리스트에 노드가 두개인 경우 
    else if(node->next == node->prev) {
        selectNode = node->next;
        node->next = node;
        node->prev = node;
    }
    // 리스트에 노드가 세개 이상인 경우
    else {
        selectNode = node->prev;
        node->prev = node->prev->prev;
        node->prev->next = node;
    }
    kfree(selectNode->key);
    kfree(selectNode);
}
*/
