
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 50+5;
using namespace std;

char str[N];
bool vis[N][N][2];
int f[N][N][2];

bool check(int a,int b)
{
	int len = b - a + 1;
	if (len & 1)return false;
	int mid = (a + b) >> 1; len >>= 1;
	for(int i=a;i<=mid;++i)
		if(str[i]!=str[i+len])
			return false;
	return true;
}

int DFS(int l,int r,bool t)
{
	if(l==r) return 1;
	int len=r-l+1,mid=(l+r)>>1;
	if(vis[l][r][t]) return f[l][r][t];
	vis[l][r][t]=1;
	int &tmp = f[l][r][t];
	tmp = len;
	if(t)
		for(int i=l;i<r;++i)
			tmp = min(tmp,DFS(l,i,t)+DFS(i+1,r,t)+1);
	for(int i=l;i<r;++i)
		tmp = min(tmp,DFS(l,i,t)+r-i);
	if(check(l,r))
		tmp = min(tmp,DFS(l,mid,0)+1);
	return tmp;
}

int main()
{
	scanf("%s",str+1);
	int len = strlen(str+1);
	cout << DFS(1,len,1);
}
