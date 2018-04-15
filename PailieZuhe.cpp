#include "PailieZuhe.h"
#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<vector>
#include<algorithm>
#include<string.h>
#include<math.h>
using namespace std;

vector<int> vec;
vector<vector<int>> arrange;
vector<vector<int>> zuhe;

void Zuhe(vector<int> &Tmp_Box, int number)//回溯法找出所有组合
{
	if (number == 0)
		return;
	int count = 0;
	vector<int> C_Box;
	C_Box.assign(Tmp_Box.begin(), Tmp_Box.end());

	while (count != Tmp_Box.size())//从最大，次大，......依次寻找组合
	{
		vec.push_back(C_Box.back());
		C_Box.pop_back();
		Zuhe(C_Box, number - 1);
		if (number == 1)
			zuhe.push_back(vec);
		vec.pop_back();
		count++;
	}
}

void Pailie_All(vector<int> &Tmp_Box)//回溯法全排列，依次以最小，次小.....开头
{
	int size = Tmp_Box.size();
	if (size == 0)
		return;
	vector<int> C_Box;
	for (int i = 0; i < size; i++)
	{
		if (i > 0)
		vec.pop_back();
		C_Box.assign(Tmp_Box.begin(), Tmp_Box.end());
		vec.push_back(C_Box[i]);
		C_Box.erase(C_Box.begin() + i);
		Pailie_All(C_Box);
	}
	if(C_Box.empty())
	arrange.push_back(vec);
	vec.pop_back();
}

void Pailie_Zuhe_All(vector<int>&Tmp_Box, int number)//列举所有排列组合情况
{
	//清零
	arrange.clear();
	zuhe.clear();
	if (Tmp_Box.size() > number)
	{
		Zuhe(Tmp_Box);
		for (int i = 0; i < zuhe.size(); i++)
			Pailie_All(zuhe[i]);
	}
	else
		Pailie_All(Tmp_Box);
}

vector<int> Pailie_Zuhe_Random(vector<int> &Random, int m, int n)//获得一组随机排列组合
{
	int count = 0;
	int random_number;
	vector<int>C_Box;
	if (m == n)
		C_Box.assign(Random.begin(), Random.end());
	while (count != n&&n != m&&Random.size() != 0)
	{
		random_number = rand() % Random.size();
		C_Box.push_back(Random[random_number]);
		Random.erase(Random.begin() + random_number);
		count++;
	}
	vector<int> perm;
	while (!C_Box.empty())
	{
		random_number = rand() % C_Box.size();
		perm.push_back(C_Box[random_number]);
		C_Box.erase(C_Box.begin() + random_number);
	}

	return perm;
}
