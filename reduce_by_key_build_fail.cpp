#include <thrust/reduce.h>
#include <thrust/execution_policy.h>
#include <thrust/device_vector.h>
#include <thrust/device_ptr.h>
#include <thrust/inner_product.h>
#include<iostream>
#include <hip/hip_runtime.h>

int main () {
  thrust::device_vector<int> iter(10);
  thrust::device_vector<int> keys(10);
  thrust::device_vector<int> counts(10);
  thrust::not_equal_to<int> binary_pred;
  thrust::reduce_by_key(thrust::device, iter.begin(), iter.end(), thrust::constant_iterator<int>(1), keys.begin(), counts.begin(), binary_pred);
}

