#include<iostream>
#include<vector>
#include<fstream>

void show_vector(std::vector<std::vector<double>> &vec)
{
    for(auto i : vec)
    {
        for(auto k : i)
        {
            std::cout<<k<<" ";
        }
        std::cout<<std::endl;
    }
}

void show_vector(std::vector<double> &vec)
{
    for(auto i : vec)
    {
        std::cout<<i<<" \n";
    }
}

int main()
{
    //variables
    std::vector<std::vector<double>>eq;
    std::vector<double>free_eq;

    //file open
    std::ifstream my_file;
    int tmp = 0, n = 0;  
    my_file.open("sample.txt");

    //open error
    try{
        bool check = true;
        if(my_file.good())
        {   
            std::cout<<"file is ok\n"<<std::endl;

            //read data from file 
            my_file >> n;
            //resize 2d vector and free variable vector
            eq.resize(n);
            free_eq.resize(n);

            std::cout<<"Number of equations: "<<n<<std::endl;
            int temporary;

            for(int i  = 0 ; i < n ; ++i)
            {
                eq[i].resize(n);
                for(int j  = 0 ; j < n ; ++j)
                {
                    my_file >> eq[i][j];
                }
                my_file >> free_eq[i];
            }
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

    //show data
    show_vector(eq);  
    std::cout<<"\nNext data of free variables \n";
    show_vector(free_eq);

    return 0;
}