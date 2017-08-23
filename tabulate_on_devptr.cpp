#include <thrust/tabulate.h>
#include <thrust/functional.h>
#include <thrust/device_ptr.h>
#include <iostream>
#include <hip/hip_runtime.h>

int main() {
  const int N = 10;
  int A[N];
  // Create device pointers
  int* devData;
  int * hostData = (int*) malloc(sizeof(int)*N);
  hipMalloc(&devData, sizeof(int) * N);
  hipMemcpy(devData, A, sizeof(int) * N, hipMemcpyHostToDevice);
  thrust::device_ptr<int> data_(devData);
  thrust::tabulate(data_, data_ + 10, thrust::negate<int>());
  hipMemcpy(hostData, devData, sizeof(int) * N, hipMemcpyDeviceToHost);
  for(int i=0; i < 10; i++) {
    if(hostData[i] != -i) {
      printf("Test failed with mismatch at index %d\n", i);
      break;
    }
  }

  // Free up resources
  hipFree(devData);
  free(hostData);
  printf("Done\n");
}
~    
