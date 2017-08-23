#include <thrust/scan.h>
#include <thrust/device_ptr.h>
#include <hip/hip_runtime.h>
#include<iostream>

int main() {
  int data[10] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
  int keys[10] = {0, 0, 0, 1, 1, 2, 3, 3, 3, 3};
  int result[10];

  int* ddata, *dkeys, *dresult;
  hipMalloc(&ddata, sizeof(int) * 10);
  hipMalloc(&dkeys, sizeof(int) * 10);
  hipMalloc(&dresult, sizeof(int) * 10);
  hipMemcpy(ddata, data, sizeof(int) * 10, hipMemcpyHostToDevice);
  hipMemcpy(dkeys, keys, sizeof(int) * 10, hipMemcpyHostToDevice);
  thrust::device_ptr<int> data_(ddata);
  thrust::device_ptr<int> keys_(dkeys);
  thrust::device_ptr<int> result_(dresult);
  thrust::inclusive_scan_by_key(keys_, keys_ + 10, data_, result_);
  hipMemcpy(result, dresult, sizeof(int) * 10, hipMemcpyDeviceToHost);
  for (int i=0; i < 10; i++) {
    printf("%d ",result[i]);
  }
}

