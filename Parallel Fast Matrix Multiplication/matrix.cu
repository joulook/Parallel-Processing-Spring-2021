#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <cuda.h>
#include <stdlib.h>
using namespace std;


__global__ void MatricesMultiply(float* x, float* y, float* z, int s) {

	int C = (blockIdx.x * blockDim.x) + threadIdx.x;
	int R = (blockIdx.y * blockDim.y) + threadIdx.y;
	
	if ((R<s) && (C<s)) {
		float result = 0;
		for (int i = 0; i < s; i++) {
			result += x[R * s + i] * y[i * s + C];
		}
		z[R * s + C] = result;
	}
}

int main(void) {
	int n = 6;
	float* a, * b, * c, * a_d, * b_d, * c_d;

	a = (float*)malloc(sizeof(float) * n * n);
	b = (float*)malloc(sizeof(float) * n * n);
	c = (float*)malloc(sizeof(float) * n * n);

	cudaSetDevice(0);

	cudaMalloc((void**)&a_d, sizeof(float) * n * n);
	cudaMalloc((void**)&b_d, sizeof(float) * n * n);
	cudaMalloc((void**)&c_d, sizeof(float) * n * n);

	for (int i = 0; i < n * n; i++) {
		a[i] = i;
		b[i] = i+1;
	}

	cudaMemcpy(a_d, a, sizeof(float) * n * n, cudaMemcpyHostToDevice);
	cudaMemcpy(b_d, b, sizeof(float) * n * n, cudaMemcpyHostToDevice);

	dim3 dimGrid(std::ceil(n/32.0), std::ceil(n/32.0), 1);
	dim3 dimBlock(32, 32, 1);
	MatricesMultiply <<<dimGrid, dimBlock>>>(a_d, b_d, c_d, n);
	cudaDeviceSynchronize();

	cudaMemcpy(c, c_d, sizeof(float) * n * n, cudaMemcpyDeviceToHost);

	cudaFree(a_d);
	cudaFree(b_d);
	cudaFree(c_d);

	printf("The Result is\n\n");
	int counter = 0;
	printf("\t | ");
	for (int i = 0; i < n*n; i++){
		if(counter == n){
			printf("\n");
			printf("\t | ");
			printf("%f\t", c[i]);
			counter = 1;
		}else{
			printf("%f\t", c[i]);
			counter++;
		}

	}
	printf("\n\n");

	return 0;
}

