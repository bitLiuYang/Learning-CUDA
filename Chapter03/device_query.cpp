#include<iostream>


int main(void)
{
	cudaDeviceProp prop;
	int count;
	
	HANDLE_ERROR(cudaGetDeviceCount(&count));
	for(int i=0; i<count; i++)
	{
		HANDLE_ERROR(cudaGetDeviceProperties(&prop, i));
		printf("---------device : %d---------\n", i);
		printf("name:\n", prop.name);
		printf("Compute capability :%d.%d\n", prop.major, prop.minor);
		printf("Clock Rate :%d\n", prop.clockRate);
		printf("Device copy overlap :");
		if(prop.deviceOverlap)
		{
			printf("Enabled !\n");
		}
		else
		{
			printf("Disabled !\n");
		}
		//...
	}
	
	return 0;
}