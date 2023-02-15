#include <iostream>
#include <thread>
#include <vector>
#include <random>
#include "solution.h"
#include "redundance_code.h"
#include <chrono>
using namespace std;
#define matrix_size 100
#define pow_time 1000
#define sudoku_size 7500
#define task1_core 0
#define task2_core 1
#define task3_core 0
#define task4_core 1
void generate(char* buf);
void task1_2_func()
{
    generate_10000_redundance_code
    //vector<vector<int>> matrix(matrix_size,vector<int>(matrix_size));
    default_random_engine e;
    uniform_real_distribution<double> u(0.0,1.0);
    generate_10000_redundance_code
    e.seed(time(0));
    volatile double a;
    for(int i=0;i<matrix_size;i++)
    {
        for(int j=0;j<matrix_size;j++)
        {
            a=u(e);
        }
    }
    generate_10000_redundance_code
    volatile double a1=0,b=u(e),c=u(e);
    for(int p=0;p<pow_time;p++)
    {
        //auto matrix1=matrix;
        //auto matrix2=matrix;
        for(int i=0;i<matrix_size;i++)
        {
            for(int j=0;j<matrix_size;j++)
            {
                
                for(int k=0;k<matrix_size;k++)
                {
                    a1+=b*c;
                }
            }
        }
    }
    generate_10000_redundance_code
}
void task3_4_func()
{
    generate_10000_redundance_code
    generate_10000_redundance_code
    char source[82];
    char answer[83];
    ProblemArgv argv={source,answer};
    generate_10000_redundance_code
    generate_10000_redundance_code
    for(int i=0;i<sudoku_size;i++)
    {
        generate(source);
        solve_problem((void*)&argv);
        // for(int i=0;i<9;i++)
        // {
        //     for(int j=0;j<9;j++)
        //     {
        //         printf("%c ",answer[i*9+j]);
        //     }
        //     printf("\n");
        // }
    }
    generate_10000_redundance_code
}
void tie_self_thread_to_cpu(int cpu_num)
{
    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(cpu_num, &mask); //指定该线程使用的CPU
    if (pthread_setaffinity_np(pthread_self(), sizeof(mask), &mask) < 0) 
    {
        perror("pthread_setaffinity_np");
    }
}
int main()
{
    thread t1([]{
        tie_self_thread_to_cpu(task1_core);
        task1_2_func();
        cout<<"task1 ok"<<endl;
    });
    thread t2([]{
        tie_self_thread_to_cpu(task2_core);
        task1_2_func();
        cout<<"task2 ok"<<endl;
    });
    thread t3([]{
        tie_self_thread_to_cpu(task3_core);
        task3_4_func();
        cout<<"task3 ok"<<endl;
    });
    thread t4([]{
        tie_self_thread_to_cpu(task4_core);
        task3_4_func();
        cout<<"task4 ok"<<endl;
    });
    t1.join();
    t2.join();
    t3.join();
    t4.join();

}
