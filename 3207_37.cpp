
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef unsigned long long ull;
const int N = 100005;
const int M = 8e6+5;
int num[N],n,m,k,Num,cnt;
ull a[N],T[N];
int find(ull x)
{
	int l = 1,r = Num+1;
	while(l<r)
	{
		int mid=(l+r)>>1;
		if(T[mid]<x)l = mid+1;
		else r = mid;
	}
	return l;
}
int root[N],ls[M],rs[M],sum[M];
void init()
{
	scanf("%d%d%d",&n,&m,&k);
	for(int i = 1;i<= n;i++)scanf("%d",&num[i]);
	for(int i=1;i+k-1<=n;i++)
	{
		for(int j = i;j<=i+k-1;j++)
			a[i] = (a[i]<<31)+num[j];
		T[++Num] = a[i];
	}
	sort(T+1,T+Num+1);
}
void update(int &p,int pre,int l,int r,int pos)
{
	p = ++cnt;
	sum[p] = sum[pre]+1;
	if(l==r)return ;
	ls[p] = ls[pre],rs[p] = rs[pre];
	int mid = (l+r)>>1;
	if(pos<=mid)
		update(ls[p],ls[pre],l,mid,pos);
	else update(rs[p],rs[pre],mid+1,r,pos);
}
void Find(int x,int y,int k)
{
	if(x>y){printf("Yes\n");return ;}
	int l = 1,r = Num;
	x = root[x],y = root[y];
	while(l<r)
	{
		int mid = (l+r)>>1;
		if(k<=mid)
		{
			x = ls[x],y = ls[y];
			r = mid;
		}else
		{
			x = rs[x],y = rs[y];
			l = mid+1;
		}
	}
	if(sum[y]-sum[x]>0)printf("No\n");
	else printf("Yes\n");
}
ull hash()
{
	int tmp[25];
	ull t = 0;
	for(int i = 1;i<= k;i++)
	{
		scanf("%d",&tmp[i]);
		t = (t<<31)+tmp[i];
	}
	return t;
}
int main()
{
	init();
	for(int i =1;i<= Num;i++)
		update(root[i],root[i-1],1,Num,find(a[i]));
	int x,y;
	while(m--)
	{
		scanf("%d%d",&x,&y);
		ull t = hash();
		int tmp = find(t);
		if(T[tmp]!=t)printf("Yes\n");
		else
			Find(x-1,y-k+1,tmp);
	}
	return 0;
}
