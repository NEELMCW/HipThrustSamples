#include <thrust/transform.h>
#include <thrust/functional.h>
#include <thrust/execution_policy.h>
#include <thrust/device_ptr.h>
#include <hip/hip_runtime.h>
#include<iostream>

int main () {
  const int N = 10;
  int input1[N];
  int input2[N];
  int output[N];
  thrust::plus<int> op;

  // Populate input
  for(int i=0; i < N; i++) {
    input1[i] = i;
    input2[i] = 2*i;
  }

  int* devIn1, *devIn2, *devOut;
  int* hostOut = (int*) malloc(sizeof(int) * N);
  hipMalloc(&devIn1, sizeof(int) * N);
  hipMalloc(&devIn2, sizeof(int) * N);
  hipMalloc(&devOut, sizeof(int) * N);

  hipMemcpy(devIn1, input1, sizeof(int) * N, hipMemcpyHostToDevice);
  hipMemcpy(devIn2, input2, sizeof(int) * N, hipMemcpyHostToDevice);
  hipMemcpy(devOut, output, sizeof(int) * N, hipMemcpyHostToDevice);

  thrust::device_ptr<int> in1Data(devIn1);
  thrust::device_ptr<int> in2Data(devIn2);
  thrust::device_ptr<int> outData(devOut);
  thrust::transform(in1Data, in1Data + N, in2Data, outData, op);
  hipMemcpy(hostOut, devOut, sizeof(int) * N, hipMemcpyDeviceToHost);
  for(int i=0; i < N; i++) {
    printf("%d ",hostOut[i]);
  }


  // Free up resources
  hipFree(devIn1);
  hipFree(devIn2);
  hipFree(devOut);
  free(hostOut);
  printf("Done\n");
}

