//// This code does graph cuts based on Vnet strategy, with intensity profiles as their cost functions

//#include <stdlib.h>
//#include <stdio.h>
//#include <iostream>
//#include <fstream>
//#include <vector>
//#include <string>
//#include <sstream>
//#include <cmath>

//#include "graph.h"

//using namespace std;

//#define sec_dim 25
//#define inf_vlu 1E+10
//#define DELTAS 4 // smoothness constraint; 3 for superquadric, 4 for heart
//#define DELTAL 2 // lower separation constraint; 2 for superquadric, 4 for heart
//#define DELTAU 8 // upper separation constraint; 12 for superquadric, 12 for heart
//#define numS 2

//int main()
//{
//      // allocate memory for weight matrix
//        float** Wgtmat1 =  new float*[Mlayers];
//        float** Wgtmat2 =  new float*[Mlayers];
//        for (int i = 0; i< Mlayers; i++){
//          Wgtmat1[i] = new float[nop];
//          Wgtmat2[i] = new float[nop];
//        }
//        for (int m = 0; m < Mlayers; m++){
//          for (int n = 0; n < nop; n++){
//              if (m < (Mlayers-1)){
//                  Wgtmat1[m][n] = Costmat1[m][n] - Costmat1[m+1][n];
//                  Wgtmat2[m][n] = Costmat2[m][n] - Costmat2[m+1][n];
//              }
//              else if (m == (Mlayers-1)){
//                  if (n < (nop - 1)){
//                    Wgtmat1[m][n] = Costmat1[m][n] - (Costmat1[m][n] + Costmat1[m][n+1] - 1);
//                    Wgtmat2[m][n] = Costmat2[m][n] - (Costmat2[m][n] + Costmat2[m][n+1] - 1);
//                  }
//                  else{
//                    Wgtmat1[m][n] = Costmat1[m][n];
//                    Wgtmat2[m][n] = Costmat2[m][n];
//                  }
//              }
//	  }
//        }

//        // Building a graph
//        typedef Graph<float,float,float> GraphType;
//        int num_nodes = Mlayers*nop;
//        cout<< "Total number of nodes = " << num_nodes<<"\n";

//        // calculate number of arcs from the second column of connectivity matrix
//        int numedges = 0;
//        for (int i = 0; i < nop; i++){
//            numedges = numedges + nbor_mat[i][1];
//        }

//        // num_intraarcs = T-link arcs + vertical arcs + oblique vertical arcs + base graph arcs
//        int num_intraarcs = Mlayers*nop + (Mlayers-1)*nop + (Mlayers-DELTAS)*numedges + numedges;
//        // num_interarcs = V1->V2 arcs + V2-> V1 arcs + base graph arcs
//        int num_interarcs = (Mlayers-(DELTAU-DELTAL))*nop + Mlayers*nop + numedges;

//        int num_arcs = numS*num_intraarcs + num_interarcs;
//        cout<< "Total number of arcs = " << num_arcs<< "\n";

//        GraphType *g = new GraphType(numS*num_nodes,num_arcs);

//        // adding nodes
//        cout << "adding nodes..." << endl;
//        for (int gn = 0; gn < numS*num_nodes; gn++)
//            g->add_node();

//        cout << "nodes added. Now, adding arcs..." << endl;
//        //adding arcs
//        // arcs connecting source and sink (T-links)
//        for (int m = 0; m < Mlayers; m++){
//            for (int n = 0; n < nop; n++ ){
//                float Tlnkcost1 = Wgtmat1[m][n];
//                if (Tlnkcost1 < 0){
//                    g->add_tweights(m*nop + n, -Tlnkcost1, 0);
//                }
//                else{
//                    g->add_tweights(m*nop + n, 0, Tlnkcost1);
//                }

//                float Tlnkcost2 = Wgtmat2[m][n];
//                if (Tlnkcost2 < 0){
//                    g->add_tweights(num_nodes + m*nop + n, -Tlnkcost2, 0);
//                }
//                else{
//                    g->add_tweights(num_nodes + m*nop + n, 0, Tlnkcost2);
//                }
//            }
//        }
//        cout << "T-links added to the graph. Now, adding N-links..." << "\n";

