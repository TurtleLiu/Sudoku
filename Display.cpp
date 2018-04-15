#include "Display.h"
#include<stdio.h>
#include<iostream>
using namespace std;

void display(int(*sudo)[9])
{
	char output[20];
	for (int i = 0; i < 9; i++)
	{
		int num = 0;
		output[num++] = sudo[i][0]+'0';
		for (int j = 1; j < 9; j++)
		{
			output[num++] = ' ';
			output[num++] = sudo[i][j]+'0';
		}
		output[num] = '\0';
		puts(output);
	}
	printf("\n");
}
