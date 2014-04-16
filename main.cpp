#include <iostream>
#include <vector>
#include <vtk/vtkMetaImageReader.h>
#include <vtk/vtkSmartPointer.h>
#include <vtk/vtkImageData.h>
#include <vtk/vtkDataArray.h>
#include <fstream>
#include "graph.h"
using namespace std;

int main()
{

    std::string mhd_filename = "/home/shri/mincut/data/GradientImage2d_op.mhd";
    std::string raw_filename = "/home/shri/mincut/data/GradientImage2d_op.raw";

    vtkSmartPointer<vtkMetaImageReader> reader =
            vtkSmartPointer<vtkMetaImageReader>::New();
    reader->SetFileName(mhd_filename.c_str());
    reader->Update();
    vtkImageData *imData = reader->GetOutput();
    //imData->GetPointData()
    //unsigned char *datapointer = ( unsigned char*)

    float pixelvals[32][60];
    for (int i = 0; i < 32; i++) {
        for (int j = 0; j < 60; j++) {
            int coordinates[] = {i, j};
            pixelvals[i][j] = imData->GetScalarComponentAsFloat(i,j,0,0);
        }
    }
    return 0;
}

