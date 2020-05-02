obj-m = cp210x.o
KDIR = /lib/modules/`uname -r`/kernel
SRCDIR = $(PWD)
# try this instead if you don't have PWD defined
# SRCDIR = $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))
all:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules
clean:
	$(MAKE) -C $(KDIR) M=$(SRCDIR) clean
