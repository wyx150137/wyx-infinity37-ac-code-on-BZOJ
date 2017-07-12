
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int N = 1e3+5;
const int M = 3e5+5;
const int W = M*35;
int n,m,cnt,U,D,L,R,k;
int a[N],b[M];
int ch[W][2],sum[W],root[M];
struct data{int x,y;}q[N];
void insert(int x,int &y,int num,int dep)
{
	y = ++cnt;
	sum[y] = sum[x]+1;
	ch[y][0]=ch[x][0],ch[y][1]=ch[x][1];
	if(dep<0)return ;
	int t = num&(1<<dep);t = t>>dep;
	insert(ch[x][t],ch[y][t],num,dep-1);
}
int solve(int k,int dep)
{
	if(dep==-1)return 0;
	int tmp = 0,t;
	for(int i = U;i<= D;i++)
	{
		t = a[i]&(1<<dep);t = t>>dep;
		tmp+=sum[ch[q[i].y][t^1]]-sum[ch[q[i].x][t^1]];
	}
	if(tmp>=k)
	{
		for(int i = U;i<=D;i++)
		{
			t = a[i]&(1<<dep);t = t>>dep;
			q[i].x = ch[q[i].x][t^1];
			q[i].y = ch[q[i].y][t^1];
		}
		return solve(k,dep-1)+(1<<dep);
	}else
	{
		for(int i = U;i<=D;i++)
		{
			t = a[i]&(1<<dep);t = t>>dep;
			q[i].x = ch[q[i].x][t];
			q[i].y = ch[q[i].y][t];
		}
		return solve(k-tmp,dep-1);
	}
}
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= n;i++)scanf("%d",&a[i]);
	for(int i = 1;i<= m;i++)scanf("%d",&b[i]);
	for(int i = 1;i<= m;i++)insert(root[i-1],root[i],b[i],30);
	int Q;
	scanf("%d",&Q);
	for(int i = 1;i<= Q;i++)
	{
		scanf("%d%d%d%d%d",&U,&D,&L,&R,&k);
		for(int i = U;i<= D;i++)
			q[i].x = root[L-1],q[i].y = root[R];
		printf("%d\n",solve(k,30));
	}
	return 0;
}
