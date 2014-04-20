#include <iostream>
#include <vector>
#include <vtkMetaImageReader.h>
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkDataArray.h>
#include <vtkJPEGReader.h>
#include <fstream>
#include "graph.h"
using namespace std;

int main()
{

//    std::string mhd_filename = "/home/sci/sdharan/mincut/data/GradientImage2d_op.mhd";
//    std::string raw_filename = "/home/sci/sdharan/mincut/data/GradientImage2d_op.raw";
    std::string flower = "/home/sci/sdharan/flower.jpg";

    vtkSmartPointer<vtkJPEGReader> reader =
            vtkSmartPointer<vtkJPEGReader>::New();
    reader->SetFileName(flower.c_str());
    reader->Update();
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
            pixelvals[i][j] = imData->GetScalarComponentAsFloat(i,j,0,0);
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
    float flow = g->mincut(mincut::SERIAL_FF);

    ofstream fout("outputimage");
    for (int i = 0; i < g->x; i++) {
        for (int j = 0; j < g->y; j++){
            if (g->m_slinks[i*g->y+j] != 0) {
                fout << "1 ";

            }
            else {
                fout << "0 ";
            }
        }
        fout << std::endl;
    }
    std::cout << "Hey! the flow is :" << flow;
    return 0;
}

