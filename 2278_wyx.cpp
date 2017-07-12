
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <algorithm>
#include <bitset>
using namespace std;
#define N 131072
#define M 2100000
#define LEN 1<<20

bitset <N> vis;
bitset <N> du;
bitset <M> ban;
using namespace std;
int to[M],next[M],head[N],ce=1;
int cnt;

inline char getc()
{
	static char *S,*T,buf[LEN];
	if(S==T)
	{
		T=(S=buf)+fread(buf,1,LEN,stdin);
		if(S==T)
			return EOF;
	}
	return *S++;
}

inline int read()
{
	static char ch;
	static int D;
	while(!isdigit(ch=getc()));
	for(D=ch-'0';isdigit(ch=getc());)
		D=D*10+ch-'0';
	return D;
}

namespace ans
{
	int val[M],next[M],head[N<<1],size[N<<1],ce;
	void add(int x,int y)
	{
		size[x]++;
		val[++ce]=y;
		next[ce]=head[x];
		head[x]=ce;
	}
}

void add(int x,int y)
{
	to[++ce]=y;
	next[ce]=head[x];
	head[x]=ce;
}

int dfs(int x,int pre)
{
	vis[x]=1;
	int i,y;
	for(i=head[x];i;i=next[i])
	{
		if(ban[i]||(i^1)==pre)	continue;
		if(!vis[to[i]])
		{
			y=dfs(to[i],i);
			ans::add(cnt,x);
			ban[i]=ban[i^1]=1;
			head[x]=next[i];
			if(x!=y)
			{
				vis[x]=0;
				return y;
			}
		}
		else
		{
			cnt++;
			ans::add(cnt,to[i]);
			ans::add(cnt,x);
			ban[i]=ban[i^1]=1;
			head[x]=next[i];
			vis[x]=0;
			return to[i];
		}
	}
	vis[x]=0;
	return 0;
}
int main()
{
	int n,m,k,x,y,z,w;
	register int i,j;
	n=read(),m=read();
	for(i=1;i<=m;i++)
	{
		x=read(),y=read(),z=read(),w=read();
		if(z!=w)
			add(x,y),add(y,x),du[x]=!du[x],du[y]=!du[y];
	}

	for(i=1;i<=n;i++) if(du[i]){puts("NIE");return 0;}
	for(i=1;i<=n;i++)if(head[i])dfs(i,0);

	cout << cnt << endl;
	for(i=1;i<=cnt;i++)
	{
		printf("%d ",ans::size[i]-1);
		for(j=ans::head[i];j;j=ans::next[j])
		{
			printf("%d ",ans::val[j]);
		}
		puts("");
	}
	return 0;
}
