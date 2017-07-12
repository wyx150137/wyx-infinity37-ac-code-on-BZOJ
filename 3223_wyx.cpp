
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#define N 100005
using namespace std;
int fa[N],ch[N][2],size[N];
int id[N];bool rev[N];int sz,rt;
inline int read()
{
    int x=0,f=1;char ch =getchar();
    while(ch <'0' || ch >'9'){if(ch == '-')f=-1;ch = getchar();}
    while(ch >='0'&& ch<='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
    return x*f;
}
void updata(int k)
{
    size[k]=size[ch[k][0]]+size[ch[k][1]]+1;
}
void down(int k)
{
    if(rev[k])
    {
        swap(ch[k][0],ch[k][1]);
        rev[ch[k][0]]^=1,rev[ch[k][1]]^=1;
        rev[k]=0;
    }
}
void rotate(int x,int &k)
{
    int l,r;
    int y=fa[x],z=fa[y];
    if(ch[y][0]==x)l=0;else l=1;r=l^1;
    if(y==k)k=x;
    else if(ch[z][0]==y)ch[z][0]=x;
    else ch[z][1]=x;
    fa[x]=z,fa[y]=x;fa[ch[x][r]]=y;
    ch[y][l]=ch[x][r];ch[x][r]=y;
    updata(y),updata(x);
}
void splay(int x,int &k)
{
    while(x!=k)
    {
        int y=fa[x],z=fa[y];
        if(y!=k)
        {
            if((ch[y][0]==x) ^ (ch[z][0]==y))
                rotate(x,k);
            else rotate(y,k);
        }
        rotate(x,k);
    }
}
int find(int k,int rank)
{
    down(k);
    int l=ch[k][0],r=ch[k][1];
    if(size[l]+1==rank)return k;
    else if(size[l]>=rank)return find(l,rank);
    else return find(r,rank-size[l]-1);
}
void rever(int l,int r)
{
    int x=find(rt,l),y=find(rt,r+2);
    splay(x,rt);
    splay(y,ch[x][1]);
    int z=ch[y][0];
    rev[z]^=1;
}
void build(int l,int r,int f)
{
    if(l>r)return;
    int now = id[l],last=id[f];
    if(l==r)
    {
        fa[now]=last;size[now]=1;
        if(l<f)ch[last][0]=now;
        else ch[last][1]=now;
        return;
    }
    int mid=(l+r)>>1;now=id[mid];
    build(l,mid-1,mid);build(mid+1,r,mid);
    fa[now]=last;updata(mid);
    if(mid<f)ch[last][0]=now;
    else ch[last][1]=now;
}
int main()
{
    int n=read(),m=read();
    for(int i=1;i<=n+2;++i)id[i]=++sz;
    build(1,n+2,0);rt=(n+3)>>1;
    for(int i=1;i<=m;++i){int l=read(),r=read();rever(l,r);}
    printf("%d",find(rt,2)-1);
    for(int i=3;i<=n+1;++i)
        printf(" %d",find(rt,i)-1);
    return 0;
}
