
#include <stdio.h>
#include <queue>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 7e4+5;
const int M = 4e6+5;
const int INF = 0x3f3f3f3f;
struct E
{int next,to,f;}e[M];
int head[N],_head[N],tot = 1;
void add(int x,int y,int f)
{
	e[++tot].to = y;e[tot].next = head[x];head[x] = tot;e[tot].f = f;
	e[++tot].to = x;e[tot].next = head[y];head[y] = tot;e[tot].f = 0;
}
int d[N];
queue<int>Q;
bool bfs(int s,int t)
{
	for(int i = s;i<= t;i++)d[i]=-1;
	Q.push(t);
	d[t] = 0;
	while(!Q.empty())
	{
		int x = Q.front();
		Q.pop();
		for(int i = head[x];i;i=e[i].next)
			if(e[i^1].f&&d[e[i].to]==-1)
			{
				d[e[i].to] = d[x]+1;
				Q.push(e[i].to);
			}
	}
	if(d[s]==-1)return false;
	memcpy(_head,head,sizeof(head));
	return true;
}
int get_mxf(int s,int t,int mf)
{
	if(s==t)return mf;
	int last=mf;
	for(int i = _head[s];i;i=e[i].next)
	{
		_head[s] = i;
		if(e[i].f&&d[e[i].to]==d[s]-1)
		{
			int tof = get_mxf(e[i].to,t,min(e[i].f,last));
			if(tof)
			{
				e[i].f-=tof;
				e[i^1].f+=tof;
				if(!(last-=tof))return mf;
			}
		}
	}
	return mf-last;
}
int dinic(int s,int t)
{
	int ans = 0;
	while(bfs(s,t))
		ans+=get_mxf(s,t,INF);
	return ans;
}
const int P = 205;
bool vis[P];
int prime[P],cnt;
vector<int>fac[P];
int id[50][50];
void quick_prime()
{
	for(int i = 2;i<=200;i++)
	{
		if(!vis[i])
			prime[++cnt] = i;
		for(int j = 1;j<= cnt&&i*prime[j]<=200;j++)
		{
			vis[i*prime[j]] = true;
			if(i%prime[j]==0)break;
		}
	}
	for(int i = 1;i<= cnt;i++)
	{
		for(int j = prime[i];j<=200;j+=prime[i])
			fac[j].push_back(i);
	}
}
struct Card
{int a,b,c;}c0[30005],c1[30005];
int S,T;
int n1,n2;
void build(int no,int tp)
{
	int a,b,c;
	if(tp)a = c1[no].a,b = c1[no].b,c = c1[no].c;
	else a = c0[no].a,b = c0[no].b,c = c0[no].c;
	for(int i = 0;i<fac[a].size();i++)
		for(int j = 0;j<fac[b].size();j++)
			if(tp)add(id[fac[a][i]][fac[b][j]]+n1+n2,n1+no,1);
			else add(no,id[fac[a][i]][fac[b][j]]+n1+n2,1);
	for(int i = 0;i<fac[a].size();i++)
		for(int j = 0;j<fac[c].size();j++)
			if(tp)add(id[fac[a][i]][fac[c][j]]+cnt*cnt+n1+n2,n1+no,1);
			else add(no,id[fac[a][i]][fac[c][j]]+cnt*cnt+n1+n2,1);
	for(int i = 0;i<fac[b].size();i++)
		for(int j = 0;j<fac[c].size();j++)
			if(tp)add(id[fac[b][i]][fac[c][j]]+cnt*cnt*2+n1+n2,n1+no,1);
			else add(no,id[fac[b][i]][fac[c][j]]+cnt*cnt*2+n1+n2,1);
}
int main()
{
	scanf("%d%d",&n1,&n2);
	quick_prime();
	int Id = 0;
	for(int i = 1;i<= cnt;i++)
		for(int j = 1;j<= cnt;j++)
			id[i][j] = ++Id;
	S = 0,T = n1+n2+3*Id+1;
	for(int i = 1;i<= n1;i++)
		scanf("%d%d%d",&c0[i].a,&c0[i].b,&c0[i].c);
	for(int i = 1;i<= n2;i++)
		scanf("%d%d%d",&c1[i].a,&c1[i].b,&c1[i].c);
	for(int i = 1;i<= n1;i++)
		add(S,i,1),build(i,0);
	for(int i = 1;i<= n2;i++)
		add(i+n1,T,1),build(i,1);
	printf("%d\n",dinic(S,T));
	return 0;
}
