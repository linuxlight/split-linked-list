obj-m := split_ll_module.o

split_ll_module-y	:= split_ll_module-base.o split_linked_list.o calclock3.o printer.o\
							split_ll_test.o kernel_ll_test.o

KERNEL_DIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

default : 
	$(MAKE) -C $(KERNEL_DIR) M=$(PWD) modules
clean :
	$(MAKE) -C $(KERNEL_DIR) M=$(PWD) clean
