obj-m		:= hello_module.o
KERNEL_DIR 	:= /lib/modules/$(shell uname -r)/build
PWD 		:= $(shell pwd)

default :
	$(MAKE) -C $(KERNEL_DIR) SUBDIRS=$(PWD) modules
clse :
	$(MAKE) -C $(KERNEL_DIR) SUBDIRS=$(PWD) clean
