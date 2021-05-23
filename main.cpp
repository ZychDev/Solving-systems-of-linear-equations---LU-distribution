#include<iostream>
#include<vector>
#include<fstream>

int main()
{
    //file check
    std::ifstream my_file("sample.txt");
    
    try{
        bool check = true;
        if(my_file.is_open())
        {   
            std::cout<<"file is ok"<<std::endl;
        }
        else
        {
            check = false;
            throw(check);
        }
    }
    catch(bool my_check)
    {
        std::cout<<"Wrong input file"<<std::endl;
    }
    

    return 0;
}