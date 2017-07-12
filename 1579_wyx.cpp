
#include <bits/stdc++.h>
#define inf 1000000000
#define maxn 10000+100
#define maxm 50000+100
#define eps 1e-10
#define ll long long
#define pa pair<int,int>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=10*x+ch-'0';ch=getchar();}
    return x*f;
}
int n,m,k,tot;
int d[maxn][25],head[maxn];
bool v[maxn][25];
struct edge{int go,next,w;}e[2*maxm];
void ins(int x,int y,int z)
{
    e[++tot].go=y;e[tot].w=z;e[tot].next=head[x];head[x]=tot;
}
void insert(int x,int y,int z)
{
    ins(x,y,z);ins(y,x,z);
}
void dijkstra()
{
    priority_queue<pa,vector<pa>,greater<pa> >q;
    for(int i=1;i<=n;i++)
     for(int j=0;j<=k;j++)
      d[i][j]=inf;
    memset(v,0,sizeof(v));
    d[1][0]=0;q.push(make_pair(0,1));
    while(!q.empty())
    {
        int x=q.top().second;q.pop();
        int z=x/(n+1);x=x%(n+1);
        if(v[x][z])continue;v[x][z]=1;
        for(int i=head[x],y;i;i=e[i].next)
          {
            if(d[x][z]+e[i].w<d[y=e[i].go][z])
            {
                d[y][z]=d[x][z]+e[i].w;
                q.push(make_pair(d[y][z],z*(n+1)+y));
            }
            if(z==k)continue;
            if(d[x][z]<d[y][z+1])
            {
                d[y][z+1]=d[x][z];
                q.push(make_pair(d[y][z+1],(z+1)*(n+1)+y));
            }
          } 
    }
}
int main()
{
    n=read();m=read();k=read();
    for(int i=1;i<=m;i++)
    {
        int x=read(),y=read(),z=read();
        insert(x,y,z);
    }
    dijkstra();
    printf("%d\n",d[n][k]);
    return 0;
}
