
#include <bits/stdc++.h>
#define N 100005
typedef long long ll;
using namespace std;
int n,q,ans,tot,num;
struct Link_Cut_Tree
{
    int c[N][2],fa[N],size1[N],size2[N],q[N],top;
    bool rev[N];
    inline void pushup(int x)
    {
        int l=c[x][0],r=c[x][1];
        size1[x]=size1[l]+size1[r]+size2[x];
    }
    inline bool isroot(int x)
    {return c[fa[x]][1]!=x&&c[fa[x]][0]!=x;}
    inline void pushdown(int x)
    {
        int l=c[x][0],r=c[x][1];
        if(rev[x])
        {
            rev[l]^=1;rev[r]^=1;rev[x]^=1;
            swap(c[x][0],c[x][1]);
        }
    }
    inline void rotate(int x)
    {
        int y=fa[x],z=fa[y],l,r;
        if(c[y][0]==x)l=0;else l=1;r=l^1;
        if(!isroot(y)){if(c[z][0]==y)c[z][0]=x;else c[z][1]=x;}
        fa[x]=z;fa[y]=x;fa[c[x][r]]=y;
        c[y][l]=c[x][r];c[x][r]=y;
        pushup(y);pushup(x);
    }
    inline void splay(int x)
    {
        top=1;q[top]=x;
        for(int i=x;!isroot(i);i=fa[i])q[++top]=fa[i];
        for(int i=top;i;i--)pushdown(q[i]);
        while(!isroot(x))
        {
            int y=fa[x],z=fa[y];
            if(!isroot(y))
            {
                if((c[z][0]==y)^(c[y][0]==x))rotate(x);
                else rotate(y);
            }
            rotate(x);
        }
        pushup(x);
    }
    void access(int x)
    {
        for(int t=0;x;t=x,x=fa[x])
        {
            splay(x);size2[x]+=size1[c[x][1]];
            c[x][1]=t;size2[x]-=size1[t];pushup(x);
        }
    }
    void makeroot(int x){access(x);splay(x);rev[x]^=1;}
    int find(int x){access(x);splay(x);while(c[x][0])x=c[x][0];return x;}
    void split(int x,int y){makeroot(x);access(y);splay(y);}
    void link(int x,int y)
    {
        makeroot(x);makeroot(y);fa[x]=y;size2[y]+=size1[x];
        pushup(y);
    }
    void cut(int x,int y){split(x,y);if(c[y][0]==x)c[y][0]=0,fa[x]=0;}
    void init(int n)
    {
        for(int i=1;i<=n;i++)size1[i]=size2[i]=1;
    }
}T;
int main()
{
    scanf("%d%d",&n,&q);
    T.init(n);char s[10];
    while(q--)
    {
        scanf("%s",s);
        int x,y;
        scanf("%d%d",&x,&y);
        if(s[0]=='A')T.link(x,y);
        else
        {
            T.makeroot(x);T.access(y);T.splay(x);
            printf("%lld\n",(ll)((T.size2[y])*(T.size1[x]-T.size2[y])));
        }
    }
    return 0;
}
