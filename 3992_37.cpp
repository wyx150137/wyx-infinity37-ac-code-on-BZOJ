
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int MOD = 1004535809;
const int M = 16400;
const int G = 3;
int n,m,d,X,S;
int ind[M];
ll quick_pow(ll x,ll y,ll mod)
{
	if(y==0)return 1;
	ll tmp = quick_pow(x,y>>1,mod);
	if(y&1)return tmp*tmp%mod*x%mod;
	else return tmp*tmp%mod;
}
void NTT(int a[],int len,int type)
{
	static int tmp[M];
	if(len==1)return ;
	for(int i = 0;i<len;i+=2)
		tmp[i>>1] = a[i],tmp[(i+len)>>1]=a[i+1];
	memcpy(a,tmp,sizeof(a[0])*len);
	int *l = a,*r = a+(len>>1);
	NTT(l,len>>1,type);
	NTT(r,len>>1,type);
	ll w = quick_pow(G,(ll)type*(MOD-1)/len%(MOD-1),MOD),wn=1;
	for(int i = 0;i<(len>>1);i++,(wn*=w)%=MOD)
		tmp[i]=(l[i]+wn*r[i]%MOD)%MOD,tmp[i+(len>>1)]=((l[i]-wn*r[i]%MOD)%MOD+MOD)%MOD;
	memcpy(a,tmp,sizeof(a[0])*len);
	return ;
}
struct F
{
	int a[M];
	F(){}
	F(bool x)
	{
		memset(a,0,sizeof(a));
		a[0]=1;
	}
	int& operator[](int x)
	{
		return a[x];
	}
	F& operator*=(const F &s)
	{
		static int b[M];
		memcpy(b,s.a,sizeof(b));
		NTT(a,d,1);
		NTT(b,d,1);
		for(int i = 0;i<d;i++)
			a[i]=(ll)a[i]*b[i]%MOD;
		NTT(a,d,MOD-2);
		for(int i = m-1;i<= (m-2)<<1;i++)
			(a[i-(m-1)]+=a[i])%=MOD,a[i]=0;
		ll inv = quick_pow(d,MOD-2,MOD);
		for(int i=0;i<=m-2;i++)
			a[i]=a[i]*inv%MOD;
		return *this;
	}
}f;
int GPR()
{
	static int s[30];
	int x = m-1;
	for(int i = 2;i*i<=x;i++)
		if(x%i==0)
		{
			s[++s[0]]=i;
			while(x%i==0)x/=i;
		}
	if(x!=1)s[++s[0]]=x;
	for(int g = 2;;g++)
	{
		int j;
		for(j = 1;j<=s[0];j++)
			if(quick_pow(g,(m-1)/s[j],m)==1)
				break;
		if(j==s[0]+1)return g;
	}
}
F Quick_pow(F &a,int y)
{
	F re(true);
	while(y)
	{
		if(y&1)re*=a;
		a*=a,y>>=1;
	}
	return re;
}
int main()
{
	scanf("%d%d%d%d",&n,&m,&X,&S);
	for(d=1;d<=m+m;d<<=1);
	int g = GPR();
	for(int i = 0,x=1;i<m-1;i++,(x*=g)%=m)
		ind[x]=i;
	int x;
	for(int i = 1;i<= S;i++)
	{
		scanf("%d",&x);
		if(!x)continue;
		f[ind[x]] = 1;
	}
	F ans = Quick_pow(f,n);
	printf("%d\n",ans[ind[X]]);
	return 0;
}
