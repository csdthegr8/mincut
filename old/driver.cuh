#ifndef MINCUT_GPU_H

#define MINCUT_GPU_H
#include <cuda.h>
#include <cuda_runtime_api.h>

#include "graph.h"

#define THREADS_PER_BLOCK 512
#define ARRAY_SIZE sz*sizeof(float)

#define IMAGE_SIZE this->x * this->y
#define FLOAT_SIZE sizeof(float)
namespace mincut {

class GPUGraph {

public:
    GPUGraph() {}

    float *m_pixelData;
    unsigned int x,y,z;

    GPUGraph(Graph *g) {
        this->x = g->x;
        this->y = g->y;
        this->g = g;
    }

    float *d_capacity;
    float *d_flow;
    float *d_slinks;

    __host__ float mincut(ALGORITHM type, bool verbose=false) {
        // Copy data to device

        cudaMalloc((void **) &d_capacity,5*IMAGE_SIZE*FLOAT_SIZE);
        cudaMalloc((void **) &d_flow,5*IMAGE_SIZE *FLOAT_SIZE);
        cudaMalloc((void **) &d_slinks,IMAGE_SIZE * FLOAT_SIZE);

        cudaMemcpy(d_capacity,g->m_capacity,5*IMAGE_SIZE*FLOAT_SIZE,cudaMemcpyHostToDevice);
        cudaMemcpy(d_flow,g->m_flow,5*IMAGE_SIZE*FLOAT_SIZE,cudaMemcpyHostToDevice);
        cudaMemcpy(d_slinks,g->m_slinks,IMAGE_SIZE * FLOAT_SIZE,cudaMemcpyHostToDevice);

        reduce<<<dim3(20,20),dim3(10,10)>>> (d_capacity, d_flow, d_slinks);



    }

    __device__ void reduce(float *capacity, float *flow, float *slinks) {

    }

    __device__ void bfs() {
    }

    inline int getUnvisitedNeighbor( bool *visited, int &pos, bool checkcapacity);

    //bool findPath(vec2 *end, int *pred, bool **visited, vec2 &size);
    int findPath(int *pred, bool *visited, vec2 &size);
    void writeSegmentedImage(std::string filename);
    void bfs(int start, bool *visited);
    void mergeGraphs(Graph *otherGraph, int nx, int ny);
    void recomputeAdjacency();
    Graph *g;


};

}
#endif
