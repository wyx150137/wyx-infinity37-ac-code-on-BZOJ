
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 20005;
const int INF = 0x3f3f3f3f;
int minn[N<<2],maxn[N<<2],sum[N<<2];
bool f[N<<2];
struct E{int next,to;}e[N<<1];
int w[N],deep[N],son[N],size[N],fa[N],top[N],cnt;
int x[N],y[N],val[N];
int head[N],tot,n;
void add(int x,int y)
{
    e[++tot].to = y;
    e[tot].next = head[x];
    head[x] = tot;
}
bool v[N];
void dfs1(int x,int dep)
{
    v[x] = true;
    deep[x] = dep;
    size[x]++;
    for(int i = head[x];i;i = e[i].next)
    {
        int tmp = e[i].to;
        if(!v[tmp])
        {
            dfs1(tmp,dep+1);
            fa[tmp] = x;
            size[x]+=size[tmp];
            if(size[tmp]>size[son[x]])son[x] = tmp;
        }
    }
}
void dfs2(int x,int tp)
{
    top[x] = tp;
    w[x] = ++cnt;
    if(son[x]!=0)dfs2(son[x],tp);
    for(int i = head[x];i;i = e[i].next)
        if(e[i].to!=fa[x]&&e[i].to!=son[x])
            dfs2(e[i].to,e[i].to);
}
int quan[N];
void push_up(int p)
{
    minn[p] = min(minn[p<<1],minn[(p<<1)+1]);
    maxn[p] = max(maxn[p<<1],maxn[(p<<1)+1]);
    sum[p] = sum[p<<1]+sum[(p<<1)+1];
}
void push_down(int p,int l,int r)
{
    if(l==r){f[p] = 0;return ;}
    f[p<<1] ^=1;
    f[(p<<1)+1] ^=1;
    sum[p<<1] = -sum[p<<1];sum[(p<<1)+1] = -sum[(p<<1)+1];
    swap(minn[p<<1],maxn[p<<1]);swap(minn[(p<<1)+1],maxn[(p<<1)+1]);
    minn[p<<1] = -minn[p<<1];maxn[p<<1] = -maxn[p<<1];
    minn[(p<<1)+1] = -minn[(p<<1)+1];maxn[(p<<1)+1] = -maxn[(p<<1)+1];
    f[p] = false;
}
int getans(int p,int l,int r,int a,int b,int opt)
{
    if(f[p])push_down(p,l,r);
    if(l>=a&&r<=b)
    {
        if(opt==1)return sum[p];
        else if(opt==2)return maxn[p];
        else return minn[p];
    }
    int ans;
    if(opt==1)ans= 0;
    else if(opt==2)ans = -INF;
    else ans = INF;
    int mid = (l+r)>>1;
    if(a<=mid)
    {
        if(opt==1)ans += getans(p<<1,l,mid,a,b,opt);
        else if(opt==2)ans = max(ans,getans(p<<1,l,mid,a,b,opt));
        else ans = min(ans,getans(p<<1,l,mid,a,b,opt));
    }
    if(b>mid)
    {
        if(opt==1)ans += getans((p<<1)+1,mid+1,r,a,b,opt);
        else if(opt==2)ans = max(ans,getans((p<<1)+1,mid+1,r,a,b,opt));
        else ans = min(ans,getans((p<<1)+1,mid+1,r,a,b,opt));
    }
    return ans;
}
void update(int p,int l,int r,int x,int c)
{
    if(f[p])push_down(p,l,r);
    if(l==r)
    {
        minn[p] = maxn[p] = sum[p] = c;
        return ;
    }
    int mid = (l+r)>>1;
    if(x<=mid)update(p<<1,l,mid,x,c);
    else update((p<<1)+1,mid+1,r,x,c);
    push_up(p);
}
void up_N(int p,int l,int r,int a,int b)
{
    if(f[p])push_down(p,l,r);
    if(l>=a&&r<=b)
    {
        f[p]^=1;
        minn[p] = -minn[p];maxn[p] = -maxn[p];sum[p] = -sum[p];
        swap(minn[p],maxn[p]);
        return ;
    }
    int mid = (l+r)>>1;
    if(a<=mid)up_N(p<<1,l,mid,a,b);
    if(b>mid)up_N((p<<1)+1,mid+1,r,a,b);
    push_up(p);
}
int qurey(int x,int y,int opt)
{
    int ans;
    if(opt==1)ans= 0;
    else if(opt==2)ans = -INF;
    else ans = INF;
    while(top[x]!=top[y])
    {
        if(deep[top[x]]<deep[top[y]])
            swap(x,y);
        if(opt==1)ans += getans(1,1,n,w[top[x]],w[x],opt);
        else if(opt==2) ans = max(ans,getans(1,1,n,w[top[x]],w[x],opt));
        else if(opt==3) ans = min(ans,getans(1,1,n,w[top[x]],w[x],opt));
        else up_N(1,1,n,w[top[x]],w[x]);
        x = fa[top[x]];
    }
    if(x==y)return ans;
    if(deep[x]<deep[y])swap(x,y);
    if(opt==1)ans += getans(1,1,n,w[son[y]],w[x],opt);
    else if(opt==2) ans = max(ans,getans(1,1,n,w[son[y]],w[x],opt));
    else if(opt==3) ans = min(ans,getans(1,1,n,w[son[y]],w[x],opt));
    else up_N(1,1,n,w[son[y]],w[x]);
    return ans;
}
int main()
{
    int m,xx,yy;
    scanf("%d",&n);
    for(int i = 1;i<n;i++)
    {
        scanf("%d%d%d",&x[i],&y[i],&val[i]);
        x[i]++;y[i]++;
        add(x[i],y[i]);
        add(y[i],x[i]);
    }
    dfs1(1,1);
    dfs2(1,1);
    for(int i = 1;i<n;i++)
    {
        if(deep[x[i]]>deep[y[i]])update(1,1,n,w[x[i]],val[i]);
        else update(1,1,n,w[y[i]],val[i]);
    }
    scanf("%d",&m);
    char ju[5];
    for(int i = 1;i<= m;i++)
    {
        scanf("%s%d%d",ju,&xx,&yy);
        if(ju[0]=='C')
        {
            if(deep[x[xx]]>deep[y[xx]])update(1,1,n,w[x[xx]],yy);
            else update(1,1,n,w[y[xx]],yy);
        }else if(ju[0]=='N')
            qurey(xx+1,yy+1,4);
        else if(ju[0]=='S')
            printf("%d\n",qurey(xx+1,yy+1,1));
        else if(ju[1]=='A')
            printf("%d\n",qurey(xx+1,yy+1,2));
        else printf("%d\n",qurey(xx+1,yy+1,3));
    }
    return 0;
}
