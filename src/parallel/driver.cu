#include "driver.h"
#include <iostream>
#include <stdio.h>
namespace mincut {
  __global__ void reduce(float *d_slinks, float *d_capacity, float *d_flow, int i, int xsize, int ysize) {
    // Find paths of length i and remove bottleneck
    int x = blockDim.x * blockIdx.x + threadIdx.x;
    int y = blockDim.y * blockIdx.y + threadIdx.y;

    int xboundmin = blockDim.x * blockIdx.x;
    int xboundmax = blockDim.x * (blockIdx.x + 1) - 1;
    int yboundmin = blockDim.y * blockIdx.y;
    int yboundmax = blockDim.y * (blockIdx.y + 1) - 1;

    int index = x * ysize + y;
    if (i == 1) {
      int s_weight = d_slinks[index];
      int t_weight = d_capacity[5*index + 4];
      if (s_weight > t_weight) {
	d_capacity[5*index + 4] = 0;
	d_slinks[index] -= t_weight;
      } else {
	d_capacity[5*index + 4] -= s_weight;
	d_slinks[index] = 0;
      }
    }
    if (i == 2) {
      float weights[4];
      int next_pos[2];
      int tempindex = index;
      weights[0] = d_slinks[index];
      char offsets[][8] = { {D,L}, {D,R}, {U,L}, {U,R}, {R, U}, {R, D}, {L, D}, {L, U} };
      for (int j = 0; j < 8; j++) {
	char mincappos = 0;
	for (int k = 1; k < 3; k++) {
	  if (offsets[j][k-1] == D) {
	    next_pos[k-1] = index + ysize;
	  } else if (offsets[j][k-1] == L) {
	    next_pos[k-1] = index - xsize;
	  } else if (offsets[j][k-1] == R) {
	    next_pos[k-1] = index + xsize;
	  } else if (offsets[j][k-1] == U) {
	    next_pos[k-1] = index - ysize;
	  }
	  weights[k] = d_capacity[5*index + offsets[j][k-1]] - d_flow[5*index + offsets[j][k-1]];
	  if (weights[k] < 0) {
	    weights[k] = 0;
	  }
	  if (weights[k] < weights[mincappos]) {
	    mincappos = k;
	  }
	  index = next_pos[k-1];
	}
	weights[3] = d_capacity[5*index + 4] - d_flow[5*index + 4];
	bool good = true;
	
	for (int i = 0; i < 2; i++){
	  
	}
      }
    }

    return;
  }

  float mincut (Graph *g) {

    float *d_slinks, *d_capacity, *d_flow;

    cudaMalloc((void **) &d_capacity,5*IMAGE_SIZE*FLOAT_SIZE);
    cudaMalloc((void **) &d_flow,5*IMAGE_SIZE *FLOAT_SIZE);
    cudaMalloc((void **) &d_slinks,IMAGE_SIZE * FLOAT_SIZE);

    cudaMemcpy(d_capacity,g->m_capacity,5*IMAGE_SIZE*FLOAT_SIZE,cudaMemcpyHostToDevice);
    cudaMemcpy(d_flow,g->m_flow,5*IMAGE_SIZE*FLOAT_SIZE,cudaMemcpyHostToDevice);
    cudaMemcpy(d_slinks,g->m_slinks,IMAGE_SIZE * FLOAT_SIZE,cudaMemcpyHostToDevice);

    cudaEvent_t seq_start_event, seq_stop_event;
    cudaEventCreate(&seq_start_event);
    cudaEventCreate(&seq_stop_event);
    cudaEventRecord(seq_start_event, 0);


    for (int i = 0; i < 2; i++) {
      reduce<<<dim3(20,20),dim3(10,10)>>> (d_capacity, d_flow, d_slinks, i, g->x, g->y);
    }

    cudaEventRecord(seq_stop_event, 0);
    cudaEventSynchronize(seq_stop_event);

    cudaDeviceSynchronize();
    float seq_time= 0;
    cudaEventElapsedTime(&seq_time, seq_start_event, seq_stop_event);
    std::cout << "Time taken for reduce :" << seq_time << std::endl;
    return 0.0f;

  }


}
