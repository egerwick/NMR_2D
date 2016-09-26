#ifndef __Base_H
#define __Base_H
#define debugM if(Base::debugging_mode == 1)
#define debugSM if(Base::debugging_mode == 2)

using namespace std;
class Base
{
private:


public:
    Base();
    ~Base();
    static int debugging_mode;
    std::string in_path;
    std::vector<string> in_files = std::vector<string>();
    std::string out_path;
    std::string out_file;
    int num_files()
    {
        return in_files.size();
    }
    void get_files();

};




#endif
