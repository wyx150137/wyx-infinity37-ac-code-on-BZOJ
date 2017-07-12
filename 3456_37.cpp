
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1<<18;
typedef long long ll;
const int mod = 1004535809;
int fac[N],env[N],cnt;
int quick_pow(int x,int y)
{
	int res = 1;
	while(y)
	{
		if(y&1)res = (ll)res*x%mod;
		x = (ll)x*x%mod;
		y = y>>1;
	}
	return res;
}
int a[N],b[N],c[N];
void NTT(int *a,int len,int type)
{
	int t = 0;
	for(int i = 0;i<len;i++)
	{
		if(t<i)swap(a[t],a[i]);
		for(int j = (len>>1);(t^=j)<j;j>>=1);
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
				a[j+k+(i>>1)]=(a[j+k]-tmp+mod)%mod;
				a[j+k] = (a[j+k]+tmp)%mod;
			}
		}
	}
	if(type==-1)
	{
		for(int i = 1;i<(len>>1);i++)
			swap(a[i],a[len-i]);
		int Inv = quick_pow(len,mod-2);
		for(int i = 0;i<len;i++)
			a[i] = (ll)a[i]*Inv%mod;
	}
	/*printf("#case %d:",++cnt);
	for(int i = 0;i<len;i++)
		printf("%d ",a[i]);
	printf("\n");*/
}
void Get_Inv(int *a,int *b,int len)
{
	if(len==1)
	{
		b[0] = quick_pow(a[0],mod-2);
		return ;
	}
	Get_Inv(a,b,len>>1);
	static int tmp[N];
	memcpy(tmp,a,sizeof(int)*len);
	memset(tmp+len,0,sizeof(int)*len);
	NTT(tmp,len<<1,1);
	NTT(b,len<<1,1);
	for(int i = 0;i<len<<1;i++)b[i]=(ll)b[i]*(2-(ll)b[i]*tmp[i]%mod+mod)%mod;
	NTT(b,len<<1,-1);
	memset(b+len,0,sizeof(int)*len);
}
int C(int n)
{
	return ((ll)n*(n-1)>>1)%(mod-1);
}
int main()
{
	int n,m=1;
	scanf("%d",&n);
	for(m=1;m<=n;m<<=1);
	fac[0]=1,env[0]=1;
	for(int i =1;i<=m;i++)
		fac[i] = (ll)fac[i-1]*i%mod;
	env[m] = quick_pow(fac[m],mod-2);
	for(int i = m-1;i>=1;i--)
		env[i] = (ll)env[i+1]*(i+1)%mod;
	for(int i = 0;i< m;i++)
		b[i] = (ll)quick_pow(2,C(i))*env[i]%mod;
	for(int i = 1;i< m;i++)
		c[i] = (ll)quick_pow(2,C(i))*env[i-1]%mod;
	static int tmp[N];
	memset(tmp,0,sizeof(tmp));
	Get_Inv(b,tmp,m);
	NTT(c,m<<1,1);
	NTT(tmp,m<<1,1);
	for(int i = 0;i<m<<1;i++)a[i]=(ll)c[i]*tmp[i]%mod;
	NTT(a,m<<1,-1);
	printf("%lld\n",(ll)a[n]*fac[n-1]%mod);
	return 0;
}
