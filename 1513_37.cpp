
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 3e3+5;
int S,D,lx,rx,sy,xy;
struct X_seg
{
	int val[N],lazy[N];
	void update(int p,int l,int r,int a,int b,int k)
	{
		val[p] = max(val[p],k);
		if(l>=a&&r<=b){lazy[p] = max(lazy[p],k);return ;}
		int mid = (l+r)>>1;
		if(a<=mid)update(p<<1,l,mid,a,b,k);
		if(b >mid)update(p<<1|1,mid+1,r,a,b,k);
	}
	int getans(int p,int l,int r,int a,int b)
	{
		if(l>=a&&r<=b)return val[p];
		int mid = (l+r)>>1;
		int ans = lazy[p];
		if(a<=mid)ans = max(ans,getans(p<<1,l,mid,a,b));
		if(b >mid)ans = max(ans,getans(p<<1|1,mid+1,r,a,b));
		return ans;
	}
};
struct Y_seg
{
	X_seg val[N],lazy[N];
	void update(int p,int l,int r,int a,int b,int y)
	{
		val[p].update(1,1,S,xy,sy,y);
		if(l>=a&&r<=b){lazy[p].update(1,1,S,xy,sy,y);return ;}
		int mid = (l+r)>>1;
		if(a<=mid)update(p<<1,l,mid,a,b,y);
		if(b >mid)update(p<<1|1,mid+1,r,a,b,y);
	}
	int getans(int p,int l,int r,int a,int b)
	{
		if(l>=a&&r<=b)return val[p].getans(1,1,S,xy,sy);
		int mid = (l+r)>>1;
		int ans = lazy[p].getans(1,1,S,xy,sy);
		if(a<=mid)ans = max(ans,getans(p<<1,l,mid,a,b));
		if(b >mid)ans = max(ans,getans(p<<1|1,mid+1,r,a,b));
		return ans;
	}
}M;
int main()
{
	int n,d,s,x,y,t;
	scanf("%d%d%d",&D,&S,&n);
	for(int i =1;i<= n;i++)
	{
		scanf("%d%d%d%d%d",&d,&s,&t,&x,&y);
		lx = x+1,rx = x+d,xy = y+1,sy = y+s;
		int ans = M.getans(1,1,D,lx,rx);
		M.update(1,1,D,lx,rx,ans+t);
	}
	xy = 1,sy = S;
	printf("%d\n",M.getans(1,1,D,1,D));
	return 0;
}
