#include "split_linked_list.h"


void print_time(void)
{
    __print_append();
    __print_insert();
    __print_traverse();
    __print_delete_at();
}


/* Print appending times */
void __print_append()
{
    printk("-------------------------------------------------\n");
    printk("%s: append_list_time: %llu, count: %llu\n", 
        __func__, append_list_time, append_list_count);
    printk("%s: append_kernel_list_time: %llu, count: %llu\n", 
        __func__, append_kernel_list_time, append_kernel_list_count);
}


/* Print times inserting specific node into the list */
void __print_insert()
{
    printk("-------------------------------------------------\n");
    printk("%s: insert_list_time: %llu, count: %llu\n", 
        __func__, insert_list_time, insert_list_count);
    printk("%s: insert_kernel_list_time: %llu, count: %llu\n", 
        __func__, insert_kernel_list_time, insert_kernel_list_count);
}


/* Print traversing times */
void __print_traverse()
{
    printk("-------------------------------------------------\n");
    printk("%s: traverse_list_time: %llu, count: %llu\n", 
        __func__, traverse_list_time, traverse_list_count);
    printk("%s: traverse_kernel_list_time: %llu, count: %llu\n", 
        __func__, traverse_kernel_list_time, traverse_kernel_list_count);
}


/* Print times deleting specific node in the list */
void __print_delete_at()
{
    printk("-------------------------------------------------\n");
    printk("%s: delete_at_list_time: %llu, count: %llu\n", 
        __func__, delete_at_list_time, delete_at_list_count);
    printk("%s: delete_at_kernel_list_time: %llu, count: %llu\n", 
        __func__, delete_at_kernel_list_time, delete_at_kernel_list_count);
}