
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#define N 300000+5
#define M 1200000+5
#define stack_size (20001000) 
using namespace std;
int stack[stack_size],bak; 
int head[N],size[N],fa[N],top[N],w[N],depth[N],n;
int sz;
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
void DFS1(int x)
{
	size[x]=1;
	for(int i=head[x];i;i=edge[i].next)
		if(edge[i].to!=fa[x])
		{
			depth[edge[i].to]=depth[x]+1;
			fa[edge[i].to]=x;
			DFS1(edge[i].to);
			size[x]+=size[edge[i].to];
		}
}

void DFS2(int x,int chain)
{
	w[x]=++sz;
	top[x]=chain;
	int k=0;
	for(int i=head[x];i;i=edge[i].next)
		if(edge[i].to!=fa[x]&&size[k]<size[edge[i].to])
			k=edge[i].to;
	if(!k)return;
	DFS2(k,chain);
	for(int i=head[x];i;i=edge[i].next)
		if(edge[i].to!=fa[x]&&edge[i].to!=k)
			DFS2(edge[i].to,edge[i].to);
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
    DFS1(1);
    DFS2(1,1);
    __asm__ __volatile__    
    (    
        "mov %0,%%esp\n"  
        :    
        :"g"(bak)    
        :    
    );    
}   
struct seg
{
	int l,r,mn,lazy;
}tr[M];
void build(int k,int l,int r)
{
	tr[k].l=l,tr[k].r=r;
	if(l==r)return;
	int mid=(l+r)>>1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
}
void down(int k)
{
	int tmp=tr[k].lazy;
	tr[k].lazy=0;
	if(tr[k].l==tr[k].r||!tmp)
		return;
	tr[k<<1].lazy+=tmp;
	tr[k<<1|1].lazy+=tmp;
	tr[k<<1].mn+=(tr[k<<1].r-tr[k<<1].l+1)*tmp;
	tr[k<<1|1].mn+=(tr[k<<1|1].r-tr[k<<1|1].l+1)*tmp;
}
inline void updata(int k)
{
	tr[k].mn=tr[k<<1].mn+tr[k<<1|1].mn;
}
void change(int k,int l,int r)
{
	down(k);
	if(l==tr[k].l&&r==tr[k].r)
	{
		tr[k].lazy++;
		tr[k].mn+=(r-l+1);
		return;
	}
	int mid=(tr[k].l+tr[k].r)>>1;
	if(r<=mid)
		change(k<<1,l,r);
	else if(l>mid)
		change(k<<1|1,l,r);
	else
	{
		change(k<<1,l,mid);
		change(k<<1|1,mid+1,r);
	}
	updata(k);
}
int map[N];
void solvechange(int x,int y)
{
	while(top[x]!=top[y])
	{
		if(depth[top[x]]<depth[top[y]])
			swap(x,y);
	//	printf("change %d %d  \n",top[x],x);
		change(1,w[top[x]],w[x]);
		x=fa[top[x]];
	}
	if(w[x]>w[y])
		swap(x,y);
	change(1,w[x],w[y]);
}

int ask(int k,int pos)
{
	down(k);
	if(tr[k].l==pos && tr[k].r==pos)
		return tr[k].mn;
	int mid=(tr[k].l+tr[k].r)>>1;
	if(pos<=mid)
		return ask(k<<1,pos);
	else
		return ask(k<<1|1,pos);
}
int ans[N];
void Getans(int k)
{
	if(tr[k].l==tr[k].r)
	{
		ans[tr[k].l]=tr[k].mn;
		return;
	}
	Getans(k<<1);
	Getans(k<<1|1);
}
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
void print( int k )
{
    int num = 0;
    char ch[17];
    while(k>0) ch[++num] = k % 10, k /= 10;
    while(num) 
        putchar( ch[num--]+48 );
    putchar(10);
}
void check()
{
	puts("checking ****************************");
	for(int i=1;i<=n;++i)
		printf("%d %d\n",i,ask(1,w[i]));
	puts("checking ****************************");
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;++i)
		map[i]=read();
	for(int i=1;i<n;++i)
	{
		int x,y;
		x=read(),y=read();
		add(x,y);
	}
	build(1,1,n);
	CallDFS();
	for( int i=1;i<n;++i)
		solvechange(map[i],map[i+1]);
	for(int i=1;i<=n;++i)
	{
		if(i!=map[1])
			printf("%d\n",ask(1,w[i])-1);
		else
			printf("%d\n",ask(1,w[i]));
	}
}
