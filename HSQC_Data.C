#ifndef __HSQC_Data_C
#define __HSQC_Data_C

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>
#include "HSQC_Data.H"
#include "Similarity.H"
#include "NPoint.C"

using namespace std;


HSQC_Data::HSQC_Data() {}
HSQC_Data::~HSQC_Data() {}

void HSQC_Data::read_from_file(const std::string path , const std::string filename)
{
    this->m_spectra_name = filename;
    remove_dot(this->m_spectra_name);
    NPoint<double> tmp;
    ifstream in( path+filename );
    std::string line;
    while (getline(in, line))
    {
        std::istringstream iss(line);
        iss >> tmp.C >> tmp.H >> tmp.H_op;
        tmp.H_op = fabs(tmp.H_op) > 1e-8 ? tmp.H_op : 0.0;
        this->m_spectra.push_back(tmp);
        tmp.clear();
    }
    in.close();
    return;
};

void HSQC_Data::assign_id(const int id)
{
    this->m_id = id;
    return;
};


void HSQC_Data::print_to_term()
{
    cout << this->m_spectra_name << std::endl;
    for(size_t i(0); i<this->m_spectra.size(); ++i)
    {
        debugSM cout << m_spectra[i].C << " " <<m_spectra[i].H << " ";
        if(m_spectra[i].H_op != 0) debugSM cout << m_spectra[i].H_op;
        debugSM cout << std::endl;
    }
    debugSM std::cout << std::endl;
    return;
};


NPoint<double> HSQC_Data::get_spectrum_size()
{
    NPoint<double> tmp, result;
    double max_C(0), max_H(0), min_C(1e10), min_H(1e10);
    for(size_t i(0); i<num_peaks(); ++i)
    {
        tmp = m_spectra[i];
        if(tmp.C > max_C) max_C = tmp.C;
        if(tmp.C < min_C) min_C = tmp.C;
        if(tmp.H > max_H) max_H = tmp.H;
        if(tmp.H < min_H) min_H = tmp.H;

    }


    result.C = max_C-min_C;
    result.H = max_H-min_H;

    return result;

}


void HSQC_Data::plot_spectrum()
{
    return;
}


void HSQC_Data::nodes_to_network_file(std::string arg)
{
    ofstream out;
    out.open(arg,ios::app);
    out << this->m_spectra_name << std::endl;
    out.close();
    return;
}


void remove_dot(std::string& arg)
{
    for(size_t i(0); i < arg.length(); ++i)
    {
        if(arg[i]=='.')
        {
            arg.erase (arg.begin()+i,arg.end());
            break;
        }
    }
    return;
}



#endif