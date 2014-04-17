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

    this->m_capacity = new float[this->x*this->y];
    memset(this->m_capacity,0, x*y);
    this->m_flow = new float[x*y];
    memset(this->m_flow, 0, x*y);

    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            for (int k = 0; k < 4; k++) {
                int nx = i + offsets[k][0];
                int ny = j + offsets[k][0];
                if (nx >= 0 && nx < x && ny >=0 && ny < y) {
                    this->m_capacity[i*y+j + k] = this->m_pixelData[i*y+j] - this->m_pixelData[nx*y+ny];
                }
                else {
                    this->m_capacity[i*y+j+k] = 0;
                }
            }
        }
    }
}

float Graph::mincut(ALGORITHM type) {
    switch (type) {
    case SERIAL_FF:
        return this->serialFF();
    default:
        std::cout << "Not implemented yet!";
    }
}

float Graph::serialFF() {
    float flow;
    vec2 size(this->x,this->y);
    vec2 start(0,0);
    int pred[size.x*size.y];
    bool visited[this->x][this->y];
    for (int i = 0; i < this->x; i++) {
        memset(visited, 0, this->x*this->y);
        memset(pred, 0, this->x*this->y);
        vec2 end;
        while (findPath(start,&end, pred, visited)) {
            for (u=n-1; pred[u]>=0; u=pred[u]) {
                increment = min(increment,capacity[pred[u]][u]-flow[pred[u]][u]);
            }
            // Now increment the flow.
            for (u=n-1; pred[u]>=0; u=pred[u]) {
                flow[pred[u]][u] += increment;
                flow[u][pred[u]] -= increment;
            }
            max_flow += increment;
        }
        start.x++;
    }
}

bool Graph::findPath(vec2 start, vec2 *end, int **pred, bool **visited, vec2 size) {
    int head = 0, tail = 0;

    int queue[size.x * size.y];
    queue[tail++] = start.sub2ind(size);
    visited[start.x][start.y] = true;
    bool pathfound = false;
    pred[start.sub2ind(size)] = -1;
    vec2 end_node;
    while (head != tail) {
        int pos = queue[head++];

        while (true) {
            vec2 next_node = this->getUnvisitedNeighbor(size, visited, pos);
            if (next_node.x == -1) {
                break;
            }
            queue[tail++] = next_node.sub2ind(size);
            visited[next_node.x][next_node.y] = true;
            pred[next_node.sub2ind(size)] = pos;
            if (next_node.isSink(size)) {
                pathfound = true;
                end_node = next_node;
                break;
            }
        }
    }
    if (pathfound) {
        end = &end_node;
    }
}

Graph::Graph()
{

}

}
