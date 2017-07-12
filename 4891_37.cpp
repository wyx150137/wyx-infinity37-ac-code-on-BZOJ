
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef long double ld;
int n,m,k;
ll b[100005],a[22][100005],M;
int fp,ts[100];
ll fs[100];
ll mul(ll a,ll b,ll c)
{
    if(c<=2000000000ll)return a*b%c;
    ll r=a*b-ll(ld(a)/c*b)*c;
    if(r>=c||r<=-c)r%=c;
    return r>=0?r:r+c;
}
ll pw(ll a,ll n,ll P)
{
    ll v=1;
    for(;n;n>>=1,a=mul(a,a,P))if(n&1)v=mul(v,a,P);
    return v;
}
ll gcd(ll a,ll b)
{
    if(a<0)a=-a;
    for(ll c;b;c=a,a=b,b=c%b);
    return a;
}
bool mr(ll n)
{
    ll z=n-1;
    int t=0;
    while(~z&1)z>>=1,++t;
    for(int i=0;i<15;++i)
    {
        ll a=rand()%(n-1)+1;
        ll x=pw(a,z,n);
        for(int j=0;j<t;++j)
        {
            ll y=mul(x,x,n);
            if(y==1&&x!=1&&x!=n-1)return 0;
            x=y;
        }
        if(x!=1)return 0;
    }
    return 1;
}
ll get(ll x,int c)
{
    int i=1,j=2;
    ll a=(rand()^ll(rand())<<31)%(x-1)+1,b=a;
    while(1)
    {
        a=mul(a,a,x);
        if((a+=c)>=x)a%=x;
        ll p=gcd(a-b,x);
        if(p!=1)return p;
        if((++i)==j)j<<=1,b=a;
    }
}
void calc(ll n)
{
    if(n==1)return;
    if(mr(n))
    {
        fs[fp++]=n;
        return;
    }
    for(int c=12347;;++c)
    {
        ll a=get(n,c);
        if(a!=n)
        {
            ll b=gcd(a,n/a);
            calc(a/b);
            calc(n/a/b);
            calc(b);
            return;
        }
    }
}
ll cal(ll*b,ll*a,ll M)
{
    fp=0;
    calc(M);
    std::sort(fs,fs+fp);
    fp=std::unique(fs,fs+fp)-fs;
    ll phi_M=M;
    for(int i=0;i<fp;++i)ts[i]=0,phi_M=phi_M/fs[i]*(fs[i]-1);
    ll B=1,A=1,x;
    for(int i=1;i<=m;++i)
    {
        x=b[i];
        if(fs[0]==2)for(;~x&1;x>>=1,++ts[0]);
        for(int j=(fs[0]==2);j<fp;++j)
        {
            for(ll p=fs[j],y=x/p;y*p==x;x=y,y=y/p,++ts[j]);
        }
        B=mul(B,x,M);
    }
    for(int i=1;i<=m;++i)
    {
        x=a[i];
        if(fs[0]==2)for(;~x&1;x>>=1,--ts[0]);
        for(int j=(fs[0]==2);j<fp;++j)
        {
            for(ll p=fs[j],y=x/p;y*p==x;x=y,y=y/p,--ts[j]);
        }
        A=mul(A,x,M);
    }
    B=mul(B,pw(A,phi_M-1,M),M);
    for(int i=0;i<fp;++i)
    {
        if(ts[i]<0)return -1;
        B=mul(B,pw(fs[i],ts[i],M),M);
    }
    return B;
}
int main()
{
    srand(200037);
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=m;++i)scanf("%lld",&b[i]);
    for(int t=1;t<=n;++t)
    	for(int i=1;i<=m;++i)
    		scanf("%lld",&a[t][i]);
    for(int i=0;i<k;++i)
    {
    	int x;
    	scanf("%d%lld",&x,&M);
        printf("%lld\n",cal(b,a[x],M));
    }
    return 0;
}
