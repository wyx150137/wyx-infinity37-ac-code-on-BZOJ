
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>
using namespace std;
#define N 100000+5
#define M 600000+5
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))
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
   
int  read()
{
    static char ch;
    static int   D;
    while(!isdigit(ch=getc()));
    for(D=ch-'0'; isdigit(ch=getc());)
        D=(D<<3)+(D<<1)+(ch-'0');
    return D;
}
   
struct graph
{
    int from,to;
    long long val;
    bool vis;
    bool operator < (const graph &z)const
    {
        return val<z.val;
    }
}edge[M];
int head[N],fa[N],f[N][22],deep[N],f_max[N][22],f_sec[N][22],n,m;
struct abcd
{
    int next, to;
    long long val;
    abcd() {}
    abcd(int _next, int _to, int _val)
    : next(_next), to(_to), val(_val) {}
} table[M];
inline void add(int x, int y, int z)
{
    static int cnt = 0;
    table[++cnt] = abcd(head[x], y, z);
    head[x] = cnt;
    swap(x,y);
    table[++cnt] = abcd(head[x], y, z);
    head[x] = cnt;
}
int find(int x)
{
    return fa[x]^x?fa[x]=find(fa[x]):fa[x];
}
void dfs(int x)
{
    deep[x]=deep[f[x][0]]+1;
    for(int i=head[x];i;i=table[i].next)
    {
        if(table[i].to==f[x][0])
            continue;
        f[table[i].to][0]=x;
        f_max[table[i].to][0]=table[i].val;
        dfs(table[i].to);
    }
}
int get_max(int x,int y)
{
    int re=0;
    if(deep[x]<deep[y])
        swap(x,y);
    for(int j=21;j>=0;--j)
        if(deep[f[x][j]]>=deep[y])
            re=max(re,f_max[x][j]),x=f[x][j];
    if(x==y)
        return re;
    for(int j=21;j>=0;j--)
        if(f[x][j]^f[y][j])
        {
            re=max(re,f_max[x][j]);
            re=max(re,f_max[y][j]);
            x=f[x][j];
            y=f[y][j];
        }
    re=max(re,f_max[x][0]);
    re=max(re,f_max[y][0]);
    return re;
}
int find_2_Max(int x,int y,int z)
{
    int re=0;
    if(deep[x]<deep[y])
        swap(x,y);
    for(int j=21;j>=0;j--)
    {
        if(deep[f[x][j]]>=deep[y])
        {
            if(f_max[x][j]!=z)
                re=max(re,f_max[x][j]);
            else
                re=max(re,f_sec[x][j]);
            x=f[x][j];
        }
    }
    if(x==y)
        return re;
    for(int j=21;j>=0;--j)
        if(f[x][j]^f[y][j])
        {
            if(f_max[x][j]^z)
                re=max(re,f_max[x][j]);
            else
                re=max(re,f_sec[x][j]);
            if(f_max[y][j]^z)
                re=max(re,f_max[y][j]);
            else
                re=max(re,f_sec[y][j]);
            x=f[x][j];
            y=f[y][j];
        }
    if(f_max[x][0]^z)
        re=max(re,f_max[x][0]);
    else
        re=max(re,f_sec[x][0]);
    if(f_max[y][0]^z)
        re=max(re,f_max[y][0]);
    else
        re=max(re,f_sec[y][0]);
    return re;
}
int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;++i)
        edge[i].from=read(),edge[i].to=read(),edge[i].val=read();
    sort(edge+1,edge+m+1);
    for(int i=1;i<=n;++i)
        fa[i]=i;
    long long ans_min=0;
    for(int i=1;i<=m;++i)
    {
        int fx=find(edge[i].from),fy=find(edge[i].to);
        if(fx==fy)continue;
        fa[fx]=fy;
        edge[i].vis=true;
        add(edge[i].from,edge[i].to,edge[i].val);
        ans_min+=edge[i].val;
    }
    dfs(1);
    for(int j=1;j<=21;++j)
    {
        for(int i=1;i<=n;++i)
        {
            int tmp=f[i][j-1];
            f[i][j]=f[tmp][j-1];
            if(f_max[i][j-1]>f[tmp][j-1])
            {
                f_max[i][j]=f_max[i][j-1];
                f_sec[i][j]=max(f_sec[i][j-1],f_sec[tmp][j-1]);
            }
            else
            {
                f_max[i][j]=f_max[tmp][j-1];
                if(f_max[i][j-1]<f_max[tmp][j-1])
                    f_sec[i][j]=max(f_sec[tmp][j-1],f_max[tmp][j-1]);
                else
                    f_sec[i][j]=max(f_sec[i][j-1],f_sec[tmp][j-1]);
            }
            f_max[i][j]=max(f_max[i][j-1],f_max[tmp][j-1]);
        }
    }
    long long ans_sec=~0ull>>1;
    for(int i=1;i<=m;++i)
    {
        if(!edge[i].vis)
        {
            int tmp=get_max(edge[i].from,edge[i].to);
            if(tmp==edge[i].val)
                tmp=find_2_Max(edge[i].from,edge[i].to,tmp);
            ans_sec=min(ans_sec,ans_min-tmp+edge[i].val);
        }
    }
    cout<<ans_sec;
}
