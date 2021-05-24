#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <cstdlib>

void show_vector(std::vector<std::vector<double>> &vec);
void show_vector(std::vector<double> &vec);

void doolitle_method(int n, std::vector<std::vector<double>> &vec, std::vector<std::vector<double>> &vecL, std::vector<std::vector<double>> &vecU);

std::vector<double> EQ_solve(int n, std::vector<std::vector<double>> &vecLU, std::vector<double> &vecB) 
{
    std::vector<double> vecX;
    vecX.resize(n);
    double sum = 0;
    vecX[0] = vecB[0];

    for (int i = 1; i < n; ++i) 
    {
        sum = 0;
        for (int j = 0; j <= i-1; ++j) 
        {
            sum += (double)vecLU[i][j] * (double)vecX[j];

        }
        vecX[i] = vecB[i] - sum;
    }

    if (vecLU[n - 1][n - 1] == 0)
    {
        return vecX;
    }

    vecX[n-1] /= vecLU[n-1][n-1];

    for (int i = n - 2; i >= 0; --i) 
    {
        sum = 0;
        for (int j = i + 1; j < n; ++j) 
        {
            sum += (double)vecLU[i][j] * (double)vecX[j];
        }
        vecX[i] = (double)(vecX[i] - sum) / (double)vecLU[i][i];
    }

    return vecX;
}

std::vector<std::vector<double>> LU_merge(int n, std::vector<std::vector<double>> &vecL, std::vector<std::vector<double>> &vecU) 
{
    std::vector<std::vector<double>>vecLU;
    vecLU.resize(n);

    for (int i = 0; i < n; ++i) 
    {
        vecLU[i].resize(n);

        for (int j = 0; j < n; ++j)
        {

            if (j >= i)
                vecLU[i][j] = vecU[i][j];
            else
                vecLU[i][j] = vecL[i][j];
        }
    }
    return vecLU;
}

int main()
{
    //main variables
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
    std::cout<<"\nFree B variable \n";
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

    //Dolitle Method 
    doolitle_method(n,eq,L,U);
    std::cout<<"\n Lower Triangular:  \n";
    show_vector(L);
    std::cout<<"\n Upper Triangular:  \n";
    show_vector(U);

    //Merge LU 
    std::vector<std::vector<double>> vec_merge_LU;
    vec_merge_LU = LU_merge(n,L,U);

    //Solve
    std::vector<double> vec_final = EQ_solve(n, vec_merge_LU, free_eq);
    std::cout << "\nSolution of a system of equations\n";
    for (int i = 0; i < n; ++i)
    {
        std::cout << "x("<< i+1 << ") = "<<vec_final[i] << std::endl;
    }

    return 0;
}




void show_vector(std::vector<std::vector<double>> &vec)
{
    for(auto i : vec)
    {
        for(auto k : i)
        {
            std::cout<<std::setw(10)<<k<<" ";
        }
        std::cout<<std::endl;
    }
    std::cout<<"\n\n";
}

void show_vector(std::vector<double> &vec)
{
    for(auto i : vec)
    {
        std::cout<<std::setw(10)<<i<<" \n";
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