#ifndef __NPointH
#define __NPointH


template<typename _Tp> class NPoint
{
public:
    typedef _Tp value_type;
    // various constructors
    NPoint();
    NPoint(_Tp _C, _Tp _H, _Tp _H_op);
    void clear();
    NPoint& operator = (const NPoint& pt);
    double dot(const NPoint& pt) const;
    _Tp H, C, H_op;
    bool exists();
};

#endif