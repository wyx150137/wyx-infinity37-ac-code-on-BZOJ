
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1e5+5;
const int M = 8e5+5;
typedef double db;
typedef long long ll;
const int mod = 1e9+7;
const db PI = 3.14159265358979323;
char s[N];
struct cp
{
	db x,y;
	friend cp operator+(const cp &a,const cp &b)
	{
		return (cp){a.x+b.x,a.y+b.y};
	}
	friend cp operator-(const cp &a,const cp &b)
	{
		return (cp){a.x-b.x,a.y-b.y};
	}
	friend cp operator*(const cp &a,const cp &b)
	{
		return (cp){a.x*b.x-a.y*b.y,a.x*b.y+a.y*b.x};
	}
}a[M],b[M],c[M];
void FFT(cp *a,int len,int type)
{
	int t = 0;
	for(int i= 0;i<len;i++)
	{
		if(t<i)swap(a[i],a[t]);
		for(int j = len>>1;(t^=j)<j;j>>=1);
	}
	for(int i = 2;i<=len;i<<=1)
	{
		cp wn = (cp){cos(2*PI*type/i),sin(2*PI*type/i)};
		for(int j = 0;j<len;j+=i)
		{
			cp w = (cp){1,0},tmp;
			for(int k = 0;k<(i>>1);k++,w = w*wn)
			{
				tmp = w*a[j+k+(i>>1)];
				a[j+k+(i>>1)] = a[j+k]-tmp;
				a[j+k] = a[j+k]+tmp;
			}
		}
	}
	if(type==-1)
		for(int i = 0;i<len;i++)
			a[i].x/=len;
}
int ans[M];
void conv(cp *a,cp *b,cp *c,int len)
{
	FFT(a,len,1);FFT(b,len,1);
	for(int i = 0;i<len;i++)c[i] = a[i]*b[i];
	FFT(c,len,-1);
	for(int i = 0;i<len;i++)
		ans[i] += (int)(c[i].x+0.1);
}
int pow2[N<<1];
void init()
{
	pow2[0] = 1;
	for(int i = 1;i<N*2;i++)
		pow2[i] = pow2[i-1]*2%mod;
}
char tt[N<<1];int p[N<<1],no[N<<1];
ll tot,Ans;
void manacher(int n)
{
	int lth = 0;
	int maxp = 1,id = 1;
	for(int i = 0;i<n;i++)
	{
		tt[++lth] = s[i];
		no[lth] = i+1;
		if(i!=n-1)tt[++lth]='^';
	}
	for(int i = 1;i<= lth;i++)
	{
		if(maxp>i)p[i] = min(p[id*2-i],maxp-i);
		else p[i] = 0;
		while(i+p[i]<=lth&&i-p[i]>=1&&tt[i+p[i]]==tt[i-p[i]])p[i]++;
		p[i]--;
		if(i+p[i]>maxp)maxp = i+p[i],id = i;
		tot+=(no[i+p[i]]?no[i+p[i]]:no[i+p[i]-1])-(no[i]?no[i]:no[i+1])+1;
	}
}
int main()
{
	init();
	scanf("%s",s);
	int n = strlen(s);
	for(int i = 0;i<n;i++)
	{
		a[i].x = (s[i]=='b')?0:1;
		b[i].x = a[i].x;
		a[i].y = b[i].y = 0;
	}
	int len = 1,m= 2*n;
	while(len<=m)len = len<<1;
	len = len<<1;
	conv(a,b,c,len);
	//for(int i = 0;i<len;i++)
	//	printf("%d ",ans[i]);
	//printf("\n");
	for(int i = 0;i<len;i++)
	{
		if(i<n)a[i].x = (s[i]=='a')?0:1;
		else a[i].x = 0;
		b[i].x = a[i].x;
		a[i].y = b[i].y = c[i].x = c[i].y = 0;
	}
	conv(a,b,c,len);
	//for(int i = 0;i<m-1;i++)
	//	printf("%d ",ans[i]);
	for(int i = 0;i<m;i++)
	{
		int tmp = (ans[i]+1)>>1;
		(Ans+=pow2[tmp]-1)%=mod;
	}
	manacher(n);
	Ans = ((Ans-tot)%mod+mod)%mod;
	printf("%lld\n",Ans);
	return 0;
}
