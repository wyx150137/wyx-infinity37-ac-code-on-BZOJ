
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 261244*2;
const int mod = 998244353;
int quick_pow(int x,int y)
{
    int res = 1;
    while(y)
    {
        if(y&1)res = (ll)res*x%mod;
        x = (ll)x*x%mod;
        y>>=1;
    }
    return res;
}
void NTT(int *a,int len,int type)
{
	//for(int i = 0;i<len;i++)printf("%d ",a[i]);
	//printf("\n");
    int t = 0;
    for(int i = 0;i<len;i++)
    {
        if(t<i)swap(a[t],a[i]);
        for(int j = len>>1;(t^=j)<j;j>>=1);
    }
    for(int i = 2;i<= len;i<<=1)
    {
        int wn = quick_pow(3,(mod-1)/i);
        for(int j = 0;j<len;j+=i)
        {
            int w = 1,tmp;
            for(int k = 0;k<(i>>1);k++,w=(ll)w*wn%mod)
            {
                tmp = (ll)a[j+k+(i>>1)]*w%mod;
                a[j+k+(i>>1)] = (a[j+k]-tmp)%mod;
                a[j+k] = (a[j+k]+tmp)%mod;
            }
        }
    }
    if(type==-1)
    {
        for(int i = 1;i<len>>1;i++)swap(a[i],a[len-i]);
        int Inv = quick_pow(len,mod-2);
        for(int i = 0;i<len;i++)
            a[i] = (ll)a[i]*Inv%mod;
    }
	//for(int i = 0;i<len;i++)printf("%d ",a[i]);
	//printf("\n");
}
void conv(int *a,int *b,int *c,int len)
{
    NTT(a,len,1),NTT(b,len,1);
    for(int i = 0;i<len;i++)c[i]=(ll)a[i]*b[i]%mod;
    NTT(c,len,-1);
}
int fac[N],env[N],a[N],b[N],c[N];
int main()
{
    int n,len=1;
    scanf("%d",&n);
    for(;len<=2*n;len<<=1);
    fac[0] = 1;
    for(int i = 1;i<= n;i++)fac[i]=(ll)fac[i-1]*i%mod;
    env[n] = quick_pow(fac[n],mod-2);
    for(int i = n-1;i>=0;i--)env[i] = (ll)env[i+1]*(i+1)%mod;
    for(int i = 0;i<= n;i++)a[i]=i%2?-env[i]:env[i];
    b[0]=1,b[1]=n+1;
    for(int i = 2;i<= n;i++)b[i]=(ll)(quick_pow(i,n+1)-1)*quick_pow(i-1,mod-2)%mod*env[i]%mod;
    conv(a,b,c,len);
    int j = 1,ans=0;
    for(int i = 0;i<=n;i++)
    {
        if(i)j=(ll)j*i%mod;
        ans=(ans+(ll)quick_pow(2,i)*fac[i]%mod*c[i]%mod)%mod;
        ans = (ans+mod)%mod;
    }
    printf("%d\n",(ans%mod+mod)%mod);
    return 0;
}
