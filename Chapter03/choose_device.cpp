#include<iostream>

/*在所有可用的设备中，寻找对应属性的设备*/
int main(void)
{
	cudaDeviceProp prop;
	int dev;
	
	HANDLE_ERROR(cudaGetDevice(&dev));
	printf("ID of current device is : %d\n", dev);
	
	memcpy(&prop, 0, sizeof(cudaDeviceProp));
	prop.major = 1;
	prop.minor = 3;
	HANDLE_ERROR(cudaChooseDevice(&dev, %prop));
	printf("ID of CUDA device closet to revision 1.3: %d\n", dev);
	HANDLE_ERROR(cudaSetDevice(dev));
}