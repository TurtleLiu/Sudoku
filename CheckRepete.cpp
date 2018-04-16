#include "CheckRepete.h"
#include<iostream>
#include<vector>
using namespace std;

int seedku[10000][8];
int finalsudo = 0;

bool Check_Rep(const vector<int> &Seed_Box)
{
	for (int i = finalsudo - 1; i > -1; i--)
	{
		for (int j = 0, count = 8; j < 8; j++)
		{
			if (Seed_Box[j + 1] == seedku[i][j]) count--;
			else 
				break;
			if (count == 0) 
				return false;
		}
	}

	for (int i = 1; i < 9; i++)
		seedku[finalsudo][i - 1] = Seed_Box[i];

	finalsudo++;
	return true;
}

