
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#define N 500000+5
#define M 3000000+5
#define change(x,y) ((x-1)*n+y)
using namespace std;
bool in[N];
int dis[N];
int s,t;
int n;
struct graph
{
    graph *next;int  to, val;
}edge[M],*head[N],*cnt = edge;
   
inline void add(int x, int y, int z)
{
    cnt->to =y;
    cnt->val=z;
    cnt->next=head[x];
    head[x]=cnt++;
}
   
namespace Heap
{
    int h[N<<1],tot;
    int pos[N<<1];
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
     
int read()
{
    static char ch;
    static int D;
    while(!isdigit(ch=getc()));
    for(D=ch-'0'; isdigit(ch=getc());)
        D=(D<<3)+(D<<1)+(ch-'0');
    return D;
}
using namespace Heap;
   
void dij()
{
    memset(dis,0x3f,sizeof dis);
    dis[s]=0;
    push(0,s);
    while(!empty())
    {
        int now  = pop();
        //cout << now << endl;
        if(in[now])continue;
        in[now]=1;
        for(graph *i=head[now];i;i=i->next)
        {
            if(!in[i->to]&&dis[i->to]>dis[now]+i->val)
            {
                dis[i->to]=dis[now]+i->val;
                push(dis[i->to],i->to);
            }
        }
    }
}
   
int main()
{
    n = read();
    s = 0 , t = n * n + 1;
    /*
        n(n + 1)个数表示所有从西到东方向的人流量，然后
        n(n + 1)个数表示所有从北到南方向的人流量，
        n(n + 1)个数表示所有从东到西方向的人流量，最后是n
        (n + 1)个数表示所有从南到北方向的人流量。
        对于每一个方向，输入顺序按照起点由北向南，若南北方向相同时由西到东的顺序给出(参见样例输入)。
    */
    for(int i=1;i<=n;++i)
    {
        int tmp = read();
        add(s,change(1,i),tmp);
    }
    for(int i=1;i<n;++i)
        for(int j=1;j<=n;++j)
        {
            int tmp = read();
            add(change(i,j),change(i+1,j),tmp);
        }
    for(int i=1;i<=n;++i)
    {
        int tmp = read();
        add(change(n,i),t,tmp);
    }
 
 
    for(int i=1;i<=n;++i)
    {
        int tmp = read();
        add(change(i,1),t,tmp);
        for(int j=2;j<=n;++j)
        {
            int tt = read();
            add(change(i,j),change(i,j-1),tt);
        }
        tmp = read();
        add(s,change(i,n),tmp);
    }
 
 
    for(int i=1;i<=n;++i)
        int tmp = read();
    for(int i=1;i<n;++i)
        for(int j=1;j<=n;++j)
        {
            int tmp = read();
            add(change(i+1,j),change(i,j),tmp);
        }
    for(int i=1;i<=n;++i)
        int tmp = read();
    for(int i=1;i<=n;++i)
    {
        int tmp = read();
        for(int j=2;j<=n;++j)
        {
            int x = read();
            add(change(i,j-1),change(i,j),x);
        }
        tmp = read();
    }
    dij();
    cout<<dis[t];
}
 
