#include<iostream>
#include<fstream>
using namespace std;
int main()
{
    ofstream fout;
    fout.open("redundance_code.h");
    fout<<"#define generate_1000000_redundance_code \\"<<endl;
    for(int i=0;i<999999;i++)
    {
        fout<<"    redundance_code();  \\"<<endl;
    }
    fout<<"    redundance_code();"<<endl;
    fout<<"inline void redundance_code()"<<endl;
    fout<<"{";
    fout<<endl;
    fout<<"    volatile int a=0;"<<endl;
    fout<<"    a++;"<<endl;
    fout<<"}";
}