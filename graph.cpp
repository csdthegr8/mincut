#include "graph.h"

namespace mincut{

Graph::Graph(int x, int y,  float **values):x(x), y(y) {

    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            m_pixelData[i*y+j] = values[i][j];
        }
    }
    this->buildAdjacency(true);
}

void Graph::buildAdjacency(bool verbose) {
    if (verbose) {
        std::cout << "Building adjacency...\n";
    }
    int offsets[2][2] = { {-1 ,0}, { 0,-1}, {0,1}, {1,0}};
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            for (int k = 0; k < 4; k++) {
                int nx = i + offsets[k][0];
                int ny = j + offsets[k][0];
                if (nx >= 0 && nx < x && ny >=0 && ny < y) {
                    this->m_adjweights[i*y+j + k] = this->m_pixelData[i*y+j] - this->m_pixelData[nx*y+ny];
                }
                else {
                    this->m_adjweights[i*y+j+k] = 0;
                }
            }
        }
    }
}

Graph::Graph()
{

}

}
