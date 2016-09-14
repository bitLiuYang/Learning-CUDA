#include<iostream>

#define DIM 1000

__global__ void kernel(unsigned char *ptr)
{
	int x = blockIdx.x;
	int y = blockIdx.y;
	int offset = x + y*gridDim.x;
	float scale = 1.5;
	float jx = (float)scale*(DIM/2 - x)/(DIM);
	float jy = (float)scale*(DIM/2 - y)/(DIM);
	int juliaVal = julia(jx, jy);
	ptr[offset*4 + 0] = 255*juliaVal;
	ptr[offset*4 + 1] = 0;
	ptr[offset*4 + 2] = 0;
	ptr[offset*4 + 3] = 255;
}

__device__ void julia(float x, float y)
{
	cuComplex z(x,y);
	cuComplex c(-0.8,0.156);
	for(int i=0; i<200; i++)
	{
		z = z*z + c;
	}
	if(z.magnitude2 > 1000)
	{
		return 0;
	}
	
	return 1;	
}

struct cuComplex
{
	float r;
	float i;
	__device__ cuComplex(float a, float b):r(a),i(b){}
	__device__ float void magnitude2(void)
	{
		return r*r + i*i;
	}
	__device__ cuComplex operator*(const cuComplex &a)
	{
		return cuComplex(r*a.r-i*a.i, i*a.r+r*a.i);
	}

	__device__ cuComplex operator+(const cuComplex &a)
	{
		return cuComplex(r+a.r, i+a.i);	
	}
};

int main(void)
{
	CPUBitmap bitmap(DIM,DIM);
	unsigned char *dev_ptr;
	dim3 grid(DIM, DIM);
	
	HANDLE_ERROR(cudaMalloc((void**)&dev_ptr, bitmap.image_size()));
	kernel<<<grid, 1>>>(dev_ptr);
		
	HANDLE_ERROR(cudaMemCopy(dev_ptr, bitmap.get_ptr(), bitmap.image_size(), cudaMemcpyDeviceToHost));
	
	bitmap.display_and_exit();
	cudaFree(dev_ptr);

	return 0;
}