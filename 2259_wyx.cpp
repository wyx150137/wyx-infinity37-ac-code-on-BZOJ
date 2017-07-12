
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 1e6+5;
const int M = N *3;
using namespace std;

int head[N];
bool pre[N],next[N];

struct graph
{
	int next,to,val;
	graph () {}
	graph (int _next,int _to,int _val)
	:next(_next),to(_to),val(_val){}
}edge[M];

inline void add(int x,int y,int z)
{
	static int cnt = 0;
	edge[++cnt] = graph(head[x],y,z);
	head[x] = cnt;
}

int n;

namespace Heap
{
    int h[N],tot;
    int pos[N];

    void up(int x)
    {
        if(x==1)
            return;
        while(h[x]<h[x>>1])
        {
            if(x==1)break;
            swap(h[x],h[x>>1]);
            swap(pos[x],pos[x>>1]);
            x>>=1;
        }
    }

    void push(int x,int y)
    {
        h[++tot]=x;
        pos[tot]=y;
        up(tot);
    }

    int pop()
    {
        swap(h[1],h[tot]);
        swap(pos[1],pos[tot--]);
        int i=1;
        while((((i<<1)<=tot)&&(h[i]>h[i<<1]))||(((i<<1)+1<=tot)&&(h[i]>h[(i<<1)+1])))
        {
            if((i<<1)+1>tot)
            {
                swap(h[i],h[i<<1]);
                swap(pos[i],pos[i<<1]);
                i<<=1;
            }
            else
            {
                int tmp=(h[i<<1]<h[(i<<1)+1])?(i<<1):((i<<1)+1);
                swap(h[i],h[tmp]);
                swap(pos[i],pos[tmp]);
                i=tmp;
            }               
        }
        return pos[tot+1];    
    }

    bool empty()
    {
        return tot == 0;
    }
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
   
inline int read()
{
    static char ch;
    static int D;
    while(!isdigit(ch=getc()));
    for(D=ch-'0'; isdigit(ch=getc());)
        D=(D<<3)+(D<<1)+(ch-'0');
    return D;
}

bool in[N];
int dis[N],s,t;
   
void dij()
{
    memset(dis,0x3f,sizeof dis);
    dis[s]=0;
    Heap :: push(0,s);
    while(!Heap :: empty())
    {
        int now  = Heap :: pop();
        if(in[now])continue; in[now]=1;
        for(int i=head[now];i;i=edge[i].next)
        {
            if(dis[edge[i].to]>dis[now]+edge[i].val)
            {
                dis[edge[i].to]=dis[now]+edge[i].val;
                Heap :: push(dis[edge[i].to],edge[i].to);
            }
        }
    }
}

int main()
{
	n = read();
	for(int i=1;i<=n;++i){
		int x = read();
		for(int j=i+1; j<=min(i+x+1,n)&&!pre[j] ;++j)
			pre[j] = 1, add(j,j-1,1);
		for(int j=i+x+1;j<=n && !next[j];++j)
			next[j] = 1,add(j,j+1,1);
		if(i+x <= n)
			add(i,i+x+1,0);
		else add(i,n+1,i+x-n);
	}

	s = 1;
	t = n + 1;
	dij();
	cout << dis[t] << endl;
}
