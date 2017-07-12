
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
#define LL long long
const int max_n=1e5+5;
const int max_tree=max_n*4;
const int max_m=max_n;

LL n,m,x,y,q,u,t,d,N; LL ans;
LL tot,point[max_n],nxt[max_m],v[max_m];
LL size[max_n],h[max_n],father[max_n],top[max_n],in[max_n],out[max_n],son[max_n];
LL sum[max_tree],delta[max_tree];
char opt[20];

inline void addedge(LL x,LL y)
{
    ++tot; nxt[tot]=point[x]; point[x]=tot; v[tot]=y;
}
inline void dfs_1(LL x,LL fa,LL dep)
{
    size[x]=1; h[x]=dep; father[x]=fa;
    LL maxson=0;
    for (LL i=point[x];i;i=nxt[i])
        if (v[i]!=fa)
        {
            dfs_1(v[i],x,dep+1);
            size[x]+=size[v[i]];
            if (size[v[i]]>maxson)
            {
                maxson=size[v[i]];
                son[x]=v[i];
            }
        }
}
inline void dfs_2(LL x,LL fa)
{
    if (son[fa]!=x) top[x]=x;
    else top[x]=top[fa];
    in[x]=++N;
    if (son[x]) dfs_2(son[x],x);
    for (LL i=point[x];i;i=nxt[i])
        if (v[i]!=fa&&v[i]!=son[x])
            dfs_2(v[i],x);
    out[x]=N;
}
inline void update(LL now)
{
    sum[now]=sum[now<<1]+sum[now<<1|1];
}
inline void pushdown(LL now,LL l,LL r,LL mid)
{
    if (delta[now])
    {
        sum[now<<1]+=delta[now]*(LL)(mid-l+1);
        delta[now<<1]+=delta[now];
        sum[now<<1|1]+=delta[now]*(LL)(r-mid);
        delta[now<<1|1]+=delta[now];
        delta[now]=0;
    }
}
inline void interval_change(LL now,LL l,LL r,LL lrange,LL rrange,LL v)
{
    LL mid=(l+r)>>1;
    if (lrange<=l&&r<=rrange)
    {
        sum[now]+=v*(LL)(r-l+1);
        delta[now]+=v;
        return;
    }
    pushdown(now,l,r,mid);
    if (lrange<=mid) interval_change(now<<1,l,mid,lrange,rrange,v);
    if (mid+1<=rrange) interval_change(now<<1|1,mid+1,r,lrange,rrange,v);
    update(now);
}
inline LL query(LL now,LL l,LL r,LL lrange,LL rrange)
{
    LL mid=(l+r)>>1;LL ans=0;
    if (lrange<=l&&r<=rrange) return sum[now];
    pushdown(now,l,r,mid);
    if (lrange<=mid) ans+=query(now<<1,l,mid,lrange,rrange);
    if (mid+1<=rrange) ans+=query(now<<1|1,mid+1,r,lrange,rrange);
    return ans;
}
int main()
{
    scanf("%lld",&n);
    for (LL i=1;i<n;++i)
    {
        scanf("%lld%lld",&x,&y);
        x++; y++;
        addedge(x,y);
    }
    dfs_1(1,0,1);
    dfs_2(1,0);
    scanf("%lld",&q);
    for (LL i=1;i<=q;++i)
    {
        scanf("%s",opt);
        if (opt[0]=='A')
        {
            scanf("%lld%lld%lld",&u,&t,&d);
            ++u; ++t;
            LL f1=top[u],f2=top[t];
            while (f1!=f2)
            {
                if (h[f1]<h[f2])
                {
                    swap(f1,f2);
                    swap(u,t);
                }
                interval_change(1,1,N,in[f1],in[u],d);
                u=father[f1];
                f1=top[u];
            }
            if (in[u]>in[t]) swap(u,t);
            interval_change(1,1,N,in[u],in[t],d);
        }
        else
        {
            scanf("%lld",&u);
            ++u;
            ans=query(1,1,N,in[u],out[u]);
            printf("%lld\n",ans);
        }
    }
}
