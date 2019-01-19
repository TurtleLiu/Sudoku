/*
DLX解决9*9的数独问题，转化为729*324的精确覆盖问题
行：测试测试！！！！！
一共9 * 9 * 9 == 729行。一共9 * 9小格，每一格有9种可能性(1 - 9)，每一种可能都对应着一行。
列：
一共(9 + 9 + 9) * 9 + 81 == 324 种前面三个9分别代表着9行9列和9小块，乘以9的意思是9种可能(1 - 9)，因为每种可能只可以选择一个。
81代表着81个小格，限制着每一个小格只放一个数字。
读入数据后，如果为'0'，则建9行，即有1-9种可能，否则建一行，表示某小格只能放确定的某个数字。
*/
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;

const int MAX = 1000;
const int oo = 0x3f3f3f3f;
const int nC = 9 * 9 * 4;
const int delta[] = { 1,82,163,244 };
const int head = 0;

int cnt[MAX], st[MAX];
int left[MAX*MAX], right[MAX*MAX], up[MAX*MAX], down[MAX*MAX];//节点的左边，右边，上边，下边
int row[MAX*MAX], col[MAX*MAX];
struct Ans
{
	int r, c, k;
}ans[MAX*MAX];
int M, K;

void remove(const int& c)//删除列及其相应的行
{
	left[right[c]] = left[c];
	right[left[c]] = right[c];
	for (int i = down[c]; i != c; i = down[i])
		for (int j = right[i]; j != i; j = right[j])
		{
			up[down[j]] = up[j];
			down[up[j]] = down[j];
			cnt[col[j]]--;
		}
}

void resume(const int& c)//恢复列及其相应的行
{
	for (int i = up[c]; i != c; i = up[i])
		for (int j = left[i]; j != i; j = left[j])
		{
			down[up[j]] = j;
			up[down[j]] = j;
			cnt[col[j]]++;
		}
	left[right[c]] = c;
	right[left[c]] = c;
}

bool dfs(const int& k)//深搜求解
{
	if (right[head] == head)//已经选够
	{
		char s[100] = { 0 };
		char output[20];
		for (int i = 0; i<k; i++)
			s[ans[st[i]].r * 9 + ans[st[i]].c] = ans[st[i]].k + '0';//s[行*9+列]
		int count = 0;
		for (int i = 0; i < 9; i++)
		{
			int num = 0;
			output[num++] = s[count++];
			for (int j = 1; j < 9; j++)
			{
				output[num++] = ' ';
				output[num++] = s[count++];
			}
			output[num] = '\0';
			puts(output);
		}
		printf("\n");
		return true;
	}
	//遍历列标元素，选一个元素最少的列（回溯率低）
	int s = oo, c = 0;
	for (int i = right[head]; i != head; i = right[i])
		if (cnt[i]<s)
		{
			s = cnt[i];
			c = i;
		}

	remove(c);//选好就移除
	//遍历该列各“1”元素
	for (int i = down[c]; i != c; i = down[i])
	{
		st[k] = row[i];
		for (int j = right[i]; j != i; j = right[j]) // 移除与该元素同行元素的列
			remove(col[j]);
		if (dfs(k + 1))// 已选行数+1，递归调用
			return true;
		for (int j = left[i]; j != i; j = left[j])// 递归返回false，说明后续无法满足，故恢复与该元素同行元素的列，循坏进入本列下一元素
			resume(col[j]);
	}
	resume(c);//所有后续都无法满足，恢复

	return false;
}

void Initial()//初始化函数
{
	left[head] = nC;
	right[head] = 1;
	up[head] = down[head] = head;
	for (int i = 1; i <= nC; i++)
	{
		left[i] = i - 1;
		right[i] = (i + 1) % (nC + 1);
		up[i] = down[i] = i;
		cnt[i] = 0;
		col[i] = i;
		row[i] = 0;
	}
	M = 0;
	K = nC;
}

int makecolhead(const int& c)//建立链表
{
	K++;
	cnt[c]++;
	col[K] = c;
	row[K] = M;

	left[K] = right[K] = K;

	up[K] = c;
	down[K] = down[c];
	up[down[K]] = K;
	down[up[K]] = K;
	return K;
}

void addcol(const int& id, const int& c)//生成列函数
{
	K++;
	cnt[c]++;
	col[K] = c;
	row[K] = M;

	left[K] = id;
	right[K] = right[id];
	left[right[K]] = K;
	right[left[K]] = K;

	up[K] = c;
	down[K] = down[c];
	up[down[K]] = K;
	down[up[K]] = K;
}

void addrow(const int& i, const int& j, const int& k)//生成行函数
{
	int id;
	M++;
	ans[M].r = i;
	ans[M].c = j;
	ans[M].k = k + 1;
	id = makecolhead(9 * i + j + delta[0]);
	addcol(id, 9 * i + k + delta[1]);
	addcol(id, 9 * j + k + delta[2]);
	addcol(id, (i / 3 * 3 + j / 3) * 9 + k + delta[3]);
}

void SolveSudo(char x[83])
{
		
	Initial();
	for(int i=0; i < 9; i++)
		for (int j = 0; j < 9; j++)
		{
			if (x[i * 9 + j] == '0')
				for (int k = 0; k < 9; k++)
					addrow(i, j, k);
			else
				addrow(i, j, x[i * 9 + j] - '1');
		}
	dfs(0);
	
}
