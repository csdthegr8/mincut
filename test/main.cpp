#include <iostream>
#include <vector>
#include <vtkMetaImageReader.h>
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkDataArray.h>
#include <vtkJPEGReader.h>
#include <fstream>
#include "graph.h"
#include <thread>
#include "driver.cuh"
using namespace std;

int splitFF(int n,float **pixelvals, int x, int y) {
//    int nx = (x+n-1)/n;
//    int ny = (y+n-1)/n;

    int nx = 2;
    int ny = 1;
    std::thread t[2];
    mincut::Graph* g[2];
    for (int i = 0; i < 1; i++) {
        for (int j = 0; j < 2; j++) {
            g[j] = new mincut::Graph(i,j, 203, 135, pixelvals, x,y);
            t[j] = std::thread(&mincut::Graph::mincut, g[j], mincut::SERIAL_FF,false);
        }
    }

    mincut::Graph *cG = new mincut::Graph(x,y,pixelvals);
//    for (int j = 0; j < n ; j++) {
////        for (int i = 0; i < n ; i++){
//            t[i*j+n].join();
////            cG->mergeGraphs(g[i+j*n],j,i);
//        }
//    }

    t[0].join();
    t[1].join();

    cG->mergeGraphs(g[0],0,0);
    cG->mergeGraphs(g[0],0,1);
    cG->mincut(mincut::SERIAL_FF,true);
    cG->writeSegmentedImage("testout");
}

int main()
{

//    std::string mhd_filename = "/home/sci/sdharan/mincut/data/GradientImage2d_op.mhd";
//    std::string raw_filename = "/home/sci/sdharan/mincut/data/GradientImage2d_op.raw";

    std::string flower = "/home/shri/flower.jpg";

    vtkSmartPointer<vtkJPEGReader> reader =
            vtkSmartPointer<vtkJPEGReader>::New();
    reader->SetFileName(flower.c_str());
    reader->Update();\
    vtkImageData *imData = reader->GetOutput();
    //imData->GetPointData()
    //unsigned char *datapointer = ( unsigned char*)

    float **pixelvals = new float*[203];
    for (int i = 0; i < 203; i++) {
        pixelvals[i] = new float[270];
    }
    for (int i = 0; i < 203; i++) {
        for (int j = 0; j < 270; j++) {
            //int coordinates[] = {i, j};
            pixelvals[i][j] = imData->GetScalarComponentAsFloat(j,i,0,0);
            //pixelvals[i][j] = i / 16 == 0 ? 1 : 2;
        }
    }
//    float **pixels = new float*[3];
//    pixels[0] = new float[3];
//    pixels[1] = new float[3];
//    pixels[2] = new float[3];


//    pixels[0][0] = 10.0f;
//    pixels[0][1] = 15.0f;
//    pixels[0][2] = 25.0f;
//    pixels[1][0] = 5.0f;
//    pixels[1][1] = 220.0f;
//    pixels[1][2] = 240.0f;
//    pixels[2][0] = 12.0f;
//    pixels[2][1] = 15.0f;
//    pixels[2][2] = 230.0f;

    mincut::Graph *g = new mincut::Graph(203,270,pixelvals);
    //float flow = g->mincut(mincut::SERIAL_FF);

    mincut::GPUGraph *gg = new mincut::GPUGraph(g);

    gg->mincut(mincut::SERIAL_FF, true);
    //splitFF(4, pixelvals, 203, 270);

}


