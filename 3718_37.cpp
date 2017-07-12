
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 5e4+5;
struct C
{int a,b,c;}car[N];
int id[N];
bool cmp(const C &x,const C &y)
{
	return x.a>y.a;
}
int getid(int x,int tot)
{
	int l = 1,r = tot+1;
	while(l<r)
	{
		int mid = (l+r)>>1;
		if(id[mid]<x)l=mid+1;
		else r = mid;
	}
	return l;
}
int c[N];
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
void work()
{
	memset(c,0,sizeof(c));
	int x1,x2,y1,y2;
	int n,w;
	scanf("%d%d",&n,&w);
	for(int i = 1;i<= n;i++)
	{
		scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
		car[i].a = min(x1,x2);
		car[i].c = abs(y2-y1);
	}
	for(int i = 1;i<= n;i++)
	{
		scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
		car[i].b = min(x1,x2);id[i] = car[i].b;
	}
	sort(id+1,id+n+1);
	int tot = 0;
	id[0]=-1;
	for(int i = 1;i<= n;i++)
		if(id[tot]!=id[i])
			id[++tot] = id[i];
	sort(car+1,car+n+1,cmp);
	for(int i = 1;i<= n;i++)
	{
		int pos = getid(car[i].b,tot);
		int maxn = getans(pos-1);
		if(w-maxn<car[i].c){printf("NIE\n");return ;}
		update(pos,car[i].c);
	}
	printf("TAK\n");
}
int main()
{
	int cas;
	scanf("%d",&cas);
	while(cas--)work();
	return 0;
}
