
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 261244<<1;
typedef long long ll;
const int mod = 998244353;
const int Inv2 = 499122177;
int a[N],b[N],c[N],cnt=0;
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
	int t = 0,i,j,k,wn,tmp,w;
	for(i = 0;i<len;i++)
	{
		if(t<i)swap(a[i],a[t]);
		for(j = len>>1;(t^=j)<j;j=j>>1);
	}
	for(i = 2;i<= len;i<<=1)
	{
		wn = quick_pow(5,(mod-1)/i);
		for(j = 0;j<len;j+=i)
		{
			w = 1;
			for(k = 0;k<(i>>1);k++,w=(ll)w*wn%mod)
			{
				tmp = (ll)a[j+k+(i>>1)]*w%mod;
				a[j+k+(i>>1)] = (a[j+k]-tmp+mod)%mod;
				a[j+k] = (a[j+k]+tmp)%mod;
			}
		}
	}
	if(type==-1)
	{
		for(i = 1;i<(len>>1);i++)
			swap(a[i],a[len-i]);
		int Inv = quick_pow(len,mod-2);
		for(i = 0;i<len;i++)
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
	for(int i = 0;i<len<<1;i++)b[i] = (ll)b[i]*(2-(ll)b[i]*tmp[i]%mod+mod)%mod;
	NTT(b,len<<1,-1);
	memset(b+len,0,sizeof(ll)*len);
}
void Get_Root(int *a,int *b,int len)
{
	if(len==1)
	{
		b[0] = 1;
		return ;
	}
	Get_Root(a,b,len>>1);
	static int tmpa[N],tmpb[N];
	memset(tmpb,0,sizeof(int)*len);  
    memset(tmpb+len,0,sizeof(int)*len);
	Get_Inv(b,tmpb,len);
	memcpy(tmpa,a,sizeof(int)*len);
	memset(tmpa+len,0,sizeof(int)*len);
	NTT(tmpa,len<<1,1),NTT(b,len<<1,1),NTT(tmpb,len<<1,1);
	for(int i = 0;i<len<<1;i++)b[i] = (ll)(b[i]+(ll)tmpa[i]*tmpb[i]%mod)%mod*Inv2%mod;
	NTT(b,len<<1,-1);
	memset(b+len,0,sizeof(int)*len);
}
int main()
{
	int n,m,k;
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= n;i++)
	{
		scanf("%d",&k);
		if(k<=m)a[k]++;
	}
	int len = 1;
	for(int i=1<<30;i;i>>=1)  
        if(m&i)  
            {len=i<<1;break;} 
	for(int i = 0;i<len;i++)
		if(a[i])a[i]=mod-4;
	a[0]++;
	Get_Root(a,b,len);
	memcpy(a,b,sizeof(int)*len);
	a[0]++;
	memset(b,0,sizeof(int)*len);
	Get_Inv(a,b,len);
	for(int i = 1;i<= m;i++)
		printf("%d\n",b[i]*2%mod);
	return 0;
}
