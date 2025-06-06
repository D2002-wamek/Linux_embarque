obj-m:=module_simple.o
KERNEL_SOURCE=/lib/modules/$(shell uname -r)/build

CFLAGS_MODULE := -fno-pic

all:
	make -C $(KERNEL_SOURCE) M=$(PWD) ARCH=arm CROSS_COMPILE=/usr/bin/arm-linux-gnueabihf- modules

clean:
	make -C $(KERNEL_SOURCE) M=$(PWD) ARCH=arm CROSS_COMPILE=/usr/bin/arm-linux-gnueabihf- clean

install:
	make -C $(KERNEL_SOURCE) M=$(PWD) ARCH=arm CROSS_COMPILE=/usr/bin/arm-linux-gnueabihf- install