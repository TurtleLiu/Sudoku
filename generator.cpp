#include"generator.h"
#include "CheckRepete.h"
#include"Display.h"
#include "PailieZuhe.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<algorithm>
#include<iostream>
#include<vector>
#include<math.h>
#include<time.h>

using namespace std;

extern vector<vector<int>> arrange;

void Get_Seedbox(vector<int> &Seed_Box)//随机生成开头为5的3x3种子宫
{
	Seed_Box = Pailie_Zuhe_Random(Seed_Box);
	for (int i = 0; i < 9; i++)
	{
		if (Seed_Box[i] == 5)
		{
			swap(Seed_Box[i], Seed_Box[0]);
			break;
		}
	}

}
void Set_Sudo(int(*sudo)[9], const vector<int> &Seed_Box, int count)//初始化函数
{
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			sudo[i][j] = 0;

	for (int i = 0, k = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			sudo[i][j] = Seed_Box[k++];

	sudo[0][3] = arrange[count][0];
	sudo[0][4] = arrange[count][1];
	sudo[0][5] = arrange[count][2];
}
void Generator(int N, int(*sudo)[9])
{
	vector<int> Seed_Box;
	vector<int> Tmp_Box;

	for (int i = 0; i < 9; i++)
		Seed_Box.push_back(i + 1);

	while (N != 0)
	{
		Get_Seedbox(Seed_Box);
		if (!Check_Rep(Seed_Box))//检验重复性
			continue;

		Tmp_Box.assign(Seed_Box.begin() + 3, Seed_Box.end());//获取第一宫第一行前三个外的6个数字,生成所有唯一的A(6,3)
		Pailie_Zuhe_All(Tmp_Box);
		int count = 0;

		while (N != 0)
		{
			if (count < 120)
				Set_Sudo(sudo, Seed_Box, count++);
			else
				break;

			for (int i = 1; i < 3; i++)//生成第二宫的第二行和第三行
			{
				Tmp_Box.assign(Seed_Box.begin(), Seed_Box.end());//删除同行在第一宫的三个数
				Tmp_Box.erase(Tmp_Box.begin() + i * 3);
				Tmp_Box.erase(Tmp_Box.begin() + i * 3);
				Tmp_Box.erase(Tmp_Box.begin() + i * 3);

				for (int j = 0; j < Tmp_Box.size(); j++)//删除已排序的数
					if (Tmp_Box[j] == sudo[0][3] || Tmp_Box[j] == sudo[0][4] || Tmp_Box[j] == sudo[0][5] ||
						Tmp_Box[j] == sudo[1][3] || Tmp_Box[j] == sudo[1][4] || Tmp_Box[j] == sudo[1][5])
						Tmp_Box.erase(Tmp_Box.begin() + (j--));
				/*第二行时只删了三个，多删三个*/
				if (Tmp_Box.size() == 6)
					Tmp_Box.erase(Tmp_Box.begin());
				if (Tmp_Box.size() == 5)
					Tmp_Box.erase(Tmp_Box.begin());
				if (Tmp_Box.size() == 4)
					Tmp_Box.erase(Tmp_Box.begin());

				Tmp_Box = Pailie_Zuhe_Random(Tmp_Box, Tmp_Box.size(), 3);//由于A（6,3）的唯一性，第二宫剩下的行任意生成一种排法即可
				sudo[i][3] = Tmp_Box[0];
				sudo[i][4] = Tmp_Box[1];
				sudo[i][5] = Tmp_Box[2];
			}
			for (int i = 0; i < 3; i++)//生成第三宫
			{
				Tmp_Box.assign(Seed_Box.begin(), Seed_Box.end());
				for (int j = 0; j < Tmp_Box.size(); j++)//删除第一二宫同行的数
					if (Tmp_Box[j] == sudo[i][0] || Tmp_Box[j] == sudo[i][1] || Tmp_Box[j] == sudo[i][2] ||
						Tmp_Box[j] == sudo[i][3] || Tmp_Box[j] == sudo[i][4] || Tmp_Box[j] == sudo[i][5])
						Tmp_Box.erase(Tmp_Box.begin() + (j--));
				Tmp_Box = Pailie_Zuhe_Random(Tmp_Box, 3, 3);//由于A（6,3）的唯一性，第二宫剩下的行任意生成一种排法即可
				sudo[i][6] = Tmp_Box[0];
				sudo[i][7] = Tmp_Box[1];
				sudo[i][8] = Tmp_Box[2];
			}
			for (int i = 3; i < 9; i++)//余下所有宫格由种子宫交替生成
			{
				for (int j = 0; j < 9; j++)
				{
					if (j == 2 || j == 5 || j == 8)
						sudo[i][j] = sudo[i - 3][j - 2];
					else
						sudo[i][j] = sudo[i - 3][j + 1];
				}
			}
			display(sudo);//输出终局
			N--;
		}
	}
}
