// API for Mincut
// Author : Shridharan Chandramouli
// Coded as part of final project for CS6345

#include "graph.h"
#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <string.h>
#include <string>

#include<fstream>
namespace mincut{

int offsets[][2] = { {-1 ,0}, { 0,-1}, {1,0}, {0,1}};

Graph::Graph(int x, int y,  float **values):x(x), y(y) {

    this->m_pixelData = new float[x*y]();
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            m_pixelData[i*y+j] = values[i][j];
        }
    }

    this->m_capacity = new float[5*this->x*this->y]();
    this->m_flow = new float[5*x*y]();

    this->m_slinks = new float[x*y];

    this->buildAdjacency();
}

Graph::Graph(int nx, int ny, int x, int y, float **values, int ax, int ay) : x(x), y(y)
{
    this->m_pixelData = new float[x*y]();
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            if (nx*x + i >= ax || ny*y + j >= ay) {
                continue;
            }
            m_pixelData[i*y+j] = values[nx*x + i][ny*y + j];
        }
    }
    this->m_capacity = new float[5*this->x*this->y]();
    this->m_flow = new float[5*x*y]();

    this->m_slinks = new float[x*y];

    this->buildAdjacency();

}

void Graph::buildAdjacency(bool verbose) {
    if (verbose) {
        std::cout << "Building adjacency...\n" << std::flush;
    }

    // Rough estimates for n & t-links
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            for (int k = 0; k < 4; k++) {
                int nx = i + offsets[k][0];
                int ny = j + offsets[k][1];
                if (nx >= 0 && nx < x && ny >=0 && ny < y) {
                    this->m_capacity[5*(i*y+j) + k] = 255.0f - fabs(this->m_pixelData[i*y+j] - this->m_pixelData[nx*y+ny]);
                }
                else {
                    this->m_capacity[5*(i*y+j)+k] = UNDEF;
                }
            }
            this->m_slinks[i*y+j] = 255.0f - this->m_pixelData[i*y+j];
            this->m_capacity[5*(i*y+j) + 4 ] = 0.0f + this->m_pixelData[i*y+j];
        }
    }
}

float Graph::mincut(ALGORITHM type, bool verbose) {
    switch (type) {
    case SERIAL_FF:
        return this->serialFF(verbose);
    default:
        std::cout << "Not implemented yet!";
    }
}

void Graph::mergeGraphs(Graph *otherGraph, int nx, int ny) {
    for (int i = 0; i < otherGraph->x; i++) {
        for (int j = 0; j < otherGraph->y; j++) {
            int offset = (nx*otherGraph->x+i)*this->y+(ny*otherGraph->y+j);
            std::cout << "Copying {" << i  << "," << j << "} to {" << nx*otherGraph->x + i << "," << ny*otherGraph->y +j << " as " << offset << std::endl;
            for (int k = 0; k < 5; k++) {
                this->m_flow[5*(offset) + k] = otherGraph->m_flow[5*(i*otherGraph->y+j) + k];
            }
            this->m_slinks[offset] = otherGraph->m_slinks[i*otherGraph->y+j];
        }
    }
}

void Graph::recomputeAdjacency() {

    for (int i = 1; i < this->x-1; i++) {
        for (int j = 1; j < this->y-1; j++){
            for (int k = 0; k < 4; k++) {
                if (m_capacity[5*(i*y+j) + k] == UNDEF) {
                    int nx = i + offsets[k][0];
                    int ny = j + offsets[k][1];
                    if (nx >= 0 && nx < x && ny >=0 && ny < y) {
                        this->m_capacity[5*(i*y+j) + k] = 255.0f - fabs(this->m_pixelData[i*y+j] - this->m_pixelData[nx*y+ny]);
                    }
                }
            }
        }
    }
}

