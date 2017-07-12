
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long LL;
const int mod = 19940417;
const int nmd = 17091780;
const int N = 50050;
const int INF = 1e9+5;
int fac[N],env[N];
int calc[N][25];
void init()
{
	calc[0][0] = 1;
	for(int i = 1;i<N;i++)
	{
		calc[i][0] = 1;
		for(int j = 1;j<= 20;j++)
			calc[i][j] = (calc[i-1][j-1]+calc[i-1][j])%mod;
	}
	return ;
}
int f[N<<2][21],la[N<<2],lf[N<<2];
void push_up(int p,int l,int r)
{
	int len = (r-l+1);
	int end = min(len,20);
	for(int i = 1;i<= end;i++)
	{
		f[p][i] = 0;
		for(int j = 0;j<=i;j++)
			(f[p][i]+=((LL)f[p<<1][j]*f[p<<1|1][i-j])%mod+mod)%=mod;
	}
}
int powx[21];
void push_down(int p,int l,int r)
{
	if(l==r||(lf[p]==0&&la[p]==0))return ;
	int mid = (l+r)>>1;
	if(lf[p])
	{
		for(int i = 1;i<=19;i+=2)
		{
			f[p<<1][i] = (mod-f[p<<1][i])%mod;
			f[p<<1|1][i] = (mod-f[p<<1|1][i])%mod;
		}
		lf[p<<1] = lf[p<<1]^lf[p],lf[p<<1|1] = lf[p<<1|1]^lf[p];
		la[p<<1] = (mod-la[p<<1])%mod,la[p<<1|1] = (mod-la[p<<1|1])%mod;
	}
	if(la[p])
	{
		powx[0] = 1;
		for(int i = 1;i<= 20;i++)
			powx[i] = (LL)powx[i-1]*la[p]%mod;
		for(int i = 20;i>= 1;i--)
			for(int j = 1;j<= i;j++)
			{
				(f[p<<1][i] += (LL)f[p<<1][i-j]*powx[j]%mod*calc[mid-l+1-i+j][j]%mod+mod)%=mod;
				(f[p<<1|1][i] += (LL)f[p<<1|1][i-j]*powx[j]%mod*calc[r-mid-i+j][j]%mod+mod)%=mod;
			}
		la[p<<1] += la[p],la[p<<1|1]+=la[p];
	}
	
	lf[p] = la[p] = 0;
	return ;
}
void update(int p,int l,int r,int a,int b,int c)
{
	push_down(p,l,r);
	if(l>=a&&r<=b)
	{
		if(c==INF)
		{
			for(int i = 1;i<=19;i+=2)
				f[p][i] = mod-f[p][i];
			lf[p] = lf[p]^1;
		}else
		{
			int end = min(20,(r-l+1));
			powx[0] = 1;
			for(int i = 1;i<= end;i++)
				powx[i] = (LL)powx[i-1]*c%mod;
			for(int i = end;i>= 1;i--)
				for(int j = 1;j<= i;j++)
					(f[p][i] += (LL)f[p][i-j]*powx[j]%mod*calc[r-l+1-i+j][j]%mod+mod)%=mod;
			la[p]+=c;
		}
		return ;
	}
	int mid = (l+r)>>1;
	if(a<=mid)update(p<<1,l,mid,a,b,c);
	if(b >mid)update(p<<1|1,mid+1,r,a,b,c);
	push_up(p,l,r);
}
struct E
{int t[21];};
E getans(int p,int l,int r,int a,int b)
{
	push_down(p,l,r);
	if(l>=a&&r<=b)
	{
		E a;
		a.t[0] =1;
		for(int i = 1;i<= 20;i++)
			a.t[i] = f[p][i];
		return a;
	}
	int mid=(l+r)>>1;
	if(b<=mid)
		return getans(p<<1,l,mid,a,b);
	else if(a>mid)
		return getans(p<<1|1,mid+1,r,a,b);
	else
	{
		E A = getans(p<<1,l,mid,a,mid);
		E B = getans(p<<1|1,mid+1,r,mid+1,b);
		E C;
		int len = (b-a+1);
		int end = min(len,20);
		C.t[0] = 1;
		for(int i = 1;i<= end;i++)
		{
			C.t[i] = 0;
			for(int j = 0;j<=i;j++)
				if(j<=mid-a+1&&i-j<=b-mid)(C.t[i]+=((LL)A.t[j]*B.t[i-j])%mod+mod)%=mod;
		}
		return C;
	}
}
void build(int p,int l,int r)
{
	la[p] = lf[p] = 0;
	f[p][0] =1;
	if(l==r)
	{
		scanf("%d",&f[p][1]);
		f[p][1] = (f[p][1]%mod+mod)%mod;
		return ;
	}
	int mid = (l+r)>>1;
	build(p<<1,l,mid);
	build(p<<1|1,mid+1,r);
	push_up(p,l,r);
}
int main()
{
	int n,q;
	scanf("%d%d",&n,&q);
	init();
	build(1,1,n);
	char opt[3];
	int a,b,c;
	for(int i =1;i<= q;i++)
	{
		scanf("%s",opt);
		if(opt[0]=='I')
		{
			scanf("%d%d%d",&a,&b,&c);
			update(1,1,n,a,b,c);
		}else if(opt[0]=='R')
		{
			scanf("%d%d",&a,&b);
			update(1,1,n,a,b,INF);
		}else
		{
			scanf("%d%d%d",&a,&b,&c);
			E t = getans(1,1,n,a,b);
			printf("%d\n",t.t[c]%mod);
		}
	}
	return 0;
}
