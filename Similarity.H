#ifndef __Similarity_H
#define __Similarity_H
#include <iostream>
#include <string>
#include <vector>
#include "Edge.H"
#include "Similarity_Algo.H"


class Similarity: public Base, public Similarity_Algo
{
private:
    std::vector<double> m_corr_vec;
    std::vector<double> H_weights;
    double m_corr;
    std::string m_node_name_L;
    std::string m_node_name_R;
    int m_L;
    int m_R;
    //methods
    void get_H_weights();

public:
    Similarity();
    ~Similarity();
    std::string filename;
    std::string path;
    double edge_thresh;
    int number_iterations;
    double highest_H_weight;
    double lowest_H_weight;
    //methods
    void compare( HSQC_Data& spec_L , HSQC_Data& spec_R );
    void iterated_compare( HSQC_Data& spec_L , HSQC_Data& spec_R );
    bool check_add_edge();
    void clear_file();
    void edge_to_network_file();
};




#endif
