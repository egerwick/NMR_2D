#ifndef __Similarity_Algo_H
#define __Similarity_Algo_H

#include "NPoint.H"

struct NLink
{
public:
    double dis;
    NPoint<double>* i_label;
    NPoint<double>* j_label;
};


class Similarity_Algo
{

private:
    HSQC_Data* m_ptr_L;
    HSQC_Data* m_ptr_R;
    std::vector<double> m_distance_dist;
    void start_diagnositcs();
    void show_diagnositcs();
    void arrange_prepare_samples(HSQC_Data& spec_smaller , HSQC_Data& spec_larger);
    int index_of_closest_point(NPoint<double> rhs, HSQC_Data& spec_larger);
    double get_distance(NPoint<double> rhs, NPoint<double> lhs);
    void comparator_copy(std::vector<NLink>& nlinks);

public:
    double weight_C ;
    double weight_H ;
    double pt_threshold;
    void fill_distance_distribution(HSQC_Data spec_smaller , HSQC_Data spec_larger);
    double correlation_from_distance(int total_number_peaks);

};


#endif
