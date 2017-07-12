
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int mod = 19940417;
const int N = 60000+5;
const int M = 140000+5;
typedef long long LL;

using namespace std;

int b[25];
int C[N][21];
bool rev[M];
int lazy[M];
int a[N];

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch - '0';ch = getchar();}
	return x*f;
}

struct node
{
	int f[23];
}p[N<<2];

inline void ad(int &x,int y)
{
	x += y;
	if(x >= mod) x -= mod;
	if(x < 0) x += mod;
}

inline void calc(int k,int l,int r,int x)
{
	for(int i=1;i<=20;++i)
	{
		int tmp1 = 0;
		int tmp2 = 1;
		for(int j=i;j >= 0;--j)
		{
			ad(tmp1,(LL)p[k].f[j]*C[r-l-j+1][i-j]% mod * tmp2 % mod);
			tmp2 = (LL)tmp2 * x % mod; 
		}
		b[i] = tmp1;
	}
	for(int i=1;i<=20;++i) p[k].f[i] = b[i];
}

inline void down(int k,int l,int r)
{
	if(rev[k])
	{
		rev[k<<1] ^= 1;
		rev[k<<1|1] ^= 1;
		for(int i=1;i<=20;i+=2) p[k<<1].f[i] = (mod - p[k<<1].f[i]) % mod;
		for(int i=1;i<=20;i+=2) p[k<<1|1].f[i] = (mod-p[k<<1|1].f[i]) % mod;
		lazy[k<<1] = (mod-lazy[k<<1]) % mod;
		lazy[k<<1|1] = (mod-lazy[k<<1|1]) % mod;
		rev[k] = 0;
	}
	if(lazy[k])
	{
		int mid = (l+r) >> 1;
		ad(lazy[k<<1],lazy[k]);
		ad(lazy[k<<1|1],lazy[k]);
		calc(k<<1,l,mid,lazy[k]);
		calc(k<<1|1,mid+1,r,lazy[k]);
		lazy[k] = 0;
	}
}

inline void updata(int k)
{
	for(int i=1;i<=20;++i) p[k].f[i] = 0;
	for(int i=0;i<=20;++i)
		for(int j=0;i+j<=20;++j)
		{
			if(i+j == 0) continue;
			ad(p[k].f[i+j],(LL)p[k<<1].f[i]*p[k<<1|1].f[j]%mod);
		}
}

void build(int k,int l,int r)
{
	p[k].f[0] = 1;
	if(l==r)
	{
		p[k].f[1] = a[l];
		return;
	}
	int mid = (l+r) >> 1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
	updata(k);
}

void change_rev(int k,int l,int r,int x,int y)
{
	if(x<=l && r<=y)
	{
		rev[k] ^= 1;
		lazy[k] = (mod - lazy[k]) % mod;
		for(int i=1;i<=20;i += 2)
			p[k].f[i] = (mod-p[k].f[i]) % mod;
		return;
	}
	down(k,l,r);
	int mid = (l+r) >> 1;
	if(x <= mid)
		change_rev(k<<1,l,mid,x,y);
	if(y > mid)
		change_rev(k<<1|1,mid+1,r,x,y);
	updata(k);
}

void change_add(int k,int l,int r,int x,int y,int val)
{
	if( x<=l && r <=y)
	{
		ad(lazy[k],val);
		calc(k,l,r,val);
		return;
	}
	down(k,l,r);
	int mid = (l+r) >> 1;
	if(x <= mid) change_add(k<<1,l,mid,x,y,val);
	if(y > mid) change_add(k<<1|1,mid+1,r,x,y,val);
	updata(k);
}

node ask(int k,int l,int r,int x,int y)
{
	if(x <=l && r<=y) return p[k];
	down(k,l,r);
	node t,tmp1,tmp2;
	int mid = (l+r) >> 1;
	if(y <= mid) return  ask(k<<1,l,mid,x,y);
	else if(x > mid) return  ask(k<<1|1,mid+1,r,x,y);
	else 
	{
		tmp1 = ask(k<<1,l,mid,x,mid);
		tmp2 = ask(k<<1|1,mid+1,r,mid+1,y);
		memset(t.f,0,sizeof t.f);
		t.f[0] = 1;

		for(int i=0;i<=20;++i)
			for(int j=0;j+i<=20;++j)
			{
				if(i+j == 0) continue;
				ad(t.f[i+j],(LL)tmp1.f[i]*tmp2.f[j]% mod);
			}
		return t;
	}
}

int main()
{
	int n = read(), q = read();
	for(int i=0;i<=n;++i)
	{
		C[i][0] = C[i][i] = 1;
		for(int j=1;j<i;++j)
			C[i][j] = ( C[i-1][j] + C[i-1][j-1] ) % mod;
	}
	for(int i=1;i<=n;++i) a[i] = read(), ad(a[i],0);
	build(1,1,n);
	char str[10];
	int x,y,z;
	while(q--)
	{
		scanf("%s",str);
		if(str[0] == 'I')
		{
			x = read(), y = read(), z = read();
			ad(z,0);
			change_add(1,1,n,x,y,z);
		}
		else if(str[0] == 'R')
		{
			int x = read(), y = read();
			change_rev(1,1,n,x,y);			
		}
		else
		{
			int x = read(), y = read(), z = read();
			ad(z,0);
			node tmp = ask(1,1,n,x,y);
			printf("%d\n",tmp.f[z]%mod);
		}
	}

}
