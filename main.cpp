#include<iostream>
#include<random>
#include<thread>
#include <mutex>
#include<cstdio>
#include <chrono>
#include<string>
using namespace std;
using namespace std::chrono;
#define matrix_size 1000
#define mul_time_1 20
#define mul_time_2 10
double matrixA1[matrix_size][matrix_size];
double matrixB1[matrix_size][matrix_size];
double matrixA2[matrix_size][matrix_size];
double matrixB2[matrix_size][matrix_size];
std::mutex print_mutex;
/*
把当前线程绑定到@cpu_num中。cpu_num从0开始引索
*/
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
void matrix_mul(int cpu,string task_name,int mul_time)
{
    tie_self_thread_to_cpu(cpu);
    auto begin=high_resolution_clock::now();
    volatile double c=0;
    for(int p=0;p<mul_time;p++)
    {
        for(int i=0;i<matrix_size;i++)
        {
            for(int j=0;j<matrix_size;j++)
            {
                for(int k=0;k<matrix_size;k++)
                {
                    c+=matrixA1[i][k]*matrixB1[k][i];
                }
            }
        }
    }
    auto end=high_resolution_clock::now();
    print_mutex.lock();
    printf("%s,%d,%d,%d,%ld\n ",task_name.c_str(),cpu,matrix_size,mul_time,(end-begin).count());
    print_mutex.unlock();
}


int main(int argc,char** argv)
{
    uniform_real_distribution<double> u(0,100);
    default_random_engine e;
    e.seed(time(0));
    int task_1_cpu=0,task_2_cpu=2,task_3_cpu=0,task_4_cpu=2;
    if((argc==2)&&string(argv[1])=="bujunheng")
    {
        task_1_cpu=0;
        task_2_cpu=0;
        task_3_cpu=2;
        task_4_cpu=2;
    }
    for(int i=0;i<matrix_size;i++)
    {
        for(int j=0;j<matrix_size;j++)
        {
            matrixA1[i][j]=u(e);
            matrixB2[i][j]=u(e);
            matrixB1[i][j]=u(e);
            matrixA2[i][j]=u(e);
        }
    }
    thread t1_matrix_mul(matrix_mul,task_1_cpu,"task_1_matrix_mul:",mul_time_1);
    thread t2_matrix_mul(matrix_mul,task_2_cpu,"task_2_matrix_mul:",mul_time_1);
    thread t3_matrix_mul(matrix_mul,task_3_cpu,"task_3_matrix_mul:",mul_time_2);
    thread t4_matrix_mul(matrix_mul,task_4_cpu,"task_4_matrix_mul:",mul_time_2);
    t1_matrix_mul.join();
    t2_matrix_mul.join();
    t3_matrix_mul.join();
    t4_matrix_mul.join();
}
