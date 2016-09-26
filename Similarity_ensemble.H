#ifndef __Similarity_ensemble_H
#define __Similarity_ensemble_H


class Similarity_ensemble: public Similarity: public Similarity_Algo
{
private:
    std::vector<double> m_corr_vec;

public:
    Similarity_ensemble();
    ~Similarity_ensemble();
    int corr_iterations;
    void ensemble_compare( HSQC_Data& spec_L , HSQC_Data& spec_R );

};




#endif
