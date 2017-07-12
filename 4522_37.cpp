
#include<cstdio>
#include<algorithm>
#include<cmath>
#define fo(i,a,b) for(i=a;i<=b;i++)
using namespace std;
typedef long long ll;
ll e,d,n,nn,r,c,a,xx,yy,t,p,q,mod;
void gcd(ll a,ll b)
{
    if (!b)
    {
        xx=1;
        yy=0;
        t=a;
    }
    else
    {
        gcd(b,a%b);
        swap(xx,yy);
        yy-=xx*(a/b);
    }
}
ll getny(ll x,ll y)
{
    gcd(x,y);
    xx=(xx%y+y)%y;
    return xx;
}
int rand() 
{
    static int rand_seed=1e9+7;
    rand_seed+=rand_seed<<1|1;
    return rand_seed;
}
ll quick_plus(ll x,ll y)
{
    if (!y) return 0;
    ll t=quick_plus(x,y/2);
    t=(t+t)%mod;
    if (y%2) t=(t+x)%mod;
    return t;
}
ll quick_pow(ll x,ll y)
{
    if (!y) return 1;
    ll t=quick_pow(x,y/2);
    t=quick_plus(t,t);
    if (y%2) t=quick_plus(t,x);
    return t;
}
ll f(ll x)
{
    return (quick_plus(x,x)+a)%mod;
}
ll pollard_rho(ll n)
{
    ll r1,r2,p;
    while (1)
    {
        a=rand()%100;
        r1=r2=2;
        do{
            r1=f(r1);
            r2=f(f(r2));
            gcd(abs(r2-r1),n);
            p=t;
            if (p>1) return p;
        }while (r1!=r2);
    }
}
int main()
{
    scanf("%lld%lld%lld",&e,&n,&c);
    mod=n;
    p=pollard_rho(n);
    q=n/p;
    r=(p-1)*(q-1);
    d=getny(e,r);
    nn=quick_pow(c,d);
    printf("%lld %lld\n",d,nn);
}
