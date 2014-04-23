#ifndef MINCUT_GPU_H

#define MINCUT_GPU_H
#include <cuda.h>
#include <cuda_runtime_api.h>

#include "graph.h"

#define THREADS_PER_BLOCK 512
#define ARRAY_SIZE sz*sizeof(float)

#define IMAGE_SIZE g->x * g->y
#define FLOAT_SIZE sizeof(float)

namespace mincut {
  float mincut (Graph *g) ;
}

short int LOOKUP_2[][2] = {
    {U,U},
    {U,D},
    {U,L},
    {U,R},
    {L,U},
    {L,D},
    {L,L},
    {L,R},
    {R,U},
    {R,D},
    {R,L},
    {R,R},
    {D,U},
    {D,D},
    {D,L},
    {D,R},
};

short int LOOKUP_3[][2] = {
    {U,U},
    {U,D},
    {U,L},
    {U,R},
    {L,U},
    {L,D},
    {L,L},
    {L,R},
    {R,U},
    {R,D},
    {R,L},
    {R,R},
    {D,U},
    {D,D},
    {D,L},
    {D,R},
};



#endif
