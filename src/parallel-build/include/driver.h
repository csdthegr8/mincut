#ifndef MINCUT_GPU_H

#define MINCUT_GPU_H
#include <cuda.h>

#define THREADS_PER_BLOCK 512
#define ARRAY_SIZE sz*sizeof(float)

#define IMAGE_SIZE this->x * this->y
#define FLOAT_SIZE sizeof(float)
namespace mincut {
class GPUGraph;
}
#endif
