#ifndef GRAPH_H
#define GRAPH_H

#define U 0
#define D 1
#define L 2
#define R 3
namespace mincut {
enum ALGORITHM {
    SERIAL_FF,
    GPU_FF,
    SERIAL_BK,
    SERIAL_PR,
    GPU_PR,
};
int offsets[2][2] = { {-1 ,0}, { 0,-1}, {0,1}, {1,0}};


class Graph
{
public:
    Graph();
    float *m_pixelData;
    unsigned int x,y,z;

    Graph(int x, int y, float **values);
    float *m_capacity;
    float *m_flow;

    void buildAdjacency(bool verbose = false);

    float mincut(ALGORITHM type);
    float serialFF();
    inline vec2 getUnvisitedNeighbor(vec2 size, bool *visited, int pos) {
        int xpos = pos / size.y;
        int ypos = pos % size.y;

        for (int i = 0; i < 4; i++) {
            int xnext = xpos + offsets[i][0];
            int ynext = ypos + offsets[i][1];
            if (!visited[xnext*size.y + ynext] && (m_capacity[xnext][ynext] - m_flow[xnext][ynext] > 0)) {
                return vec3(xnext,ynext);
            }
        }
        return vec3(-1,-1);
    }

};

class vec2
{
public:
    vec2::vec2(int x, int y) : x(x), y(y) {}
    int x,y;
    bool isSink(vec2 size) {
        if (y == size.y) {
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
}

#endif // GRAPH_H
