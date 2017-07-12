
#include <bits/stdc++.h>
using namespace std;
#define MAXN 3
using namespace std;
typedef  long long  LL;
LL mod,a,c,x0,n,g;
struct matrix
{
    int n,m;
    LL p[MAXN][MAXN];
};

LL fastmul(LL x,LL y)
{
    if(y==1)
    return x;
    if(y==0)
    	return 0;
    if(x==0)
    	return 0;
    if(x==1)
    	return y;
    LL tmp=fastmul(x,y/2);
    if(y%2==0)
    	return (tmp+tmp)%mod;
    else
    	return ((tmp+tmp)%mod+x)%mod;
}

matrix operator*(matrix a,matrix b)
{
    matrix c;
    c.n=a.n;
    c.m=b.m;
    for(int i=1;i<=a.n;i++)
        for(int j=1;j<=b.m;j++)
        {
            c.p[i][j]=0;
            for(int k=1;k<=a.m;k++)
                c.p[i][j]=(c.p[i][j]+(fastmul(a.p[i][k],b.p[k][j]))%mod)%mod;
        }
    return c;
}

matrix fastpow(matrix base,LL pow)
{
    matrix tmp=base,ans;
    memset(ans.p,0,sizeof(ans.p));
    for(int i=1;i<=2;i++)
        ans.p[i][i]=1;
    ans.n=ans.m=2;
    while(pow>0)
    {
        if(pow&1)
            ans=ans*tmp;
        tmp=tmp*tmp;
        pow>>=1;
    }
    return ans;
}

int main()
{
    scanf("%lld%lld%lld%lld%lld%lld",&mod,&a,&c,&x0,&n,&g);
    matrix x,y;
    x.n=x.m=y.n=y.m=2;
    x.p[1][1]=a%mod;
    x.p[1][2]=0;
    x.p[2][1]=c%mod;
    x.p[2][2]=1;
    matrix ans=fastpow(x,n);
    LL xn=fastmul(ans.p[1][1],x0)+ans.p[2][1];
    printf("%lld\n",(xn%mod)%g);
    return 0;
}
