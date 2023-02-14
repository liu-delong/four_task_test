#include "solution.h"
#include <bits/stdc++.h>
using namespace std;
bool (*solve)(int,Sudoku*) = solve_sudoku_dancing_links;//默认解法为dancing_links
void solve_problem(void* arg){
	//初始化数组结构体
	Sudoku* sudo = new Sudoku;
	ProblemArgv* argv = (ProblemArgv*)arg;//接受参数
	init_neighbors(sudo);
	/***********求解过程start**********/
	input(argv->source,sudo);//传入问题
	//init_cache(sudo);
	if (solve(0,sudo)) {
		//这里调用solved()检验下是不是正确的解
		if (!solved(sudo))
			assert(0);
		//将结果传给answer
		int index = 0;
		for (int row = 0; row < ROW; ++row) {
			for (int col = 0; col < COL; ++col) {
				argv->answer[index++] = (sudo->chess[row][col])+'0';
		  	}
		}
		argv->answer[81] = '\0';
		argv->answer[82] =argv->source[81];
	  }
	else{
		//3表示无解,4表示最后一行且无解
		memcpy(argv->answer,argv->source,81);
		argv->answer[82] = 2 + argv->source[81];
	}
  /***********求解过程end**********/
	delete sudo;
	return;
}


//默认为basic
bool solutionInit(string solution_name){
	if(solution_name == "d")
		solve = solve_sudoku_dancing_links;
	else 
	{
		printf("算法名称错误\n");
		return false;
	}
	return true;
}