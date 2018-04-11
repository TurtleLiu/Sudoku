/*
DLX解决9*9的数独问题，转化为729*324的精确覆盖问题
行：
一共9 * 9 * 9 == 729行。一共9 * 9小格，每一格有9种可能性(1 - 9)，每一种可能都对应着一行。
列：
一共(9 + 9 + 9) * 9 + 81 == 324 种前面三个9分别代表着9行9列和9小块，乘以9的意思是9种可能(1 - 9)，因为每种可能只可以选择一个。
81代表着81个小格，限制着每一个小格只放一个数字。
读入数据后，如果为'.'，则建9行，即有1-9种可能，否则建一行，表示某小格只能放确定的某个数字。
*/
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int INF = 0x7fffffff;
const int NN = 350;
const int MM = 750;
#define N 9
int n, m;    //列，行
int cntc[NN];
int L[NN*MM], R[NN*MM], U[NN*MM], D[NN*MM];//节点的左边，右边，上边，下边
int C[NN*MM];
int head;
int mx[MM][NN];
int O[MM], idx;
int ans[10][10];

//删除列及其相应的行
void remove(int c)
{
	int i, j;
	L[R[c]] = L[c];
	R[L[c]] = R[c];
	for (i = D[c]; i != c; i = D[i])
	{
		for (j = R[i]; j != i; j = R[j])
		{
			U[D[j]] = U[j];
			D[U[j]] = D[j];
			cntc[C[j]]--;
		}
	}
}

//恢复列及其相应的行
void resume(int c)
{
	int i, j;
	R[L[c]] = c;
	L[R[c]] = c;
	for (i = D[c]; i != c; i = D[i])
	{
		for (j = R[i]; j != i; j = R[j])
		{
			U[D[j]] = j;
			D[U[j]] = j;
			cntc[C[j]]++;
		}
	}
}

bool dfs()
{
	int i, j, c;
	if (R[head] == head)
		return true;
	int min = INF;
	for (i = R[head]; i != head; i = R[i])
	{
		if (cntc[i] < min)
		{
			min = cntc[i];
			c = i;
		}
	}
	remove(c);
	for (i = D[c]; i != c; i = D[i])
	{
		//i是某点的序号，将该点所在行的行号保存
		O[idx++] = (i - 1) / n;
		for (j = R[i]; j != i; j = R[j])
			remove(C[j]);
		if (dfs())
			return true;
		for (j = L[i]; j != i; j = L[j])
			resume(C[j]);
		idx--;
	}
	resume(c);
	return false;
}

int build()
{
	int i, j, now, pre, first;
	idx = head = 0;
	for (i = 0; i < n; i++)
	{
		R[i] = i + 1;
		L[i + 1] = i;
	}
	R[n] = 0;
	L[0] = n;
	//列双向链表
	for (j = 1; j <= n; j++)
	{
		pre = j;
		cntc[j] = 0;
		for (i = 1; i <= m; i++)
		{
			if (mx[i][j])
			{
				cntc[j]++;//j的边数
				now = i*n + j;
				C[now] = j;//C为列指针
				D[pre] = now;
				U[now] = pre;
				pre = now;
			}
		}
		U[j] = pre;
		D[pre] = j;
		if (cntc[j] == 0)
			return 0;
	}
	//行双向链表
	for (i = 1; i <= m; i++)
	{
		pre = first = -1;
		for (j = 1; j <= n; j++)
		{
			if (mx[i][j])
			{
				now = i*n + j;
				if (pre == -1)
					first = now;
				else
				{
					R[pre] = now;
					L[now] = pre;
				}
				pre = now;
			}
		}
		if (first != -1)
		{
			R[pre] = first;
			L[first] = pre;
		}
	}
	return 1;
}

int T;

void print()
{
	int i, j;
	int x, y, k;
	for (i = 0; i < idx; i++)
	{
		int r = O[i];
		k = r % 9;
		if (k == 0) k = 9;
		int num = (r - k) / 9 + 1;
		y = num % 9;
		if (y == 0) y = 9;
		x = (num - y) / 9 + 1;
		ans[x][y] = k;
	}
	if (idx == 0)
		printf("impossible\n\n");
	else
	{
		for (int i = 1; i < 10; i++)
		{
			printf("%d", ans[i][1]);
			for (int j = 2; j < 10; j++)
				printf(" %d", ans[i][j]);
			printf("\n");
		}
		printf("\n");
	}
	
}

int map[MM][NN];
void SolveSudo(char x[83])
{
	int i, j, k;
	int cases;
	char cao[12];
	char s[12][12];
	char ch;
	int ind = 0;
	memset(mx, 0, sizeof(mx));
	for (int i = 1; i <=N; i++)
	for (int j = 1; j <= N; j++)
			{
				ch = x[ind++];
				map[i][j] = ch - '0';
			}
	for (i = 1; i <= 9; i++)
		{
	for (j = 1; j <= 9; j++)
			{
				int t = (i - 1) * 9 + j;
				if (map[i][j] == 0)
				{
					for (k = 1; k <= 9; k++)
					{
						mx[9 * (t - 1) + k][t] = 1;               //81grid 每个小格只能放一个数字
						mx[9 * (t - 1) + k][81 + (i - 1) * 9 + k] = 1;    //9row 每行数字k只能出现一次
						mx[9 * (t - 1) + k][162 + (j - 1) * 9 + k] = 1;   //9col  每列数字k只能出现一次
						mx[9 * (t - 1) + k][243 + ((i - 1) / 3 * 3 + (j + 2) / 3 - 1) * 9 + k] = 1;   //subgrid 每个3*3格子数字k只能出现一次
					}
				}
				else
				{
					k = map[i][j];
					mx[9 * (t - 1) + k][t] = 1;               //81grid
					mx[9 * (t - 1) + k][81 + (i - 1) * 9 + k] = 1;    //9row
					mx[9 * (t - 1) + k][162 + (j - 1) * 9 + k] = 1;   //9col
					mx[9 * (t - 1) + k][243 + ((i - 1) / 3 * 3 + (j + 2) / 3 - 1) * 9 + k] = 1;   //subgrid
				}
			}
		}
		n = 324;
		m = 729;
		build();
		dfs();
		print();
	
}
