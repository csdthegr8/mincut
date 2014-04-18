#include <iostream>
#include <vector>
#include <vtkMetaImageReader.h>
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkDataArray.h>
#include <fstream>
#include "graph.h"
using namespace std;

int main()
{

    std::string mhd_filename = "/home/sci/sdharan/mincut/data/GradientImage2d_op.mhd";
    std::string raw_filename = "/home/sci/sdharan/mincut/data/GradientImage2d_op.raw";

    vtkSmartPointer<vtkMetaImageReader> reader =
            vtkSmartPointer<vtkMetaImageReader>::New();
    reader->SetFileName(mhd_filename.c_str());
    reader->Update();
    vtkImageData *imData = reader->GetOutput();
    //imData->GetPointData()
    //unsigned char *datapointer = ( unsigned char*)

    float **pixelvals = new float*[32];
    for (int i = 0; i < 32; i++) {
        pixelvals[i] = new float[32];
    }
    for (int i = 0; i < 32; i++) {
        for (int j = 0; j < 32; j++) {
            int coordinates[] = {i, j};
            pixelvals[i][j] = imData->GetScalarComponentAsFloat(i,j,0,0);
            //pixelvals[i][j] = i / 16 == 0 ? 1 : 2;
        }
    }

    mincut::Graph *g = new mincut::Graph(32,32,pixelvals);
    float flow = g->mincut(mincut::SERIAL_FF);
    std::cout << "Hey! the flow is :" << flow;
    return 0;
}

