
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 5e5+5;
const int M = (N<<1)+5e4;
const int INF = 1e9+10;
ll ans;
int A[N],B[N],aa[M],ab[M],ba[M],bb[M],lazy[M],vm[M],n,k;
struct data
{
	int x,y;
	data(){}
	data(int _x,int _y):x(_x),y(_y){}
	data operator +(const data &b){return A[x]+B[y]<A[b.x]+B[b.y]?*this:b;}
}va[M],vb[M],vc[M],t;
inline void add(int x,int p)
{
	vm[x]+=p;
	lazy[x]+=p;
}
inline void Push_down(int p)
{
	if(!lazy[p])return ;
	add(p<<1,lazy[p]),add(p<<1|1,lazy[p]);
	lazy[p]=0;
}
inline void Push_up(int p)
{
	int ls = p<<1,rs = p<<1|1;
	va[p] = va[ls]+va[rs]+data(aa[ls],ab[rs]);
	vc[p] = vc[ls]+vc[rs]+data(aa[rs],ab[ls]);
	vb[p] = vb[ls]+vb[rs];
	aa[p] = A[aa[ls]]<A[aa[rs]]?aa[ls]:aa[rs];
	ab[p] = B[ab[ls]]<B[ab[rs]]?ab[ls]:ab[rs];
	if(vm[ls]<vm[rs])
	{
		vb[p] = vb[p]+vc[rs]+data(aa[rs],bb[ls]);
		ba[p] = ba[ls];
		bb[p] = B[ab[rs]]<B[bb[ls]]?ab[rs]:bb[ls];
		vm[p] = vm[ls];
	}
	else if(vm[ls]>vm[rs])
	{
		vb[p] = vb[p]+vc[ls]+data(ba[rs],ab[ls]);
		ba[p] = A[aa[ls]]<A[ba[rs]]?aa[ls]:ba[rs];
		bb[p] = bb[rs];
		vm[p] = vm[rs];
	}else
	{
		vb[p] = vb[p]+data(ba[rs],bb[ls]);
		ba[p] = ba[ls];
		bb[p] = bb[rs];
		vm[p] = vm[ls];
	}
}
void build(int p,int l,int r)
{
	if(l==r)
	{
		va[p]=vc[p]=data(l,l),vb[p]=data(0,0);
		aa[p]=ba[p]=ab[p]=l;
		return ;
	}
	int mid = (l+r)>>1;
	build(p<<1,l,mid),build(p<<1|1,mid+1,r);
	Push_up(p);
}
void Add(int p,int l,int r,int a,int b,int val)
{
	if(l>=a&&r<=b)
	{
		add(p,val);
		return ;
	}
	Push_down(p);
	int mid = (l+r)>>1;
	if(a<=mid)Add(p<<1,l,mid,a,b,val);
	if(b >mid)Add(p<<1|1,mid+1,r,a,b,val);
	Push_up(p);
}
void Change(int p,int l,int r,int pos)
{
	if(l==r)return ;
	Push_down(p);int mid = (l+r)>>1;
	if(pos<=mid)Change(p<<1,l,mid,pos);
	else Change(p<<1|1,mid+1,r,pos);
	Push_up(p);
}
int main()
{
	scanf("%d%d",&n,&k);
	for(int i = 1;i<= n;i++)scanf("%d",&A[i]);
	for(int i = 1;i<= n;i++)scanf("%d",&B[i]);
	A[0]=B[0]=INF;
	build(1,0,n);
	while(k--)
	{
		t = va[1]+vb[1];
		int i = t.x,j = t.y;
		ans += A[i]+B[j];
		if(i<j)Add(1,0,n,i,j-1,1);
		if(j<i)Add(1,0,n,j,i-1,-1);
		A[i] = INF,Change(1,0,n,i);
		B[j] = INF,Change(1,0,n,j);
	}
	printf("%lld\n",ans);
	return 0;
}
