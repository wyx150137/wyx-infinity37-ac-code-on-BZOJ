
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#define N 1000000+5
#define M 4000000+5
typedef long long LL;
using namespace std;

LL tr[M],lazy[M];


inline void updata(int k)
{
	tr[k] = max(tr[k<<1],tr[k<<1|1]);
}

inline LL read()
{
	LL x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

inline void down(int k,int l,int r)
{
	if(l==r || !lazy[k])return;
	LL tmp = lazy[k];lazy[k] = 0;
	tr[k<<1] += tmp;tr[k<<1|1] += tmp;
	lazy[k<<1] += tmp;lazy[k<<1|1]+=tmp;
}

inline void change(int k,int l,int r,int x,int y,LL c)
{
	down(k,l,r);
	if(l==x && r==y){lazy[k] += c;tr[k] += c;return;}
	int mid = (l+r)>>1;
	if(y<=mid)change(k<<1,l,mid,x,y,c);
	else if(x>mid)change(k<<1|1,mid+1,r,x,y,c);
	else change(k<<1,l,mid,x,mid,c),change(k<<1|1,mid+1,r,mid+1,y,c);
	updata(k);
}

LL a[N],b[N];
LL next[N],last[N];

int main()
{
	int n = read(), m =read();
	for(int i=1;i<=n;++i)
		a[i] = read();
	for(int i=1;i<=m;++i)
		b[i] = read();
	for(int i=n;i>=1;--i)
		next[i] = last[a[i]],last[a[i]] = i;
	for(int i=1;i<=m;++i)
		if(last[i])
		{
			if(!next[last[i]])
				change(1,1,n,last[i],n,b[i]);
			else
				change(1,1,n,last[i],next[last[i]]-1,b[i]);
		}
	LL ans = 0;
	for(int i=1;i<=n;++i)
	{
		ans = max(ans,tr[1]);
		int t = next[i];
		if(t)
		{	
			change(1,1,n,i,t-1,-b[a[i]]);
			if(next[t])
				change(1,1,n,t,next[t]-1,b[a[i]]);
			else
				change(1,1,n,t,n,b[a[i]]);
		}
		else 
			change(1,1,n,i,n,-b[a[i]]);
	}
	cout<<ans<<endl;
}
