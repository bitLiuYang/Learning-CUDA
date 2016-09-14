#include<iostream>

__global__ void add(int *a, int *b, int *c)
{
	int tid = blockIdx.x;
	if(tid<N)
		c[tid] = a[tid] + b[tid];
}

int main(void)
{
	int a[N], b[N], c[N];
	int *dev_a, *dev_b, *dev_c;
	for(int i=0; i<N; i++)
	{
		a[i] = 2*i;
		b[i] = i*i;
		c[i] = 0;		
	}
	
	HANDLE_ERROR(cudaMalloc((void**)&dev_a, N*sizeof(int)));
	HANDLE_ERROR(cudaMalloc((void**)&dev_b, N*sizeof(int)));
	HANDLE_ERROR(cudaMalloc((void**)&dev_c, N*sizeof(int)));
	
	HANDLE_ERROR(cudaMemCopy(dev_a, a, N*sizeof(int), cudaMemcpyHostToDevice));
	HANDLE_ERROR(cudaMemCopy(dev_b, b, N*sizeof(int), cudaMemCpyHostToDevice));
	
	add<<N,1>>(dev_a, dev_b, dev_c); //将会并行的调用add函数N次
	
	HANDLE_ERROR( cudaMemcpy(&c, dev_c, N*sizeof(int), cudaMemcpyDeviceToHost) );
	for(int -i=0; i<N; i++)
	{
		printf("%d\t", c[i]);
	}
	cudaFree(dev_a);
	cudaFree(dev_b);
	cudaFree(dev_c);
	return 0;
}