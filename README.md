# sysfs mock

Simple kernel module that helps to mock /sys/firmware/devicetree/base/model  
This has been tested using QEMU and buildroot.  

## Build

If you want to build this you need to edit the Makefile to point to the correct kernel-headers.  
Then use ```make``` to build the kernel module.  

## Crosscompile

To build this you need to edit the Makefile to point to the kernel-headers in for example buildroot.  
Then edit the CROSS_COMPILE argument in the make (make sure the ARCH matches your target architecture).  
```sh
make CROSS_COMPILE=/home/dev/Desktop/buildroot-2022.11-rc1/output/host/bin/aarch64-buildroot-linux-gnu- ARCH=arm64
```

## Usage

```sh
insmod sysfs_mock.ko  
echo "desired_model_string" > /sys/firmware/devicetree/base/model  
cat /sys/firmware/devicetree/base/model  
```
