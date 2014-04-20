#ifndef GRAPH_H
#define GRAPH_H

#define U 0
#define D 1
#define L 2
#define R 3
#define SOURCE -63
#define SINK -64 // some random negative numbers

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
    float *m_capacity;
    float *m_flow;
    float *m_slinks;
    void buildAdjacency(bool verbose = false);

    float mincut(ALGORITHM type);
    float serialFF();
    inline int getUnvisitedNeighbor(vec2 &size, bool *visited, int &pos);

    //bool findPath(vec2 *end, int *pred, bool **visited, vec2 &size);
    int findPath(int *pred, bool *visited, vec2 &size);
};

}

#endif // GRAPH_H
