#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<algorithm>
#include<iostream>
#include<vector>
#include<math.h>
#include"Solve.h"
#include "CheckRepete.h"
#include"generator.h"
#include "Display.h"
#include "PailieZuhe.h"

using namespace std;

extern vector<vector<int>> arrange;
extern vector<vector<int>> zuhe;


char ch;
char x[83];
int main(int argc, char** argv)
{
	//clock_t start = clock();
	srand((int)time(0));//根据时间生成随机数独
	freopen("sudoku.txt", "w", stdout);
	/*输入检验*/
	if (strcmp(argv[1], "-c") == 0)//生成数独终局
	{
		int N = 0;
		for (int i = 0; i < strlen(argv[2]); i++)
		{
			if (argv[2][i] < 48 || argv[2][i] > 57)
			{
				printf("Wrong Input!\n");//非法输入（错误字符）
				return -1;
			}
			else
			{
				N = N + (argv[2][i] - '0') * pow(10, (strlen(argv[2]) - i - 1));
				if (N < 0 || N>1000000)
				{
					printf("Overflow!\n");//非法输入（越界）
					return -2;
				}
			}
		}
		int sudo[9][9];
		Generator(N, sudo);
	}
	else if (strcmp(argv[1], "-s") == 0)//解数独
	{
		int tot = 0;
		freopen(argv[2], "r", stdin);
		while ((ch=getchar())!=EOF)
		{
			if (ch < '0' || ch > '9')
				continue;
			x[tot++] = ch;
			if (tot == 81)
			{
				SolveSudo(x);
				tot = 0;
			}
		}
	}
	else if (strcmp(argv[1], "-c") != 0 && strcmp(argv[1], "-s") != 0)//错误参数
	{
		printf("Wrong Input!\n");
		return -3;
	}
	//clock_t ends = clock();
	//cout << "Running Time : " << (double)(ends - start) / CLOCKS_PER_SEC << endl;
	return 0;
}
