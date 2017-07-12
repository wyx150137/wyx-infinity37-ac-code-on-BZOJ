
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#include <queue>
#define N 100+5
#define M 400+5
using namespace std;
int head[N];
 
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
    head[x]=cnt;
}
queue <int> Q;
int S,TT;
bool in[N];
int used[N][N];
int f[N];
int dis[N];
int spfa(int from,int t)
{
    int T[N] = {};
    for(int j=from;j<=t;++j)
        for(int i=1;i<=used[j][0];++i)
            T[used[j][i]]=1;
    memset(dis,0x3f,sizeof dis);
    dis[S]=0;Q.push(S);
    while(!Q.empty())
    {
        int tt=Q.front();
        Q.pop();
        in[tt]=false;
        for(int i=head[tt];i;i=edge[i].next)
        {
            if(dis[edge[i].to]>dis[tt]+edge[i].val && !T[edge[i].to])
            {
                dis[edge[i].to] = dis[tt]+edge[i].val;
                if(!in[edge[i].to])
                {
                    in[edge[i].to]=1;
                    Q.push(edge[i].to);
                }
            }
        }
    }
    return dis[TT];
}
int cost[N][N];
int main()
{
    int t=read(),n=read(),k=read(),m=read();S=1,TT=n;
    for(int i=1;i<=m;++i)
    {
        int x=read(),y=read(),z=read();
        add(x,y,z),add(y,x,z);
    }
    int d=read();
    for(int i=1;i<=d;++i)
    {
        int x=read();
        int from=read(),to=read();
        for(int j=from;j<=to;++j)
            used[j][++used[j][0]] = x;
    }
    memset(cost,0x3f,sizeof cost);
    int inf = cost[0][0];
    for(int i=1;i<=t;++i)
        for(int j=i;j<=t;++j)
            cost[i][j]=spfa(i,j);
    memset(f,0x3f,sizeof f);
    f[0]=-k;
    for(int i=1;i<=t;++i)
        for(int j=0;j<i;++j)
            if(cost[j+1][i]!=inf)
            f[i]=min(f[j]+cost[j+1][i]*(i-j)+k,f[i]);
    cout<<f[t];
}   
