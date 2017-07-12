
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#define N 200000+5
#define M 8000000+5
using namespace std;
typedef long long LL;
int ls[M],rs[M],l[M],r[M];
int size[M],v[M],root[M];

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int n,sz;
int mempool;

void build_a_tree(int x)
{
	v[x] = read();
	if(!v[x])
	{
		l[x] = ++sz;
		build_a_tree(l[x]);
		r[x] = ++sz;
		build_a_tree(r[x]);
	}
}

void updata(int k)
{
	size[k] = size[ls[k]] + size[rs[k]];
}

inline void insert(int &k,int l,int r,int val)
{
	if(!k) k = ++mempool;
	if(l==r){size[k] = 1;return;}
	int mid = (l+r)>>1;
	if(val <= mid)
		insert(ls[k],l,mid,val);
	else insert(rs[k],mid+1,r,val);
	updata(k);	
}

LL cnt1 , cnt2;

int merge(int x,int y)
{
	if(!x) return y;
	if(!y) return x;
	cnt1 += (LL)size[rs[x]] * size[ls[y]];
	cnt2 += (LL)size[ls[x]] * size[rs[y]];
	ls[x] = merge(ls[x],ls[y]);
	rs[x] = merge(rs[x],rs[y]);
	updata(x);
	return x;
}

LL ans = 0;

void solve(int x)
{
	if(!x)return;
	solve(l[x]);solve(r[x]);
	if(!v[x])
	{
		cnt1 = cnt2 = 0;
		root[x] = merge(root[l[x]],root[r[x]]);
		ans += min(cnt1,cnt2);
	}
}

int main()
{	
	int n = read();
	++sz;
	build_a_tree(1);
	for(int i=1;i<=sz;++i)
		if(v[i])
			insert(root[i],1,n,v[i]);
	solve(1);
	cout<<ans;
}
