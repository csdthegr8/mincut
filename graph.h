#ifndef GRAPH_H
#define GRAPH_H

#define U 0
#define D 1
#define L 2
#define R 3
namespace mincut {
class Graph
{
public:
    Graph();
    float *m_pixelData;
    unsigned int x,y,z;

    Graph(int x, int y, float **values);
    float *m_adjweights;

    void buildAdjacency(bool verbose = false);

};

}

#endif // GRAPH_H
