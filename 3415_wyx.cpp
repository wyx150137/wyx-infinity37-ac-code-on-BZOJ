
#include <queue>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 1000000+5;
const int M = 4000000+5;
using namespace std;
inline void Min(int &a,int b)
{
	if(a > b) a = b;
}
struct data
{
	int head[N],nxt[N],to[N];
	int pre[N];
	void add(int x,int y)
	{
		static int cnt = 0;
		nxt[++cnt] = head[x];
		pre[head[x]] = cnt;
		head[x] = cnt;
		to[cnt] = y;
	}
	void del(int x,int y)
	{
		if(y == head[x]) head[x] = nxt[y];
		{
			nxt[pre[y]] = nxt[y];
			pre[nxt[y]] = pre[y];
		}
 	}
}edge[3];

queue <int> q;

int ans[N],depth[N],vis[N];
int n,m,a,b,k;

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int main()
{
	n = read(), m = read(), k = read(),a = read(),b = read();
	for(int i=1;i<=m;++i)
	{
		int x = read(),y = read();
		edge[1].add(x,y),edge[1].add(y,x);
		edge[2].add(x,y),edge[2].add(y,x);
	}
	q.push(k);
	depth[k] = 1;

	while(!q.empty())
	{
		int tt =q.front();
		q.pop();
		for(int i=edge[1].head[tt];i;i=edge[1].nxt[i])
		{
			if(!depth[edge[1].to[i]])
			{
				depth[edge[1].to[i]] = depth[tt] + 1;
				q.push(edge[1].to[i]);
			}	
		}			
	}
	
	for(int i=1;i<=n;++i)
	{
		int tt = depth[i] - 1;
		depth[i] = 0;
		ans[i] = min(tt*a,(tt>>1)*b+(tt&1)*a);
	}

	q.push(k);
	depth[k] = 1;

	while(!q.empty())
	{
		int tt = q.front();q.pop();
	//	cout << tt << endl;
		for(int i=edge[1].head[tt];i;i=edge[1].nxt[i])
			vis[edge[1].to[i]] = 1;
		for(int i=edge[1].head[tt];i;i=edge[1].nxt[i])
			for(int j=edge[2].head[edge[1].to[i]];j;j=edge[2].nxt[j])
			{
				if(!depth[edge[2].to[j]] && !vis[edge[2].to[j]])
				{
					depth[edge[2].to[j]] = depth[tt] + 1;
					q.push(edge[2].to[j]);
					edge[2].del(edge[1].to[i],j);
				}
			}
		for(int i=edge[1].head[tt];i;i=edge[1].nxt[i])
			vis[edge[1].to[i]] = 0;
	}
	for(int i=1;i<=n;++i)
		if(depth[i])
			Min(ans[i],(depth[i]-1)*b);
	for(int i=1;i<=n;++i)
		printf("%d\n",ans[i]);
}
