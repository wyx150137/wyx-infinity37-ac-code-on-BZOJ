
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 5e5+5;
struct Seg
{
	ll sum,v,lazy,del;
	Seg(){lazy = -1;}
}t[N<<2];
ll a[N],sum[N];
inline int id(int l,int r){return (l+r)|(l!=r);}
void add_day(int l,int r,ll d)
{
	t[id(l,r)].v += d*a[r];
	t[id(l,r)].sum += (sum[r]-sum[l-1])*d;
	t[id(l,r)].del+=d;
}
void push_down(int l,int r)
{
	int mid = (l+r)>>1;
	int p = id(l,r);
	if(t[p].lazy!=-1)
	{
		int lf = id(l,mid),rt = id(mid+1,r);
		t[lf].lazy=t[rt].lazy=t[p].lazy;
		t[lf].v=t[rt].v=t[p].lazy;
		t[lf].sum=(ll)(mid-l+1)*t[p].lazy,t[rt].sum=(ll)(r-mid)*t[p].lazy;
		t[lf].del=t[rt].del=0;
		t[p].lazy=-1;
	}
	if(t[p].del)
	{
		add_day(l,mid,t[p].del);
		add_day(mid+1,r,t[p].del);
		t[p].del=0;
	}
}
void push_up(int l,int r)
{
	int mid = (l+r)>>1;
	t[id(l,r)].sum= t[id(l,mid)].sum+t[id(mid+1,r)].sum;
	t[id(l,r)].v = t[id(mid+1,r)].v;
}
int L;
int Find(int l,int r,ll x)
{
	if(l==r)return l;
	int mid = (l+r)>>1;
	push_down(l,r);
	if(t[id(l,mid)].v>=x)return Find(l,mid,x);
	else return Find(mid+1,r,x);
}
ll Update(int l, int r,ll b) 
{
    if(r<L) return 0;
    int mid = (l+r)>>1,p = id(l,r); 
	ll ans = 0;
    if(L<=l) 
	{ 
		ans = t[p].sum; 
		t[p].del = 0; 
		t[p].sum = (ll)(r-l+1)*b; 
		t[p].v = b; 
		t[p].lazy = b; 
		return ans; 
	}
	push_down(l,r);
	ans = Update(l,mid,b)+Update(mid+1,r,b);
    push_up(l,r);
    return ans;
}
int main()
{
	int n,m;
	ll last = 0,d,b;
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= n;i++)scanf("%lld",&a[i]);
	sort(a+1,a+n+1);
	for(int i = 1;i<= n;i++)sum[i] = sum[i-1]+a[i];
	for(int i = 1;i<= m;i++)
	{
		scanf("%lld%lld",&d,&b);
		ll dt = d-last;last = d;
		add_day(1,n,dt);
		if(t[id(1,n)].v<b){printf("0\n");continue;}
		L = Find(1,n,b);
		printf("%lld\n",Update(1,n,b)-b*(n-L+1));
	}
	return 0;
}
