#ifndef GRAPH_H
#define GRAPH_H

#include<string>
#define U 0
#define D 1
#define L 2
#define R 3
#define SOURCE -63
#define SINK -64 // some random negative numbers
#define UNDEF -65

namespace mincut {
enum ALGORITHM {
    SERIAL_FF,
    GPU_FF,
    SERIAL_BK,
    SERIAL_PR,
    GPU_PR,
};
class vec2
{
public:
    vec2(int x, int y) : x(x), y(y) {}
    int x,y;
    bool isSink(vec2 size) {
        if (y == size.y-1) {
            return true;
        }
        return false;
    }
    inline int sub2ind(vec2 size){
        return x*size.y + y;
    }
    static inline vec2 ind2sub(vec2 size, int pos) {
        vec2 vecpos(pos/size.y, pos % size.y);
        return vecpos;
    }
};

class Graph
{
public:
    Graph();
    float *m_pixelData;
    unsigned int x,y,z;

    Graph(int x, int y, float **values);
    Graph(int nx, int ny, int x, int y, float **values, int ax, int ay);
    float *m_capacity;
    float *m_flow;
    float *m_slinks;
    void buildAdjacency(bool verbose = false);

    float mincut(ALGORITHM type, bool verbose=false);
    float serialFF(bool verbose = false);
    inline int getUnvisitedNeighbor( bool *visited, int &pos, bool checkcapacity);

    //bool findPath(vec2 *end, int *pred, bool **visited, vec2 &size);
    int findPath(int *pred, bool *visited, vec2 &size);
    void writeSegmentedImage(std::string filename);
    void bfs(int start, bool *visited);
    void mergeGraphs(Graph *otherGraph, int nx, int ny);
    void recomputeAdjacency();
};

}

#endif // GRAPH_H
