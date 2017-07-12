
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#define max(a,b) ((a)>(b)?(a):(b))
#define getmax() max(tr[1][0],max(tr[1][1],max(tr[1][2],tr[1][3])))
typedef long long LL;
const int N = 40000+5;
const int M = N << 2;
using namespace std;

const int F[4][4] = {
	{ 0, 3, 0, 3},
	{-1, 1, 2,-1},
	{ 2, 1, 2, 1},
	{-1, 3, 0,-1}
};

int tr[M][4];

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

inline void updata(int k)
{
	memset(tr[k],-0x3f,sizeof tr[k]);
	for(int i=0;i<4;++i)
		for(int j=0;j<4;++j)
			if(F[i][j]!=-1)
				tr[k][F[i][j]] = max(tr[k][F[i][j]],tr[k<<1][i]+tr[k<<1|1][j]);
}

inline void change(int k,int l,int r,int pos,int x)
{
	if(l==r)
	{
		tr[k][3] = x;
		tr[k][0] = tr[k][1] = -100000000; 
		return;
	}
	int mid = (l+r) >> 1;
	if(pos <= mid)change(k<<1,l,mid,pos,x);
	else change(k<<1|1,mid+1,r,pos,x);
	updata(k);
}

int main()
{
	int n = read(), d = read(),pos,x;
	for(int i=1;i<=n;++i) change(1,1,n,i,read());
	LL ans = 0;
	for(int i=1;i<=d;++i)
	{
		pos = read(),x = read();
		change(1,1,n,pos,x);
		ans = ans + getmax();
	}
	cout << ans << endl;
}
