
#include <queue>
#include <stack>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <limits.h>
#include <string.h>
#include <string>
#include <algorithm>

using namespace std;

const int MAX = 10010;
struct NODE{int to,len;NODE *next;};
NODE *p[MAX],node[MAX*10];
int cou;
int dis[25][MAX],L;
void init()
{
	cou = 0;
	memset(node,'\0',sizeof(node));
	memset(p,'\0',sizeof(p));
}
void Add(int x,int y,int w)
{
	node[cou].len = w;
	node[cou].to = y;
	node[cou].next = p[x];
	p[x] = &node[cou++];
}
struct cmp{
	bool operator()(int a,int b)
	{
		return dis[L][a] > dis[L][b];
	}
};
void Dijkstra(int s,int n,int *dis)
{
	bool used[MAX];
	memset(used,0,sizeof(used));
	used[s] = true;
	dis[s] = 0; int now = s;
	for(int i=0; i<n-1; i++)
	{
		NODE *head = p[now];
		while( head )
		{
			if( dis[head->to] > dis[now] + head->len )
				dis[head->to] = dis[now] + head->len;
			head = head->next;
		}
		int mmin = INT_MAX;
		for(int k=1; k<=n; k++)
			if( !used[k] && mmin > dis[k] )
				mmin = dis[now = k];
		used[now] = true;
	}
}
void Dijkstra1(int s,int n,int l)
{
	priority_queue<int,vector<int>,cmp> q;
	bool used[MAX];
	memset(used,0,sizeof(used));
	used[s] = true;
	int now = s;
	dis[l][s] = 0;
	q.push(s);
	while( !q.empty() )
	{
		int now = q.top(); used[now] = true;
		NODE *head = p[now]; q.pop();
		while( head )
		{
			if( dis[l][head->to] > min( dis[l-1][now],dis[l][now] + head->len ) )
			{
				dis[l][head->to] = min( dis[l-1][now],dis[l][now] + head->len );
				q.push(head->to);
			}
			head = head->next;
		}
	}
}

int main()
{
	int n,m,K,x,y,w;
	
	while( ~scanf("%d%d%d",&n,&m,&K) )
	{
		while( m-- )
		{
			scanf("%d%d%d",&x,&y,&w);
			Add(x,y,w); Add(y,x,w);
		}
		for(int k=0; k<=K; k++)
			for(int i=1; i<=n; i++)
				dis[k][i] = 500000000;
		Dijkstra(1,n,dis[0]);
		
		for(L=1; L<=K; L++)
			Dijkstra1(1,n,L);
		printf("%d\n",dis[K][n]);
	}

return 0;
}
