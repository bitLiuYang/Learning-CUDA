#include<iostream>

__global__ void add(int a, int b, int *c)
{
	*c = a + b;
}
/*
	在host中定义一个指针，然后将这个指针的地址传递给device，在device中进行内存分配。
	在device中，进行运算，结果可以保存在这个指针中。
	通过cudaMemcpy函数将结果拷贝出来，供host中函数使用。
	通过cudaFree，来释放这个指针。
	总结起来：主机指针只能访问主机代码中的内存，设备指针也只能访问设备代码中的内存
	cudaMemcpyDeviceToHost， cudaMemcpyHostToDevice， cudaMemcpyDeviceToDevice
*/
int main(void)
{
	int c;
	int *dev_c;
	//把dev_c这个指针变量的地址更改了，可是&dev_v不是编译后，就确定了的常量么...
	HANDLE_ERROR(cudaMalloc((void**)&dev_c, sizeof(int)));
	add<<1,1>>(2,7,dev_c);
	HANDLE_ERROR( cudaMemcpy(&c, dev_c, sizeof(int), cudaMemcpyDeviceToHost) );
	printf("2+7 = %d\n", c);
	cudaFree(dev_c);
	return 0;
}