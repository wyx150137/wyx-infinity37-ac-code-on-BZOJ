
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 100000+5;
const int M = N << 5;

typedef long long LL;

int fa[N];
int T[N];
int size[N];

int find(int x)
{
	return fa[x]^x?fa[x] = find(fa[x]) : fa[x];
}

void Union(int x,int y)
{
	int fx = find(x),fy = find(y);
	if(fx == fy) return ;
	if(size[fx] < size[fy]) swap(fx,fy);
	fa[fy] = fx,size[fx] += size[fy];
}

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch - '0';ch = getchar();}
	return x*f;
}

int sz;

int tr[M],ls[M],rs[M],root[N];

inline void updata(int k)
{
	tr[k] = tr[ls[k]] + tr[rs[k]];
}

void change(int &k,int l,int r,int pos)
{
	if(!k) k = ++sz;
	if(l==r){tr[k]=1;return;}
	int mid = (l+r)>>1;
	if(pos <= mid) change(ls[k],l,mid,pos);
	else change(rs[k],mid+1,r,pos); updata(k);
}

int ask(int k,int l,int r,int size)
{
	if(l==r)return l;
	int mid = (l+r)>>1;
	if(tr[ls[k]] >= size) return ask(ls[k],l,mid,size);
	else return ask(rs[k],mid+1,r,size-tr[ls[k]]);
}

int merge(int x,int y)
{
	if(!x) return y;
	if(!y) return x;
	ls[x] = merge(ls[x],ls[y]);
	rs[x] = merge(rs[x],rs[y]);
	updata(x); return x;
}

int V[N];

int main()
{
	int n = read(), m = read();
	for(int i=1;i<=n;++i) V[i] = read(),size[fa[i] = i] = 1;
	for(int i=1;i<=m;++i) Union(read(),read());
	for(int i=1;i<=n;++i) change(root[find(i)],1,n,V[i]),T[V[i]] = i;
	int Q = read();char str[10];
	while(Q--)
	{
		scanf("%s",str);
		int x = read(),y = read();
		if(str[0] == 'Q')
		{
			int fx = find(x);
			if(tr[root[fx]] < y) {puts("-1");continue;}
			printf("%d\n",T[ask(root[fx],1,n,y)]);
		}
		else
		{
			int fx = find(x),fy = find(y);
			if(fx ^ fy)
			{
				fa[fy] = fx;
				root[fx] = merge(root[fx],root[fy]);
			}
		}
	}
}
