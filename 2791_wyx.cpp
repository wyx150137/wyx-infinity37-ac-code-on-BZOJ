
#include<cstdio>
#include<algorithm>
#define N 500050
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int n,fa[N][20],root,q,belong[N],deep[N];
int num[N],sum[N],tot,pos[N],vis[N];

void Find(int x)
{
    int now=x;
    for(;;x=fa[x][0])
    {
        if(vis[x]==now)break;
        if(vis[x])return;
        vis[x]=now;
    }
    tot++;
    while(!belong[x])
    {
        belong[x]=x;
        deep[x]=1;
        num[x]=++sum[tot];
        pos[x]=tot;
        x=fa[x][0];
    }
}

void DFS(int x)
{
    if(deep[x]) return;
    DFS(fa[x][0]);
    belong[x] = belong[fa[x][0]];
    deep[x] = deep[fa[x][0]]+1;
}
inline int Lca(int x,int y)
{
    if(deep[x]<deep[y]) swap(x,y);
    int t=deep[x]-deep[y];
    for(int i=18;~i;i--)
    	if(t&(1<<i))
    		x=fa[x][i];
    if(x==y)return x;
    for(int i=18;~i;--i)
    	if(fa[x][i]!=fa[y][i])
    		x=fa[x][i],y=fa[y][i];
    return fa[x][0];
}
bool check(int a,int b,int c,int d)
{
    if(max(a,b)<max(c,d))return 1;
    if(max(a,b)>max(c,d))return 0;
    if(min(a,b)<min(c,d))return 1;
    if(min(a,b)>min(c,d))return 0;
    if(a>=b)return 1;
    return 0;
}
int main()
{
    n=read();int Q=read();
    for(int i=1;i<=n;i++)
	    fa[i][0]=read();
    for(int i=1;i<=n;i++)
    	Find(i);
    for(int i=1;i<=n;i++)
    	if(!belong[i])
    		DFS(i);
    for(int j=1;j<=19;++j)
    	for(int i=1;i<=n;++i)
    		fa[i][j] = fa[fa[i][j-1]][j-1];
    		
    while(Q--)
    {
        int x=read(),y=read();
        if(pos[belong[x]]!=pos[belong[y]])
        {
            puts("-1 -1");
            continue;
        }
        if(belong[x]==belong[y])
        {
            int t=Lca(x,y);
            printf("%d %d\n",deep[x]-deep[t],deep[y]-deep[t]);
            continue;
        }
        int ans1=deep[x]-1,ans2=deep[y]-1;
        int t=pos[belong[x]];
        x=num[belong[x]];
        y=num[belong[y]];
        int z1=(sum[t]+y-x)%sum[t],z2=sum[t]-z1;
        if(check(ans1+z1,ans2,ans1,ans2+z2))
       		printf("%d %d\n",ans1+z1,ans2);
        else printf("%d %d\n",ans1,ans2+z2);
    }
}
