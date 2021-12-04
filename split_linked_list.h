#ifndef _SPLIT_LINKED_LIST_H
#define _SPLIT_LINKED_LIST_H

#include <linux/kernel.h>  // Needed by all modules
#include <linux/module.h>  // Needed for KERN_ALERT
#include <linux/moduleparam.h>
#include <linux/init.h>    // Needed for the macros
#include <linux/list.h>
#include <linux/slab.h>    // for kmalloc
#include <linux/ktime.h>
#include <linux/timekeeping.h>

#define TRUE 1
#define FALSE 0

typedef struct node {   /* list node using our defined data structure */
    int key;
    struct node *prev;  // pointer pointing to previous NODE
    struct node *next;  // pointer pointing to next NODE
} NODE;


struct my_node {        /* list node using kernel data structure */
    struct list_head list;
    int data;
};

/* Kernel timer to measure performance */
unsigned long long calclock3(
    struct timespec64 *, 
    unsigned long long *, 
    unsigned long long *
    );

extern struct timespec64 spclock[2];

extern unsigned long long append_list_time;
extern unsigned long long append_list_count;
extern unsigned long long append_kernel_list_time;
extern unsigned long long append_kernel_list_count;

extern unsigned long long insert_list_time;
extern unsigned long long insert_list_count;
extern unsigned long long insert_kernel_list_time;
extern unsigned long long insert_kernel_list_count;

extern unsigned long long traverse_list_time;
extern unsigned long long traverse_list_count;
extern unsigned long long traverse_kernel_list_time;
extern unsigned long long traverse_kernel_list_count;

extern unsigned long long delete_at_list_time;
extern unsigned long long delete_at_list_count;
extern unsigned long long delete_at_kernel_list_time;
extern unsigned long long delete_at_kernel_list_count;


/* Split Linked-List functions */
void insert_node(NODE **, int);
NODE* split_search(NODE *, int, int);
void display_node(NODE *);
void delete_node_at(NODE *, int, int *);

/* Test example functions */
void split_ll_example(int);
void kernel_ll_example(int);
NODE* __init_list(void);
struct list_head __init_kernel_list(struct list_head *);
void __append_list(NODE *, int);
void __append_kernel_list(struct list_head *, int);
void __insert_list(int, int, NODE *, int *);
void __insert_kernel_list(int, int, struct list_head *);
void __traverse_list(NODE *);
void __traverse_kernel_list(struct list_head *, unsigned short);
void __delete_list(int, NODE *, int *);
void __clear_list(NODE *, int *);
void __delete_kernel_list(int, struct list_head *, struct list_head *);

/* Printer functions */
void print_time(void);
void __print_append(void);
void __print_insert(void);
void __print_traverse(void);
void __print_delete_at(void);


#endif /* _SPLIT_LINKED_LIST_H */