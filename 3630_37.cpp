
#include <stdio.h>
#include <queue>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
queue<int>Q;
const int N = 6010;
const int M = 2e5+5;
const int INF = 0x3f3f3f3f;
typedef long long ll;
struct S
{
	int x1,y1,x2,y2,x,y,r;
	int k;
}s[N];
ll getdis(int x1,int y1,int x2,int y2)
{
	return (ll)(x1-x2)*(x1-x2)+(ll)(y1-y2)*(y1-y2);
}
bool check(int i,int j)
{
	int typ = s[i].k+s[j].k;
	if(typ==2)
	{
		return getdis(s[i].x,s[i].y,s[j].x,s[j].y)<=(ll)(s[i].r+s[j].r)*(s[i].r+s[j].r);
	}
	if(typ==3)
	{
		if(s[i].k==1)swap(i,j);
		if(getdis(s[i].x1,s[i].y1,s[j].x,s[j].y)<=(ll)s[j].r*s[j].r)return true;
		if(getdis(s[i].x1,s[i].y2,s[j].x,s[j].y)<=(ll)s[j].r*s[j].r)return true;
		if(getdis(s[i].x2,s[i].y1,s[j].x,s[j].y)<=(ll)s[j].r*s[j].r)return true;
		if(getdis(s[i].x2,s[i].y2,s[j].x,s[j].y)<=(ll)s[j].r*s[j].r)return true;
		if(s[i].y1<=s[j].y&&s[i].y2>=s[j].y)
			if(abs(s[i].x2-s[j].x)<=s[j].r||abs(s[i].x1-s[j].x)<=s[j].r)
				return true;
		if(s[i].x1<s[j].x&&s[i].x2>s[j].x)
			if(abs(s[i].y2-s[j].y)<=s[j].r||abs(s[i].y1-s[j].y)<=s[j].r)
				return true;
		if(s[i].x1<=s[j].x&&s[i].x2>=s[j].x&&s[i].y1<=s[j].y&&s[i].y2>=s[j].y)
			return true;
	}
	if(typ==4)
	{
		if((s[i].x1>=s[j].x1&&s[i].x1<=s[j].x2)||(s[i].x2>=s[j].x1&&s[i].x2<=s[j].x2))
        if((s[i].y1>=s[j].y1&&s[i].y1<=s[j].y2)||(s[i].y2>=s[j].y1&&s[i].y2<=s[j].y2))return 1;
        if(s[i].x1<=s[j].x1&&s[j].x2<=s[i].x2&&s[j].y1<=s[i].y1&&s[i].y2<=s[j].y2)return 1;
        swap(i,j);
        if((s[i].x1>=s[j].x1&&s[i].x1<=s[j].x2)||(s[i].x2>=s[j].x1&&s[i].x2<=s[j].x2))
        if((s[i].y1>=s[j].y1&&s[i].y1<=s[j].y2)||(s[i].y2>=s[j].y1&&s[i].y2<=s[j].y2))return 1;
        if(s[i].x1<=s[j].x1&&s[j].x2<=s[i].x2&&s[j].y1<=s[i].y1&&s[i].y2<=s[j].y2)return 1;
	}
	return false;
}
struct E
{int next,to,f;}e[M];
int head[N],tot=1;
void add(int x,int y,int f1,int f2)
{
	e[++tot].to = y;e[tot].next = head[x];head[x] = tot;e[tot].f = f1;
	e[++tot].to = x;e[tot].next = head[y];head[y] = tot;e[tot].f = f2;
}
int d[N],st,ed;
bool bfs(int s,int t)
{
	for(int i = st;i<= ed;i++)
		d[i] = -1;
	d[t] = 0;
	Q.push(t);
	while(!Q.empty())
	{
		int x = Q.front();
		Q.pop();
		for(int i = head[x];i;i=e[i].next)
			if(d[e[i].to]==-1&&e[i^1].f)
			{
				d[e[i].to] = d[x]+1;
				Q.push(e[i].to);
			}
	}
	return d[s]!=-1;
}
int get_mf(int s,int t,int mf)
{
	if(s==t)return mf;
	int last = mf;
	for(int i = head[s];i;i=e[i].next)
		if(d[e[i].to]==d[s]-1&&e[i].f)
		{
			int tof = get_mf(e[i].to,t,min(e[i].f,last));
			if(tof)
			{
				e[i].f-=tof;
				e[i^1].f+=tof;
				if(!(last-=tof))return mf;
			}
		}
	d[s] = -1;
	return mf-last;
}
int dinic(int s,int t)
{
	int ans = 0,nf;
	while(bfs(s,t))
		while((nf=get_mf(s,t,INF)))
			ans+=nf;
	return ans;
}
void display(int S,int T)
{
	for(int i = S;i<= T;i++)
		for(int j = head[i];j;j=e[j].next)
			printf("%d %d:%d\n",i,e[j].to,e[j].f);
}
int main()
{
	int cx,cy,n;
	scanf("%d%d%d",&cx,&cy,&n);
	int S = 1,T = (n+1)<<1;
	st = S,ed = T;
	s[0].k = 2,s[0].x1 = 0,s[0].y1 = cy,s[0].x2 = cx,s[0].y2 = cy;
	s[n+1].k = 2,s[n+1].x1 = 0,s[n+1].y1 = 0,s[n+1].x2=cx,s[n+1].y2 = 0;
	for(int i = 1;i<= n;i++)
	{
		scanf("%d",&s[i].k);
		if(s[i].k==1)scanf("%d%d%d",&s[i].x,&s[i].y,&s[i].r);
		else scanf("%d%d%d%d",&s[i].x1,&s[i].y1,&s[i].x2,&s[i].y2);
		for(int j = 0;j<i;j++)
			if(check(i,j))
				add(j<<1|1,i<<1,INF,0),add(i<<1|1,j<<1,INF,0);
	}
	for(int i = 1;i<= n;i++)
		if(check(i,n+1))
			add(i<<1|1,(n+1)<<1,INF,0),add((n+1)<<1|1,i<<1,INF,0);
	for(int i = 1;i<= n;i++)add(i<<1,i<<1|1,1,1);
	printf("%d\n",dinic(S,T));
	return 0;
}
