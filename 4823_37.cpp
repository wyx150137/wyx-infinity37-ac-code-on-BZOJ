
#include <cstdio>
#include <map>
#include <algorithm>
using namespace std;
const int maxn=100005,s=100005,t=100006,oo=0x3f3f3f3f;
int rd()
{
    int x=0;
    char c=getchar();
    while (c<'0'||c>'9') c=getchar();
    while (c>='0'&&c<='9')
    {
        x=x*10+c-'0';
        c=getchar();
    }
    return x;
}
int fir[maxn],cur[maxn],ne[20*maxn],to[20*maxn],w[20*maxn],dep[maxn],que[maxn],
xx[maxn],yy[maxn],ww[maxn],
n,num,r,c;
map<pair<int,int>,int> id;
void add(int u,int v,int x)
{
    num++;ne[num*2]=fir[u];fir[u]=num*2;to[num*2]=v;w[num*2]=x;
    ne[num*2+1]=fir[v];fir[v]=num*2+1;to[num*2+1]=u;w[num*2+1]=0;
}
bool bfs()
{
    int u,v,hd,tl;
    for (int i=1;i<=n;i++) dep[i]=0;
    dep[t]=0;
    dep[s]=1;
    que[hd=tl=1]=s;
    while (hd<=tl)
    {
        u=que[hd++];
        for (int i=fir[u];i;i=ne[i])
            if (w[i]&&!dep[v=to[i]])
            {
                dep[v]=dep[u]+1;
                que[++tl]=v;
            }
    }
    return dep[t];
}
int dfs(int u,int lim)
{
    if (u==t) return lim;
    int v,x,ret=0;
    for (int &i=cur[u];i&&ret<lim;i=ne[i])
        if (w[i]&&dep[v=to[i]]==dep[u]+1)
        {
            x=dfs(v,min(lim-ret,w[i]));
            ret+=x;
            w[i]-=x;
            w[i^1]+=x;
        }
    return ret;
}
int main()
{
    int u,ans=0;
    c=rd();
    r=rd();
    n=rd();
    for (int i=1;i<=n;i++)
    {
        xx[i]=rd();
        yy[i]=rd();
        ww[i]=rd();
        id[make_pair(xx[i],yy[i])]=i;
    }
    for (int i=1;i<=n;i++)
        switch (xx[i]%4)
        {
            case 0:
                if (yy[i]&1) add(s,i,ww[i]);
                else
                {
                    if (id.count(make_pair(xx[i]+1,yy[i])))
                        add(id[make_pair(xx[i]+1,yy[i])],i,oo);
                    if (id.count(make_pair(xx[i],yy[i]+1)))
                        add(id[make_pair(xx[i],yy[i]+1)],i,oo);
                    if (id.count(make_pair(xx[i],yy[i]-1)))
                        add(id[make_pair(xx[i],yy[i]-1)],i,oo);
                }
                break;
            case 1:
                if (yy[i]&1)
                {
                    if (id.count(make_pair(xx[i]-1,yy[i])))
                        add(id[make_pair(xx[i]-1,yy[i])],i,oo);
                    if (id.count(make_pair(xx[i],yy[i]+1)))
                        add(id[make_pair(xx[i],yy[i]+1)],i,oo);
                    if (id.count(make_pair(xx[i],yy[i]-1)))
                        add(id[make_pair(xx[i],yy[i]-1)],i,oo);
                    if (id.count(make_pair(xx[i]+1,yy[i])))
                    {
                        u=id[make_pair(xx[i]+1,yy[i])];
                        add(i,u,min(ww[i],ww[u]));
                    }
                }
                else add(s,i,ww[i]);
                break;
            case 2:
                if (yy[i]&1)
                {
                    if (id.count(make_pair(xx[i]+1,yy[i])))
                        add(i,id[make_pair(xx[i]+1,yy[i])],oo);
                    if (id.count(make_pair(xx[i],yy[i]+1)))
                        add(i,id[make_pair(xx[i],yy[i]+1)],oo);
                    if (id.count(make_pair(xx[i],yy[i]-1)))
                        add(i,id[make_pair(xx[i],yy[i]-1)],oo);
                }
                else add(i,t,ww[i]);
                break;
            case 3:
                if (yy[i]&1) add(i,t,ww[i]);
                else
                {
                    if (id.count(make_pair(xx[i]-1,yy[i])))
                        add(i,id[make_pair(xx[i]-1,yy[i])],oo);
                    if (id.count(make_pair(xx[i],yy[i]+1)))
                        add(i,id[make_pair(xx[i],yy[i]+1)],oo);
                    if (id.count(make_pair(xx[i],yy[i]-1)))
                        add(i,id[make_pair(xx[i],yy[i]-1)],oo);
                    if (id.count(make_pair(xx[i]+1,yy[i])))
                    {
                        u=id[make_pair(xx[i]+1,yy[i])];
                        add(u,i,min(ww[i],ww[u]));
                    }
                }
        }
    while (bfs())
    {
        for (int i=1;i<=n;i++) cur[i]=fir[i];
        cur[s]=fir[s];
        cur[t]=fir[t];
        ans+=dfs(s,oo);
    }
    printf("%d\n",ans);
}
