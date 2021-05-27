obj-m:=car.o

KERNELDIR:=/home/incipe/expend/6818GEC/kernel
CROSS_COMPILE:=/home/incipe/expend/6818GEC/prebuilts/gcc/linux-x86/arm/arm-eabi-4.8/bin/arm-eabi-

PWD:=$(shell pwd)

default:
	$(MAKE) ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE) -C $(KERNELDIR) M=$(PWD) modules

clean:
	rm -rf *.o *.order .*.cmd *.ko *.mod.c *.symvers *.tmp_versions