float Graph::serialFF (bool verbose) {
    float flow;
    int flow_map [][2]  = {
        {0,2},
        {1,3},
        {2,0},
        {3,1}
    };
    vec2 size(this->x,this->y);
    int *pred = new int[size.x*size.y];
    bool *visited = new bool[size.x*size.y];
//    memset(pred, 0, sizeof(int)*x*y);
    memset(visited,0,sizeof(bool)*x*y);
//    for (int i = 0; i < x; i++) {
//        for (int j = 0; j < y; j++) {
//            pred[i*y+j] = -1;
//            visited[i*y+j] = false;
//        }
//    }

    vec2 end(-1,-1);
    float increment = 0.0f;
    bool first = true;
    int parentpos = -1, lastpos = -1;
    while ((lastpos = findPath(pred, visited,size)) > -1) {
        vec2 node = vec2::ind2sub(size,lastpos);
        parentpos = pred[lastpos];
        vec2 backup = node;
        while(parentpos != SOURCE) {
            vec2 parent = vec2::ind2sub(size, parentpos);
            int xdiff = -parent.x + node.x;
            int ydiff = -parent.y + node.y;

            int offset = -1;
            if (xdiff > 0) {
                // Parent is to the right of node
                offset = 2;
            } else if (xdiff < 0) {
                // Parent is to the left of node
                offset = 0;

            } else if (ydiff > 0) {
                // parent is to the bottom of node
                offset = 3;

            } else if (ydiff < 0) {
                // parent is to the top of node
                offset = 1;

            } else {
                std::cerr << "Something is wrong!";
                exit(-1);
            }

            if (first) {
                increment = m_capacity[5*parentpos + offset] - m_flow[5*parentpos+offset];
                first = false;
            }
            else {
                increment = std::min((m_capacity[5*parentpos+offset] - m_flow[5*parentpos+offset]), increment);
            }

            if (verbose) {
                std::cout << "{ " << node.x  << " , " << node.y << " } <- (" << offset << ","  << m_capacity[5*parentpos + offset] - m_flow[5*parentpos+offset] << ")<-" ;
            }

            node = parent;
            backup = node;
            parentpos = pred[node.sub2ind(size)];
        }
        if(verbose) {
            std::cout << "{ " << node.x  << " , " << node.y << " } <- (" << "?" << ","  << m_slinks[backup.sub2ind(size)] << ") <-" ;
            std::cout << std::endl;
        }
        // Update increment to account for lastnode -> SINK
        if (!first) {
            increment = std::min(m_slinks[node.x*size.y+ node.y], increment);
            increment = std::min(m_capacity[5*lastpos+4]- m_flow[5*lastpos+4],increment);
        } else {
            increment = std::min(m_slinks[node.x*size.y+ node.y],m_capacity[5*lastpos+4]- m_flow[5*lastpos+4]);
        }
        parentpos = pred[lastpos];
        node = vec2::ind2sub(size,lastpos);
        while(parentpos != SOURCE) {
            vec2 parent = vec2::ind2sub(size, parentpos);
            int xdiff = -parent.x + node.x;
            int ydiff = -parent.y + node.y;

            int offset = -1;
            if (xdiff > 0) {
                // Parent is to the bottom of node
                offset = 2;
            } else if (xdiff < 0) {
                // Parent is to the top of node
                offset = 0;

            } else if (ydiff > 0) {
                // parent is to the right of node
                offset = 3;

            } else if (ydiff < 0) {
                // parent is to the left of node
                offset = 1;
            } else {
                std::cerr << "Something is wrong!";
                exit(-1);
            }

            m_flow[5*parentpos+offset] += increment;
            int oppositeoffset = flow_map[offset][1];
            m_flow[5*node.sub2ind(size) + oppositeoffset] -= increment;
            node = parent;
            parentpos = pred[node.sub2ind(size)];
        }
        m_slinks[backup.sub2ind(size)] -= increment;
        m_flow[lastpos*5 + 4] += increment;
        flow += increment;

//        for (int i = 0; i < x; i++) {
//            for (int j = 0; j < y; j++) {
//                pred[i*size.y+j] = -1;
//                visited[i*size.y+j] = false;
//            }
//        }
        memset(visited, 0, sizeof(bool)*x*y);
    }
    std::cout << "Flow is " << flow;
    return flow;
}

int Graph::getUnvisitedNeighbor(bool *visited, int &pos, bool checkcapacity) {
    int xpos = pos / y;
    int ypos = pos % y;

    if (m_capacity[5*(xpos*y+ypos) + 4] - m_flow[5*(xpos*y+ypos) + 4] > 0) {
        return SINK;
    }

    for (int i = 0; i < 4; i++) {
        int xnext = xpos + offsets[i][0];
        int ynext = ypos + offsets[i][1];
        if (xnext < x && ynext < y && xnext >= 0 && ynext >= 0) {
            if (checkcapacity) {
                if (m_capacity[5*(xpos*y+ypos) + i] == UNDEF) {
                    continue;
                }
                if (!visited[xnext*y+ ynext] && (m_capacity[5*(xpos*y+ypos) + i] - m_flow[5*(xpos*y+ypos) + i] > 0)) {
                    return xnext*y+ynext;
                }
            } else {
                if (!visited[xnext*y+ ynext]) {
                    return xnext*y+ynext;
                }
            }
        }
    }


    return -1;
}

int Graph::findPath(int *pred, bool *visited, vec2 &size) {

    int head = 0, tail = 0;
    int queue[size.x * size.y];
    for (int i = 0; i < x*y; i++) {
        if (this->m_slinks[i] != 0) {
            queue[tail++] = i;
            visited[i] = true;
            pred[i] = SOURCE;
        }
    }
    int lastpred = -1;

    while (head != tail) {
        int pos = queue[head++];
        int next_nodepos;
        do {
            next_nodepos = this->getUnvisitedNeighbor(visited, pos, true);
            if (next_nodepos == -1) {
                // Cannot find a path
                continue;
            }
            if (next_nodepos == SINK) {
                // Found a path
                lastpred = pos;
//                std::cout << "Hey!" << std::endl;
                return lastpred;
            }
            // Update predecessor
            queue[tail++] = next_nodepos;
            visited[next_nodepos] = true;
            pred[next_nodepos] = pos;
        } while (next_nodepos != -1);
    }
    return lastpred;
}

void Graph::writeSegmentedImage(std::string filename) {
    std::ofstream fout(filename.c_str());
    bool *out = new bool[x*y];
    for (int i = 0; i < x*y; i++) {
        if (m_slinks[i] != 0) {
            bfs(i, &out[0]);
        }
    }

    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            fout << out[i*y+j] ? 1 : 0;
        }
        fout << std::endl;
    }
}

void Graph::bfs(int start, bool *visited) {
    int queue[x*y];

    int head = 0, tail = 0;

    queue[tail++] = start;

    while (head!=tail) {
        int pos = queue[head++];
        while(true) {
            int next_nodepos = this->getUnvisitedNeighbor(visited, pos, true);
            if (next_nodepos == -1) {
                break;
            } else if (next_nodepos == SINK) {
                std::cerr << "Bad Output!" <<std::endl << std::flush;
                break;
            }
            visited[next_nodepos] = true;
        }
    }
}

Graph::Graph()
{

}


}
