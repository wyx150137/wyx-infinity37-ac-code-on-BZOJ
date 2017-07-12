
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#include <map>
using namespace std;
const int N = 500000+1;
const int M = 8*N;
const int inf = 0X7F7F7F7F;

int tr[M],lazy[M];

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

map<int,int>mp;

struct data
{
	int l,r,len;
	data () {}
	data (int _l,int _r)
	:l(_l),r(_r){len = r - l;}
	bool operator < (const data &z)const
	{return len < z.len;}
}a[N];

inline void updata(int k)
{
	tr[k] = max(tr[k<<1],tr[k<<1|1]);
}

inline void down(int k,int l,int r)
{
	int tmp = lazy[k];lazy[k] = 0;
	if(l==r || !tmp)return;
	tr[k<<1]+=tmp,tr[k<<1|1]+=tmp;
	lazy[k<<1]+=tmp,lazy[k<<1|1]+=tmp;
} 

void change(int k,int l,int r,int x,int y,int c)
{
	down(k,l,r);
	if(l==x && r==y){tr[k]+=c,lazy[k]+=c;return;}
	int mid = (l+r)>>1;
	if(y<=mid)change(k<<1,l,mid,x,y,c);
	else if(x>mid)change(k<<1|1,mid+1,r,x,y,c);
	else change(k<<1,l,mid,x,mid,c),change(k<<1|1,mid+1,r,mid+1,y,c);
	updata(k);
}

int V[2*N];

int main()
{
	int n , m ;
	cin >> n >> m;
	for(int i=1;i<=n;++i)
	{
		int x = read(), y = read();
		a[i] = data(x,y);
		V[++V[0]] = x,V[++V[0]] = y;
	}
	int tt = V[0];
	sort(a+1,a+n+1);
	sort(V+1,V+tt+1);
	for(int i=1;i<=tt;++i)
		if(!mp[V[i]])
			mp[V[i]] = i;
	register int j = 2, i = 1;
	change(1,1,tt,mp[a[i].l],mp[a[i].r],1);
	int ans = inf;
	while(j<=n)
	{
		change(1,1,tt,mp[a[j].l],mp[a[j].r],1);
		if(tr[1]>=m)
		{
			while(tr[1] >= m)
				change(1,1,tt,mp[a[i].l],mp[a[i].r],-1),++i;
			ans = min(ans,a[j].len-a[i-1].len);
		}
		++j;
	}
	printf("%d\n",ans == inf ? -1 : ans);
}
