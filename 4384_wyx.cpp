
#include <bits/stdc++.h>
using namespace std;
#define N 1100000
int n,lim,ans;
char s[N];
struct node 
{
    int a,b,c,pos;
    node(){}
    node(int a,int b,int c,int pos):a(a),b(b),c(c),pos(pos){}
    friend bool operator < (const node &r1,const node &r2)
    {return r1.a<r2.a;};
}p[N];
struct diw_tree
{
    int mx[N<<1],sx[N<<1],cx[N<<1],mn[N<<1],sn[N<<1],cn[N<<1];
    void init()
    {
        memset(mx,-0x3f,sizeof(mx));
        memset(sx,-0x3f,sizeof(sx));
        memset(mn,0x3f,sizeof(mn));
        memset(sn,0x3f,sizeof(sn));
    }
    void insert(int x,int y,int v)
    {
        for(int i=x;i<=lim;i+=i&-i)
        {
            if(v>mx[i])
            {
                if(cx[i]!=y)sx[i]=mx[i];
                mx[i]=v;cx[i]=y;
            }
            else if(y!=cx[i])
                sx[i]=max(sx[i],v);
            if(v<mn[i])
            {
                if(cn[i]!=y)sn[i]=mn[i];
                mn[i]=v;cn[i]=y;
            }
            else if(y!=cn[i])
                sn[i]=min(sn[i],v);
        }
    }
    inline void query(int x,int y,int v)
    {
        for(int i=x;i;i-=i&-i)
        {
            if(cx[i]!=y)ans=max(ans,mx[i]-v);
            else ans=max(ans,sx[i]-v);
            if(cn[i]!=y)ans=max(ans,v-mn[i]);
            else ans=max(ans,v-sn[i]);
        }
    }
}tr1,tr2;
int main()
{
    scanf("%d",&n);lim=(n+1)<<1;
    scanf("%s",s+1);
    for(int i=1,j;i<=n;i++)
    {
        j=i;
        while(s[j]==s[i]&&j<=n)j++;j--;
        ans=max(ans,j-i+1);i=j;
    }
    for(int i=1,a=0,b=0,c=0;i<=n;i++)
    {
        if(s[i]=='B')a++;
        if(s[i]=='C')b++;
        if(s[i]=='S')c++;
        p[i]=node(a-b,b-c,c-a,i);
    }
    tr1.init();tr2.init();
    sort(p,p+1+n);
    for(int i=0,j;i<=n;i++)
    {
        j=i;
        while(p[j].a==p[i].a&&j<=n)j++;j--;
        for(int k=i;k<=j;k++)
        {
            tr1.query(p[k].b-1+n+1,p[k].c,p[k].pos);
            tr2.query(n-(p[k].b+1)+1,p[k].c,p[k].pos);
        }
        for(int k=i;k<=j;k++)
        {
            tr1.insert(p[k].b+n+1,p[k].c,p[k].pos);
            tr2.insert(n-p[k].b+1,p[k].c,p[k].pos);
        }
        i=j;
    }
    printf("%d\n",ans);
    return 0;
} 
