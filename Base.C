#ifndef __Base_C
#define __Base_C
#include "Base.H"


Base::Base() {}
Base::~Base() {}

void Base::get_files()
{

    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(this->in_path.c_str())) == NULL)
    {
        cout << "Error(" << errno << ") opening " << this->in_path << endl;
        return;
    }
    int i = 0;
    while ((dirp = readdir(dp)) != NULL)
    {
        if(i>1) this->in_files.push_back(string(dirp->d_name));
        ++i;
    }
    closedir(dp);
    return;

};




#endif
