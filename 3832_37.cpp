
#include <stdio.h>
#include <queue>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int M = 1e6+5;
const int N = 5e5+5;
const int INF = 0x3f3f3f3f;
struct E
{int next,to;}e[M],fe[M];
int head[N],fh[N],tot;
int line[N],top;
int g[N],f[N],ind[N];
void add(int x,int y)
{
	ind[y]++;
	e[++tot].to = y;
	e[tot].next = head[x];
	head[x] = tot;
	fe[tot].to = x;
	fe[tot].next = fh[y];
	fh[y] = tot;
}
queue<int>Q;
int heap[M<<1],dele[M<<1],ch,cd;
int main()
{
	//freopen("raj.in","r",stdin);
	//freopen("raj.out","w",stdout);
	int n,m,x,y;
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= m;i++)
	{
		scanf("%d%d",&x,&y);
		add(x,y);
	}
	for(int i = 1;i<= n;i++)
		if(!ind[i])
			Q.push(i);
	while(!Q.empty())
	{
		x = Q.front();
		Q.pop();
		line[++top] = x;
		for(int i = head[x];i;i = e[i].next)
			if(!--ind[e[i].to])
				Q.push(e[i].to);
	}
	for(int i = 1;i<= top;i++)
	{
		int tmp = line[i];
		f[tmp] = max(f[tmp],1);
		for(int j = head[tmp];j;j = e[j].next)
			f[e[j].to] = max(f[e[j].to],f[tmp]+1);
	}
	for(int i = top;i>= 1;i--)
	{
		int tmp = line[i];
		g[tmp] = max(g[tmp],1);
		for(int j = head[tmp];j;j = e[j].next)
			g[tmp] = max(g[tmp],g[e[j].to]+1);
	}
	for(int i = 1;i<= n;i++)
	{
		heap[++ch] = g[i];
		push_heap(heap+1,heap+ch+1);
	}
	int ans_len = INF,ans;
	for(int i = 1;i<= top;i++)
	{
		x = line[i];
		for(int j = fh[x];j;j = fe[j].next)
		{
			dele[++cd] = f[fe[j].to]+g[x];
			push_heap(dele+1,dele+cd+1);
		}
		dele[++cd] = g[x];
		push_heap(dele+1,dele+cd+1);
		while(dele[1]==heap[1]&&cd>=1&&ch>=1)
		{
			pop_heap(dele+1,dele+cd+1);
			cd--;
			pop_heap(heap+1,heap+ch+1);
			ch--;
		}
		if(ch&&heap[1]<ans_len)
		{
			ans_len = heap[1];
			ans = x;
		}
		for(int j=head[x];j;j = e[j].next)
		{
			heap[++ch] = f[x]+g[e[j].to];
			push_heap(heap+1,heap+ch+1);
		}
		heap[++ch] = f[x];
		push_heap(heap+1,heap+ch+1);
	}
	printf("%d %d\n",ans,ans_len-1);
	return 0;
}