//        cout << "arcs connecting node to the node below it"<< "\n";
//        // arc from a node to the node below it
//        for (int m = 0; m < (Mlayers-1); m++){
//            for (int n = 0; n < nop; n++ ){
//              g->add_edge(m*nop + n, ((m+1)*nop) + n, inf_vlu, 0);
//              g->add_edge(num_nodes + m*nop + n, num_nodes + ((m+1)*nop) + n, inf_vlu, 0);
//        //    cout << m * nop  + n << "<->"<< (m+1) * nop + n << " ";
//            }
//        }

//        cout<<"arcs connecting nodes in the base graph" << endl;
//        int m = (Mlayers-1);
//        for (int n = 0; n < nop; n++ ){
//            for (int c = 2;c < sec_dim; c++){
//                if (Nnbor_mat[n][c] != -1){
//                    g->add_edge((m*nop)+Nnbor_mat[n][0],(m*nop) + Nnbor_mat[n][c], inf_vlu, 0);
//                    g->add_edge(num_nodes + (m*nop)+Nnbor_mat[n][0], num_nodes + (m*nop) + Nnbor_mat[n][c], inf_vlu, 0);
////                    cout << m*nop+Nnbor_mat[n][0] << "<->" << m*nop + Nnbor_mat[n][c] << " ";
//                }
//            }
//        }

//        cout << "arcs connecting node to the side-nodes in the layer below it" <<endl;
//        for (int m = 0; m < (Mlayers-DELTAS); m++){
//            for (int n = 0; n < nop; n++ ){
//                for (int c = 2;c < sec_dim; c++){
//                    if (Nnbor_mat[n][c] != -1){
//                        g->add_edge((m*nop)+Nnbor_mat[n][0],((m+DELTAS)*nop) + Nnbor_mat[n][c], inf_vlu, 0);
//                        g->add_edge(num_nodes + (m*nop)+Nnbor_mat[n][0],num_nodes + ((m+DELTAS)*nop) + Nnbor_mat[n][c], inf_vlu, 0);
////                            cout << m*nop+Nnbor_mat[n][0] << "<->" << (m+1)*nop + Nnbor_mat[n][c] << " ";
//                    }
//                }
//            }
//        }

//        cout << "Inter-surface arcs" << "\n";
//        for (int m = 0; m < Mlayers; m++){
//            for (int n = 0; n < nop; n++ ){
//                g->add_edge(num_nodes + m*nop + n, m*nop + n, inf_vlu, 0);
//                if (m < (Mlayers-(DELTAU-DELTAL))){
//                    g->add_edge(m*nop + n, num_nodes + ((m+(DELTAU-DELTAL))*nop)+n, inf_vlu, 0);
//                }
//                else if (m == (Mlayers-1))
//                    g->add_edge( m*nop + n, num_nodes + m*nop + n, inf_vlu, 0);
//            }
//        }

//        cout << "all arcs added" << endl;

//       // Finding minimum s-t cut
//        float flow = g -> maxflow();
//        cout<< "Flow = " << flow<< "\n";

//        // allocate memory for segmentation region matrix
//        int** Segrgnmat1 =  new int*[Mlayers];
//        int** Segrgnmat2 =  new int*[Mlayers];
//        for (int m = 0; m< Mlayers; m++){
//          Segrgnmat1[m] = new int[nop];
//          Segrgnmat2[m] = new int[nop];
//        }

//        for (int m = 0; m < Mlayers; m++){
//          for (int n = 0; n < nop; n++){
//              if (g -> what_segment(m*nop + n) == GraphType::SOURCE)
//                Segrgnmat1[m][n] = 150;
//              else
//                Segrgnmat1[m][n] = 0;

//              if (g -> what_segment(num_nodes + m*nop + n) == GraphType::SOURCE)
//                Segrgnmat2[m][n] = 150;
//              else
//                Segrgnmat2[m][n] = 0;

//            }
//        }
//    return 0;
//}


