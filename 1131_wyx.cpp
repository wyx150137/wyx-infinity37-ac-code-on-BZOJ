
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#define N 1000000+5
#define M 2000000+5
#define stack_size (20001000) 
using namespace std;
int head[N];
long long size[N];
long long depth[N];
long long sum[N];
long long f[N];
int fa[N];
int stack[stack_size],bak;  
int n;


inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch - '0';ch = getchar();}
	return x*f;
}

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
	edge[++cnt] = graph(head[x],y);
	head[x] = cnt;
	edge[++cnt] = graph(head[y],x);
	head[y] = cnt;
}

void DFS(int x)
{
	size[x] = 1;
	sum[x] = depth[x];
	for(int i=head[x] ; i ;i=edge[i].next)
		if(edge[i].to!=fa[x])
		{
			depth[edge[i].to] = depth[x] + 1;
			fa[edge[i].to] = x;
			DFS(edge[i].to);
			sum[x] += sum[edge[i].to];
			size[x]+=size[edge[i].to];
		}
}

void DFS2(int x)
{
	//printf("x = %d fa = %d\n",x,fa);
	for(int i=head[x] ; i ; i=edge[i].next)
	{
		if(edge[i].to!=fa[x])
		{
			f[edge[i].to] = f[x] + (n-size[edge[i].to]) - size[edge[i].to];
			DFS2(edge[i].to);
		}
	}
}
void CallDFS()    
{    
    __asm__ __volatile__    
    (    
        "mov %%esp,%0\n"  
        "mov %1,%%esp\n"  
        :"=g"(bak)    
        :"g"(stack+stack_size-1)    
        :    
    );    
    DFS(1);
    f[1] = sum[1];
    DFS2(1);    
    __asm__ __volatile__    
    (    
        "mov %0,%%esp\n"  
        :    
        :"g"(bak)    
        :    
    );    
}   

int main()
{
	//freopen("sta9b.in","r",stdin);
	scanf("%d",&n);
	for(int i=1;i<n;++i)
	{
		int x=read(),y=read();
		add(x,y);
	}
	depth[1] = 1;
	//for(int i=1;i<=n;++i)
	//{
	//	printf("depth[%d] = %d\n",i,depth[i]);
	//}

	//cout<<sum[1]<<endl;
	//for(int i=1;i<=n;++i)
	//	printf("f[%d] = %d\n",i,f[i]);
	//cout<<size[1] << endl;
	//for(int i=1;i<=n;++i)
	//	printf("size[%d] = %d\n",i,size[i]);
	CallDFS();
	long long ans = 0;
	int num = 0;
	for(int i=1;i<=n;++i)
		if(ans < f[i])
			ans = f[i] , num = i;
	cout<<num<<endl;
}
