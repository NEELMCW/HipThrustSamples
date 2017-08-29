#include <thrust/sort.h>
#include <thrust/device_ptr.h>
#include <thrust/functional.h>
#include <thrust/execution_policy.h>
#include <hip/hip_runtime.h>
#include<iostream>

int main () {
  const int N = 6;
  int    keys[N] = {  1,   4,   2,   8,   5,   7};
  char values[N] = {'a', 'b', 'c', 'd', 'e', 'f'};

  int* devKeys, *hostKeys;
  char* devValues, *hostValues;

  // allocations
  hostKeys = (int *) malloc(sizeof(int) * 6);
  hostValues = (char *) malloc(sizeof(char) * 6);
  hipMalloc(&devKeys, sizeof(int) * 6);
  hipMalloc(&devValues, sizeof(char) * 6);

  // Copy input to device
  hipMemcpy(devKeys, keys, sizeof(int) * 6, hipMemcpyHostToDevice);
  hipMemcpy(devValues, values, sizeof(char) * 6, hipMemcpyHostToDevice);

  thrust::device_ptr<int> Keys_(devKeys);
  thrust::device_ptr<char> Values_(devValues);
  thrust::stable_sort_by_key(thrust::device, Keys_, Keys_ + N, Values_, thrust::greater<int>());

  // Copy results back to host
  hipMemcpy(hostKeys, devKeys, sizeof(int) * 6, hipMemcpyDeviceToHost);
  hipMemcpy(hostValues, devValues, sizeof(char) * 6, hipMemcpyDeviceToHost);

  printf("\n Keys after sorting: \n");
  for (int i = 0; i < 6; i++) {
    printf("%d \t", hostKeys[i]);
  }
  printf("\n Values after sorting: \n");
  for (int i = 0; i < 6; i++) {
    printf("%c \t", hostValues[i]);
  }
  // keys is now   {  8,   7,   5,   4,   2,   1}
  // values is now {'d', 'f', 'e', 'b', 'c', 'a'}

  // Free up resources
  hipFree(devKeys);
  hipFree(devValues);
  free(hostKeys);
  free(hostValues);
}

