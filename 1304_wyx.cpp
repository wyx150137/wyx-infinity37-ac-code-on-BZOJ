
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#define N 100000+5
#define M 200000+5
using namespace std;
int head[N],f[N],g[N],h[N],m,n;
int to[N];
//f[i] represent the formal least nums && the root is i
//g[i] represent the informal least nums because of the white leaves && the root is i
//h[i] represent the informal least nums because of the black leaves && the root is i
//of all his son-trees there can't be conflick or it will go die
//we make tmp1=sum{f[v]}  v is one son of i 
//        tmp2=sum{min(f[v],g[v])} v is one son of i 
//        tmp3=sum{min(f[v]),h[v]} v is one son of i
//then f[i]=min(tmp1,tmp2+1,tmp3+1)
//     g[i]=min(tmp2,tmp3+1)
//	   h[i]=min(tmp2+1,tmp3)
//     ans=f[root]
char getc()
{
    static const int LEN = 1<<15;
    static char buf[LEN],*S=buf,*T=buf;
    if(S == T)
    {
        T = (S=buf)+fread(buf,1,LEN,stdin);
        if(S == T)return EOF;
    }
    return *S++;
}
  
int read()
{
    static char ch;
    static int D;
    while(!isdigit(ch=getc()));
    for(D=ch-'0'; isdigit(ch=getc());)
        D=(D<<3)+(D<<1)+(ch-'0');
    return D;
}
int color[N];
struct graph
{
	int next,to;
	graph () {}
	graph (int _next,int _to)
	:next(_next),to(_to){}
}edge[M];
inline void add(int x,int y)
{
	static int cnt = 0;
	edge[++cnt]=graph(head[x],y);
	head[x]=cnt;
	edge[++cnt]=graph(head[y],x);
	head[y]=cnt;
}
void DFS(int x,int fa)
{
	int tmp1=0,tmp2=0,tmp3=0;
	if(color[x]==0)
	{
		f[x]=1,g[x]=0;
		return;
	}
	else if(color[x]==1)
	{
		f[x]=1,h[x]=0;
		return;
	}
	for(int i=head[x];i;i=edge[i].next)
		if(edge[i].to^fa)
		{
			DFS(edge[i].to,x);
			tmp1+=f[edge[i].to];
			tmp2+=min(f[edge[i].to],g[edge[i].to]);
			tmp3+=min(f[edge[i].to],h[edge[i].to]);
		}
	f[x]=min(tmp1,min(tmp2+1,tmp3+1));
	g[x]=min(tmp2,tmp3+1);
	h[x]=min(tmp3,tmp2+1);
}
int main()
{
	cin>>m>>n;
	memset(color,-1,sizeof color);
	//memset(f,0x3f,sizeof f);
	memset(g,0x3f,sizeof g);
	memset(h,0x3f,sizeof h);
	for(int i=1;i<=n;++i)
		color[i]=read();
	int root=-1;
	for(int i=1;i<m;++i)
	{
		int tmp1=read(),tmp2=read();
		add(tmp1,tmp2);
		if(root==-1)
		{
			to[tmp1]++,to[tmp2]++;
			if(to[tmp1]>1)
				root=tmp1;
			else if(to[tmp2]>1)
				root=tmp2;
		}
	}
	DFS(root,-1);
	cout<<f[root];
}
