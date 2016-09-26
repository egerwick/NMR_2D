#include <iostream>
#include <string>
#include <time.h>
#include <dirent.h>
#include "HSQC_Data.H"
#include "Similarity.C"
#include "Base.C"
#include "Base.H"

using namespace std;


int Base::debugging_mode = 0;


int main( int argc, char** argv )
{
    clock_t t1,t2;
    t1=clock();

    //path to data
    Similarity sim;
    sim.in_path = "real_data/";
    sim.get_files();

    //correlations matrix n(n+1)/2 indirectly
    std::vector<HSQC_Data> hsqc_data(sim.num_files());
    sim.filename = "network1.dat";
    sim.path = "networks/";
    sim.clear_file();

    for(size_t i(0); i<sim.num_files(); ++i)
    {
        hsqc_data[i].read_from_file(sim.in_path,sim.in_files[i]);
        hsqc_data[i].assign_id(i);
        //hsqc_data[i].nodes_to_network_file(sim.path+sim.filename);
    }

    //similarity comparator
    sim.edge_thresh =  0.0;
    sim.edge_thresh =  0.0;
    sim.pt_threshold =  1.0;
    sim.weight_C =  1.0;
    sim.weight_H =  20.0;
    sim.number_iterations = 10;
    sim.highest_H_weight = 30;
    sim.lowest_H_weight = 10;
    int number_of_comparisons = 0;
    for(size_t i(0); i<sim.num_files(); ++i)
    {
        for(size_t j(i+1); j<sim.num_files(); ++j)
        {
            number_of_comparisons++;
            sim.compare(hsqc_data[i],hsqc_data[j]);
            if( sim.check_add_edge() ) sim.edge_to_network_file();
        }
    }

    std::cout << "num comparisons: " << number_of_comparisons << std::endl;
    t2=clock();
    float diff ((float)t2-(float)t1);
    float seconds = diff / CLOCKS_PER_SEC;
    std::cout << "time: " << seconds << std::endl;

}




