
#include <bits/stdc++.h>
using namespace std;
#define N 510000
int n,tot;
int a[N],head[N],nex[N<<1],to[N<<1];
int f[N],size[N];
void add(int x,int y)
{
    tot++;
    nex[tot]=head[x];
    head[x]=tot;
    to[tot]=y;
}
struct node
{
    int x,y;
    node(){}
    node(int x,int y):x(x),y(y){}
    friend bool operator < (const node &r1,const node &r2)
    {return r1.x-r1.y>r2.x-r2.y;};
};
vector<node>v[N];
void dfs(int x,int y)
{
    size[x]=1;f[x]=a[x];
    for(int i=head[x];i;i=nex[i])
        if(to[i]!=y)
        {
            dfs(to[i],x);
            size[x]+=size[to[i]];
            v[x].push_back(node(f[to[i]]+1,size[to[i]]*2));
        }

    sort(v[x].begin(),v[x].end());

    for(int i=0,sum=0;i<v[x].size();i++)
    {
        node t=v[x][i];
        f[x]=max(f[x],t.x+sum);
        sum+=t.y;
    }
}

inline int read()
{
    int x=0,f=1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
    while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch - '0';ch = getchar();}
    return x*f;
}

int main()
{

    n = read();
    for(int i=1;i<=n;i++) a[i] = read();
    for(int i=1,x,y;i<n;i++)
    {
        x = read(),y = read();
        add(x,y);add(y,x);
    }
    dfs(1,0);
    printf("%d\n",max(f[1],(n-1)*2+a[1]));
    return 0;
}
