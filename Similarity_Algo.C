#ifndef __Similarity_Algo_C
#define __Similarity_Algo_C

#include "Similarity_Algo.H"
#include "NPoint.C"
#include "Base.H"

//super private


bool comp_op(const NLink i, const NLink j)
{
    return (i.dis < j.dis);
}

void Similarity_Algo::fill_distance_distribution( HSQC_Data spec_smaller , HSQC_Data spec_larger )
{
    arrange_prepare_samples(spec_smaller , spec_larger);
    m_distance_dist.clear();
    std::vector<NLink> nlinks;
    NLink tmp;

    for(int i(0); i<spec_smaller.num_peaks(); i++)
    {
        for(int j(0); j<spec_larger.num_peaks(); j++)
        {
            tmp.dis = get_distance(spec_smaller.get_spec_point(i),spec_larger.get_spec_point(j));
            tmp.i_label = spec_smaller.get_spec_address(i);
            tmp.j_label = spec_larger.get_spec_address(j);
            nlinks.push_back(tmp);
        }
    }

    std::sort( nlinks.begin(), nlinks.end() , comp_op );

    for(size_t i(0); i<nlinks.size(); i++)
        debugSM cout << "after_sort " << nlinks[i].dis << " " << nlinks[i].i_label << " " << nlinks[i].j_label << endl;

    comparator_copy(nlinks);

    for(size_t i(0); i<m_distance_dist.size(); i++)
        debugM cout << "after_filter " << m_distance_dist[i] << endl;

    return;
}


void Similarity_Algo::comparator_copy(std::vector<NLink>& nlinks)
{
    //Comparator conditions
    NPoint<double> ci,cj;
    for(size_t i(0); i<nlinks.size(); i++)
    {
        ci = *nlinks[i].i_label;
        cj = *nlinks[i].j_label;
        if( nlinks[i].dis < pt_threshold && ci.exists() && cj.exists() )
        {
            m_distance_dist.push_back(nlinks[i].dis);
            nlinks[i].i_label->clear();
            nlinks[i].j_label->clear();
        }
    }
    return;
}


double Similarity_Algo::correlation_from_distance(int total_number_peaks)
{
    double result = 0.0;
    int num_matched_peaks = m_distance_dist.size();
    result = double( 2* num_matched_peaks )/( total_number_peaks );
    return result;
}


void Similarity_Algo::arrange_prepare_samples(HSQC_Data& spec_smaller , HSQC_Data& spec_larger)
{

    if( spec_smaller.num_peaks() > spec_larger.num_peaks() ) swap(spec_smaller,spec_larger);
    debugM start_diagnositcs();
    m_ptr_L = &spec_smaller;
    m_ptr_R = &spec_larger;
    show_diagnositcs();
    debugM cout << "num peaks: " << spec_smaller.num_peaks() << " " << spec_larger.num_peaks() << endl;

    NPoint<double> specS_size = spec_smaller.get_spectrum_size();
    NPoint<double> specL_size = spec_larger.get_spectrum_size();

    debugM cout <<  "Size: " << specS_size.C << "," << specS_size.H <<
                "  :  " << specL_size.C << "," << specL_size.H << endl;
    return;
}


int Similarity_Algo::index_of_closest_point(NPoint<double> rhs, HSQC_Data& spec_larger)
{
    int closest = 0;
    double m_dis=1e10;
    double c_dis=0;
    for(size_t i(0); i<spec_larger.num_peaks(); ++i)
    {
        c_dis = this->get_distance(rhs,spec_larger.get_spec_point(i));
        if(c_dis < m_dis)
        {
            m_dis = c_dis;
            closest = i;
        }
    }
    return closest;
}


double Similarity_Algo::get_distance(NPoint<double> rhs, NPoint<double> lhs)
{
    return sqrt(weight_C*pow(rhs.C - lhs.C,2) + weight_H*pow(rhs.H - lhs.H,2));
}


void Similarity_Algo::start_diagnositcs()
{
    std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
    std::cout << "comparison" << std::endl;
    std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
}


void Similarity_Algo::show_diagnositcs()
{
    m_ptr_L->HSQC_Data::print_to_term();
    m_ptr_R->HSQC_Data::print_to_term();
}



#endif
