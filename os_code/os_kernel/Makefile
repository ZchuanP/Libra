#makefile

obj-m += hellomod.o
 
# $(shell uname -r)用来获取当前的内核版本号
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
# clean用于清除当前文件夹中所有的内核模块相关文件
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
