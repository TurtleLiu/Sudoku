#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<algorithm>
#include<iostream>
#include<vector>
#include<math.h>
#include"generator.h"
#include "CheckRepete.h"
using namespace std;

extern vector<vector<int>> arrange;
int main(int argc, char** argv)
{
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
				N = N + (argv[2][i] - '0') * pow(10, (strlen(argv[2]) - i - 1));
		}
		if (N < 0 || N>1000000)
		{
			printf("Overflow!\n");//非法输入（越界）
			return -2;
		}
		int sudo[9][9];
		Sudo_Generator(N, sudo);
	}
	else if (strcmp(argv[1], "-s") == 0)//解数独
	{

	}
	else if (strcmp(argv[1], "-c") != 0 && strcmp(argv[1], "-s") != 0)
	{
		printf("Wrong Input!\n");
		return -3;
	}
	return 0;
}
