obj-m +=sysfs_mock.o
all:
	make -C /home/dev/Desktop/buildroot-2022.11-rc1/output/build/linux-5.15.18 M=$(PWD) modules

clean:
	make -C /home/dev/Desktop/buildroot-2022.11-rc1/output/build/linux-5.15.18 M=$(PWD) clean
