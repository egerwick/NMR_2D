#ifndef __HSQC_Data_H
#define __HSQC_Data_H

#include <iostream>
#include <string>
#include <vector>
#include "NPoint.H"
#include "Base.H"
using namespace std;

class HSQC_Data: public Base
{

private:
    std::vector < NPoint<double> > m_spectra;
    std::string m_spectra_name;
    int m_id;

public:
    HSQC_Data();
    ~HSQC_Data();
    void read_from_file(const std::string path, const std::string filename);
    void assign_id(int id);
    NPoint<double> get_spectrum_size();
    void print_to_term();
    void nodes_to_network_file(std::string arg);
    void plot_spectrum();
    int get_id()
    {
        return m_id;
    }
    NPoint<double> get_spec_point(int i)
    {
        return m_spectra[i];
    }
    NPoint<double>* get_spec_address(int i)
    {
        return &m_spectra[i];
    }
    std::string get_name()
    {
        return m_spectra_name;
    }
    int num_peaks()
    {
        return this->m_spectra.size();
    }

};
void remove_dot(std::string& arg);

#endif

