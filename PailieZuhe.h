#pragma once
#ifndef __PAILIEZUHE_H_
#define __PAILIEZUHE_H_
#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<vector>
#include<algorithm>
#include<string.h>
#include<math.h>
using namespace std;

void Zuhe(vector<int> &Tmp_Box, int number = 3);
void Pailie_All(vector<int> &Tmp_Box);//枚举法全排列
void Pailie_Zuhe_All(vector<int> &Tmp_Box, int number = 3);//获得所有的组合排列情况
vector<int> Pailie_Zuhe_Random(vector<int> &Random, int m = 9, int n = 9);//随机获得一种组合情况

#endif
