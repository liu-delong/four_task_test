#ifndef SOLUTION_H
#define SOLUTION_H
#include<string>
#include "sudoku.h"
using namespace std;


/********************ReadMe***********************/
/*
管理者会在一开始调用solutionInit进行初始化。会且只会调用一次。
管理者会开启一个线程，这个线程调用solve_problem函数解决问题。
并通过ProblemArgv向你传递参数，你的输出应该放在answer数组中。

下面这点非常非常重要！！！！
解答完成后，请在answer[81]处设置为1. 也就是answer[81]=1。告诉管理者这个已经完成计算。
上面这点非常非常重要！！！！

如果你在解决问题是要用多线程，请务必使用线程池。线程池已经使用单例模式设计。
使用方法如下(头文件已经为你准备好，不需要include其他东西)
    ThreadingPool* TP=ThreadingPool::getThreadPool();
    TP->addJob(yourfunction,yourargument);
    注意，yourfunction的函数必须是这样：void funcname(void *)
    你可以像我一样先把参数封装成一个类。
    同步资源（锁，条件变量等）都弄到这个类里。


你应该要在algorithm文件夹下新建.cpp文件，并include "solution.h",你不需要include"ThreadingPool.h",但你可以使用。
*/
/********************end**************************/


class ProblemArgv
{
    public:
    char* source;// 原来的数组。类型为char[82] 引索从0开始.  char[81]是标记位。
    char* answer;// 答案输出的位置。  是个char[83] 引索从0开始， char[81]固定为0,最后一个元素(char[82]一开始为0，完成计算后，你应该把它设置为source[81].
};

// 数独算法初始化，参数为算法名字。
bool solutionInit(string solution_name);
// 数独算法开始运行，参数为arg，但实际传入的是PromblemArgv(问题参数封装类）的指针（转化为void)。
// 在solve_problem的第一行写上通过PromblemArgv *argv=(PromblemArgv)arg解析参数。
// 使用时，用argv->source,argv->answer方式使用。
void solve_problem(void* arg);


#endif
