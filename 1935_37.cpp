
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 500005;
const int M = 500005;
int id[N*3],n,m;
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
			c[i]+=y;
	}
	int getans(int x)
	{
		int ans = 0;
		for(int i = x;i>0;i-=i&(-i))
			ans+=c[i];
		return ans;
	}
}C;
struct A
{int x,y,no,ans;}ask[M<<2];
bool cmp(A a,A b)
{return a.y<b.y;}
bool fir(A a,A b)
{return a.no<b.no;}
struct T
{int x,y;}tr[N];
bool cmt(T a,T b)
{
	if(a.y!=b.y)
		return a.y<b.y;
	return a.x<b.x;
}
int find(int x)
{
	int l = 1,r = n+1;
	while(l<r)
	{
		int mid = (l+r)>>1;
		if(id[mid]<x)l = mid+1;
		else r = mid;
	}
	if(id[l]>x)return --l;
	return l;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= n;i++)
	{
		scanf("%d%d",&tr[i].x,&tr[i].y);
		tr[i].x+=2;tr[i].y+=2;
		id[i] = tr[i].x;
	}
	sort(tr+1,tr+n+1,cmt);
	sort(id+1,id+n+1);
	int a,b,c,d,cnt = 0;
	for(int i = 1;i<= m;i++)
	{
		scanf("%d%d%d%d",&a,&b,&c,&d);
		a+=2,b+=2,c+=2,d+=2;
		ask[++cnt].x = c;ask[cnt].y = d;ask[cnt].no = cnt;
		ask[++cnt].x = a-1;ask[cnt].y = d;ask[cnt].no = cnt;
		ask[++cnt].x = c;ask[cnt].y = b-1;ask[cnt].no = cnt;
		ask[++cnt].x = a-1;ask[cnt].y = b-1;ask[cnt].no = cnt;
	}
	sort(ask+1,ask+cnt+1,cmp);
	int j = 1;
	for(int i = 1;i<= cnt;i++)
	{
		while(tr[j].y<=ask[i].y&&j<=n)
		{
			C.update(find(tr[j].x),1);
			j++;
		}
		ask[i].ans = C.getans(find(ask[i].x));
	}
	sort(ask+1,ask+cnt+1,fir);
	for(int i = 1;i<= m;i++)
	{
		int t = (i-1)*4;
		printf("%d\n",ask[t+1].ans-ask[t+2].ans-ask[t+3].ans+ask[t+4].ans);
	}
}
