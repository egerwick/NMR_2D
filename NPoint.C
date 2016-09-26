#ifndef __NPointC
#define __NPointC


#include <iostream>
#include <string>
#include <math.h>
#include "NPoint.H"

using namespace std;


template<typename _Tp> inline NPoint<_Tp>::NPoint() : H(0), C(0), H_op(0) {}
template<typename _Tp> inline NPoint<_Tp>::NPoint(_Tp _H, _Tp _C, _Tp _H_op) : H(_H), C(_C), H_op(_H_op) {}
template<typename _Tp> inline NPoint<_Tp>& NPoint<_Tp>::operator = (const NPoint& pt)
{
    H = pt.H;
    H_op = pt.H_op;
    C = pt.C;
    return *this;
}

template<typename _Tp> inline double NPoint<_Tp>::dot(const NPoint& pt) const
{
    return (double)H*pt.H + (double)C*pt.C;
}

template<typename _Tp> inline void NPoint<_Tp>::clear()
{
    H = 0;
    H_op = 0;
    C = 0;
}

template<typename _Tp> inline bool NPoint<_Tp>::exists()
{
    if(H == 0 && H_op == 0 && C == 0)
    {
        return false;
    }
    return true;

}


#endif