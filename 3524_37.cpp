
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 5e5+5;
const int M = 1e7+5;
int root[N];
int ls[M],rs[M],sum[M];
int cnt,n,m;
void update(int l,int r,int rt1,int &rt2,int v)
{
	rt2 = ++cnt;
	sum[rt2] = sum[rt1]+1;
	if(l==r)return ;
	int mid = (l+r)>>1;
	ls[rt2] = ls[rt1],rs[rt2] = rs[rt1];
	if(v<=mid)update(l,mid,ls[rt1],ls[rt2],v);
	else update(mid+1,r,rs[rt1],rs[rt2],v);
}
int ask(int L,int R)
{
	int l,r,tmp = (R-L+1)>>1;
	int rt1 = root[L-1],rt2 = root[R];
	l = 1,r = n+1;
	while(l<r)
	{
		int mid = (l+r)>>1;
		if(sum[rt2]-sum[rt1]<=tmp)return 0;
		if(sum[ls[rt2]]-sum[ls[rt1]]>tmp)
		{
			r = mid;
			rt1 = ls[rt1],rt2 = ls[rt2];
		}else if(sum[rs[rt2]]-sum[rs[rt1]]>tmp)
		{
			l = mid+1;
			rt1 = rs[rt1],rt2 = rs[rt2];
		}
		else return 0;
	}
	return l;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= n;i++)
	{
		int x;
		scanf("%d",&x);
		update(1,n,root[i-1],root[i],x);
	}
	int x,y;
	for(int i = 1;i<= m;i++)
	{
		scanf("%d%d",&x,&y);
		printf("%d\n",ask(x,y));
	}
	return 0;
}
