// #---------- splitted_ll_module-base.c -----------#
#include "split_linked_list.h"

static int size = 0;
struct timespec64 spclock[2];

module_param(size, int, 0);

int __init split_ll_module_init(void)
{	
	printk(KERN_EMERG "Split Linked-List Module started!\n");

	split_ll_example(size);
	kernel_ll_example(size);

	print_time();
	return 0;
}



void __exit split_ll_module_cleanup(void)
{
	printk("Split Linked-List Module exited!\n");
}

module_init(split_ll_module_init);
module_exit(split_ll_module_cleanup);

MODULE_LICENSE("GPL");