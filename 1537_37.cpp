
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1e5+5;
struct P
{int x,y,p;}pos[N];
int id[N],n,m,k,f[N];
bool cmp(P a,P b)
{
	if(a.y!=b.y)
		return a.y<b.y;
	return a.x<b.x;
}
struct Tree
{
	int c[N];
	Tree()
	{
		memset(c,0,sizeof(c));
	}
	void update(int x,int y)
	{
		for(int i = x;i<N;i+=i&(-i))
			c[i] = max(c[i],y);
	}
	int getans(int x)
	{
		int ans = 0;
		for(int i = x;i>0;i-=i&(-i))
			ans = max(ans,c[i]);
		return ans;
	}
}C;
int find(int x)
{
	int l = 1,r = k+1;
	while(l<r)
	{
		int mid = (l+r)>>1;
		if(id[mid]<x)l= mid+1;
		else r = mid;
	}
	return l;
}
int main()
{
	scanf("%d%d%d",&n,&m,&k);
	for(int i = 1;i<= k;i++)
	{
		scanf("%d%d%d",&pos[i].x,&pos[i].y,&pos[i].p);
		id[i] = pos[i].x;
	}
	sort(id+1,id+k+1);
	sort(pos+1,pos+k+1,cmp);
	int ans = 0;
	for(int i = 1;i<= k;i++)
	{
		f[i] = C.getans(find(pos[i].x))+pos[i].p;
		ans = max(ans,f[i]);
		C.update(find(pos[i].x),f[i]);
	}
	printf("%d\n",ans);
	return 0;
}
