#ifndef __Similarity_C
#define __Similarity_C
#include "HSQC_Data.H"
#include "Similarity.H"
#include "Similarity_Algo.C"
#include "Edge.H"
#include <fstream>

Similarity::Similarity() {};
Similarity::~Similarity() {};


void Similarity::iterated_compare( HSQC_Data& spec_L , HSQC_Data& spec_R )
{
    //set the weight
    get_H_weights();
    for(size_t i(0); i<number_iterations; ++i)
    {
        weight_H = H_weights[i];
        compare(spec_L,spec_R);
        m_corr_vec.push_back(m_corr);
    }
    return;
}

void Similarity::get_H_weights()
{
    for(size_t i(0); i<number_iterations; ++i)
    {
        H_weights.push_back(lowest_H_weight+i*(highest_H_weight-lowest_H_weight)/number_iterations);
    }
    return;
};


void Similarity::compare( HSQC_Data& spec_L , HSQC_Data& spec_R )
{
    this->m_node_name_L = spec_L.get_name() ;
    this->m_node_name_R = spec_R.get_name() ;
    this->m_L = spec_L.get_id() ;
    this->m_R = spec_R.get_id() ;

    //insert comparson algorithm
    fill_distance_distribution(spec_L,spec_R);
    this->m_corr = correlation_from_distance( spec_L.num_peaks() + spec_R.num_peaks() );
    cout << "correlation: " << this->m_corr << endl;
    cout << endl;
    return;
}


bool Similarity::check_add_edge()
{
    return (this->m_corr > this->edge_thresh) ? true : false;
}


void Similarity::clear_file()
{
    remove( (this->path + this->filename).c_str() );
    //string()
}


void Similarity::edge_to_network_file()
{
    ofstream out;
    out.open( this->path+this->filename, ios::app );
    out << this->m_node_name_L << " " << this->m_node_name_R  << " " << this->m_corr << std::endl;
    out.close();
}



#endif






