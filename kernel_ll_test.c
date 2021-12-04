#include "split_linked_list.h"

void kernel_ll_example(int size)
{   
    struct list_head my_list;

    struct list_head head = __init_kernel_list(&my_list);
    __append_kernel_list(&my_list, size);
    __insert_kernel_list(-7777, size * 4/5, &my_list);
    __traverse_kernel_list(&my_list, TRUE);
    __delete_kernel_list(-7777, &my_list, &head);

    printk("After node deletion " );
    __traverse_kernel_list(&my_list, FALSE);
}


/* Initialize list */
struct list_head __init_kernel_list(struct list_head *_list)
{
    INIT_LIST_HEAD(_list);

    return *_list;
}


/* Append list element */
void __append_kernel_list(struct list_head *_list, int size)
{
    int i;
    for (i = 0; i < size; i++) {
        ktime_get_ts64(&spclock[0]);
        struct my_node *new = kmalloc(sizeof(struct my_node), GFP_KERNEL);
        new->data = i;
        list_add(&new->list, _list);
        ktime_get_ts64(&spclock[1]);
        calclock3(spclock, &append_kernel_list_time, &append_kernel_list_count);
    }
}


/* Insert new node at position which has key */
void __insert_kernel_list(int key, int position_data, struct list_head *_list)
{
    struct my_node *current_node;  /* This will point on the actual data structures during the iteration */
    ktime_get_ts64(&spclock[0]);
    list_for_each_entry_reverse(current_node, _list, list) {
        if (current_node->data == position_data)
            break;
    }
    struct my_node *new = kmalloc(sizeof(struct my_node), GFP_KERNEL);
    new->data = key;
    list_add(&new->list, &current_node->list);
    ktime_get_ts64(&spclock[1]);
    calclock3(spclock, &insert_kernel_list_time, &insert_kernel_list_count);
}


/* Display all nodes in the list */
void __traverse_kernel_list(struct list_head *_list, unsigned short is_timer)
{
    struct my_node *current_node;  /* This will point on the actual data structures during the iteration */
    ktime_get_ts64(&spclock[0]);
    printk(KERN_CONT "<Kernel-LL nodes>: [ ");
    list_for_each_entry_reverse(current_node, _list, list) {
        printk(KERN_CONT "%d, ", current_node->data);
    }
    printk(KERN_CONT "]\n");
    ktime_get_ts64(&spclock[1]);
    if (is_timer)
        calclock3(spclock, &traverse_kernel_list_time, &traverse_kernel_list_count);

}


/* Delete list node which has key */
void __delete_kernel_list(int key, struct list_head *_list, struct list_head *_head)
{
    struct my_node *current_node;  /* This will point on the actual data structures during the iteration */
    struct my_node *tmp;

    list_safe_reset_next(current_node, tmp, list);

    ktime_get_ts64(&spclock[0]);
    list_for_each_entry_safe(current_node, tmp, _list, list) {
        if (current_node->data == key) {
            // printk("current node value : %d\n", current_node->data);
            list_del(&current_node->list);
            kfree(current_node);
            break;
        }
    }
    ktime_get_ts64(&spclock[1]);
    calclock3(spclock, &delete_at_kernel_list_time, &delete_at_kernel_list_count);
}


unsigned long long append_kernel_list_time = 0;
unsigned long long append_kernel_list_count = 0;

unsigned long long insert_kernel_list_time = 0;
unsigned long long insert_kernel_list_count = 0;

unsigned long long traverse_kernel_list_time = 0;
unsigned long long traverse_kernel_list_count = 0;

unsigned long long delete_at_kernel_list_time = 0;
unsigned long long delete_at_kernel_list_count = 0;
