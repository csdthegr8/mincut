#include "graph.h"
#include <iostream>
#include <string.h>

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
    int flow_map [2][]  = {
        {0,2},
        {1,3},
        {2,0},
        {3,1}
    };
    vec2 size(this->x,this->y);
    vec2 start(0,0);
    int *pred = new int[size.x*size.y];
    bool **visited = new bool*[size.x];
    for (int i = 0; i < size.y; i++) {
        visited[i] = new bool[size.y];
    }
    for (int i = 0; i < this->x; i++) {
        memset(visited, 0, this->x*this->y);
        memset(pred, 0, this->x*this->y);
        vec2 end(-1,-1);
        float increment = 0;
        bool first = true;
        while (findPath(start,&end, pred, visited,size)) {
            vec2 node = end;
            int parentpos = pred[node.sub2ind(size)];
            while(parentpos != -1) {
                vec2 parent = vec2::ind2sub(size, pred[node.sub2ind(size)]);
                int xdiff = parent.x - node.x;
                int ydiff = parent.y - node.y;

                float weight = 0;
                int offset = -1;
                if (xdiff > 0) {
                    // Parent is to the right of node
                    offset = 0;
                } else if (xdiff < 0) {
                    // Parent is to the left of node
                    offset = 2;

                } else if (ydiff > 0) {
                    // parent is to the bottom of node
                    offset = 1;

                } else if (ydiff < 0) {
                    // parent is to the top of node
                    offset = 3;

                } else {
                    std::cerr << "Something is wrong!";
                    exit(-1);
                }


                if (first) {
                    increment = m_capacity[parentpos + offset] - m_flow[parentpos+offset];
                    first = false;
                }
                else {
                    increment = std::min((m_capacity[parentpos+offset] - m_flow[parentpos+offset]), increment);
                }
                node = parent;
                parentpos = pred[node.sub2ind(size)];
            }
            parentpos = pred[end.sub2ind(size)];
            while(parentpos != -1) {
                vec2 parent = vec2::ind2sub(size, parentpos);
                int xdiff = parent.x - node.x;
                int ydiff = parent.y - node.y;

                float weight = 0;
                int offset = -1;
                if (xdiff > 0) {
                    // Parent is to the right of node
                    offset = 0;
                } else if (xdiff < 0) {
                    // Parent is to the left of node
                    offset = 2;

                } else if (ydiff > 0) {
                    // parent is to the bottom of node
                    offset = 1;

                } else if (ydiff < 0) {
                    // parent is to the top of node
                    offset = 3;

                } else {
                    std::cerr << "Something is wrong!";
                    exit(-1);
                }


                m_capacity[parentpos+offset] += increment;
                int oppositeoffset = flow_map[offset][1];
                m_capacity[node.sub2ind(size) + oppositeoffset] -= increment;
                node = parent;
                parentpos = pred[node.sub2ind(size)];

            }
            flow += increment;
        }
        start.x++;
    }
    return flow;
}

bool Graph::findPath(vec2 &start, vec2 *end, int *pred, bool **visited, vec2 &size) {
    int head = 0, tail = 0;

    int queue[size.x * size.y];
    queue[tail++] = start.sub2ind(size);
    visited[start.x][start.y] = true;
    bool pathfound = false;
    pred[start.sub2ind(size)] = -1;
    vec2 end_node(-1,-1);
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
    return pathfound;
}

Graph::Graph()
{

}

}
