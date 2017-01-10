#pragma OPENCL EXTENSION cl_khr_icd : enable
__kernel void add_vector(__global float *a, __global float *b,
        __global float *c, const unsigned int n)
{
    int id = get_global_id(0);
    if (id < n)
        c[id] = a[id] + b[id];
}




