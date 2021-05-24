#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <cstdlib>

void show_vector(std::vector<std::vector<double>> &vec)
{
    for(auto i : vec)
    {
        for(auto k : i)
        {
            std::cout<<std::setw(4)<<k<<" ";
        }
        std::cout<<std::endl;
    }
    std::cout<<"\n\n";
}

void show_vector(std::vector<double> &vec)
{
    for(auto i : vec)
    {
        std::cout<<i<<" \n";
    }
}

void doolitle_method(int n, std::vector<std::vector<double>> &vec, std::vector<std::vector<double>> &vecL, std::vector<std::vector<double>> &vecU) 
{
    for (int i = 0; i < n; ++i) 
    {
        if (vec[i][i] == 0) 
        {
            std::cout << "\nA divisor equal to '0' a distribution is impossible\n";
        }
        else 
        {
            for (int i = 0; i < n; ++i) 
            {
                for (int j = i; j < n; ++j) 
                {
                    double sum = 0;
                    for (int k = 0; k < i; ++k)
                    {
                        sum += ((double)vecL[i][k] * (double)vecU[k][j]);
                    }

                    vecU[i][j] = (double)vec[i][j] - (double)sum;
                }

                for (int j = i; j < n; ++j) 
                {
                    if (i == j)
                    {
                        vecL[i][i] = 1;  
                    }
                    else 
                    {
                        double sum = 0;
                        for (int k = 0; k <= i-1; ++k)
                        {
                            sum += ((double)vecL[j][k] * (double)vecU[k][i]);
                        }

                        vecL[j][i] = (((double)vec[j][i] - (double)sum) / (double)vecU[i][i]);
                    }
                }
            }
        }
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
    try
    {
        bool check = true;
        if(my_file.good())
        {   
            std::cout<<"File is ok\n"<<std::endl;

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
    }
    catch(bool my_check)
    {
        std::cout<<"Wrong input file"<<std::endl;
    }


    //show data
    show_vector(eq);  
    std::cout<<"\nNext data of free variables \n";
    show_vector(free_eq);

    //LU
    std::vector<std::vector<double>>L,U;
    L.resize(n);
    U.resize(n);

    for(int i = 0 ; i < n ; ++i)
    {
        L[i].resize(n);
        U[i].resize(n);
        for(int j = 0 ; j < n ; ++j)
        {
            L[i][j] = 0;
            U[i][j] = 0;
        }
    }

    doolitle_method(n,eq,L,U);
    show_vector(L);
    show_vector(U);

  




    return 0;
}