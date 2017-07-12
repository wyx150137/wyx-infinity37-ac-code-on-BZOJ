
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
using namespace std;
typedef long long LL;
#define rep(i,j,n) for(int i=j;i<=n;i++)
char c;
bool t[4010010];
LL n,p[1000000],ans[1000000];
int T,tot,tott,len,S=10;
void pre()
{
    memset(t,true,sizeof(t));
    rep(i,2,4010000) 
    	if(t[i])
    	{
        	p[++len]=i;
       		rep(j,i,4010000/i) t[i*j]=false;
    	}
}
inline LL muti_mod(LL a,LL b,LL c)
{
    a%=c;
    b%=c;
    LL ret=0;
    while(b)
    {
        if(b&1){ret+=a;if(ret>=c)ret-=c;}
        a<<=1;
        if(a>=c)a-=c;
        b>>=1;
    }
    return ret;
}
inline LL pow_mod(LL x,LL n,LL mod)
{
    if(n==1)return x%mod;
    int bit[50],k=0;
    while(n)
    {
        bit[k++]=n&1;
        n>>=1;
    }
    LL ret=1;
    for(;k>0;k--)
    {
        ret=muti_mod(ret,ret,mod);
        if (bit[k-1]==1) ret=muti_mod(ret,x,mod);
    }
    return ret;
}
inline bool check(LL a,LL n,LL x,LL t)
{
    LL ret=pow_mod(a,x,n),last=ret;
    for(int i=1;i<=t;i++)
    {
        ret=muti_mod(ret,ret,n);
        if(ret==1&&last!=1&&last!=n-1) return true;
        last=ret;
    }
    if(ret!=1) return true;
    return false;
}
inline bool prime(LL n)
{
    if(n<2)return false;
    if(n==2)return true;
    if((n&1)==0) return false;
    LL x=n-1;LL t=0;
    while((x&1)==0){x>>=1;t++;}
    for(int i=0;i<S;i++)
    {
        LL a=rand()%(n-1)+1;
        if(check(a,n,x,t)) return false;
    }
    return true;
}
void find(LL n,int list,LL now)
{
    if(n==1){ans[tot++]=now;return;}
    if(1&n) return;
    LL N=now,m,maxi=int(sqrt(n))+1;
    rep(i,list,len) if(p[i]>maxi)break;else if(n%(p[i]-1)==0)
    {
        m=n/(p[i]-1);
        N*=p[i];
        find(m,i+1,N);
        while(m%p[i]==0)
        {
            m/=p[i];N*=p[i];
            find(m,i+1,N);
        }
        N=now;
    }
    if(n+1>=p[list])
    {
        if(n+1>p[len]){if(prime(n+1))ans[tot++]=N*(n+1);}
        else{if(t[n+1])ans[tot++]=N*(n+1);}
    }
}
int main()
{
    scanf("%d",&T);
    pre();
    while(T--)
    {
        scanf("%lld",&n);tot=0;
        if(1&n){
            if(n==1){puts("2");puts("1 2");}else puts("0"),puts("");
            continue;
        }
        find(n,1,1);
        sort(ans,ans+tot);
        printf("%d\n",tot);
        rep(i,0,tot-2) printf("%lld ",ans[i]);
        if(tot)printf("%lld\n",ans[tot-1]);else{puts("");};
    }
}
