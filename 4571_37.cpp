
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 2e5+5;
int root[N],size[N*100],ls[N*100],rs[N*100],cnt,a[N];
void Update(int &p,int pre,int l,int r,int pos)
{
	p = ++cnt;
	size[p] = size[pre]+1;
	ls[p] = ls[pre],rs[p] = rs[pre];
	if(l==r)return ;
	int mid = (l+r)>>1;
	if(pos<=mid)Update(ls[p],ls[pre],l,mid,pos);
	else Update(rs[p],rs[pre],mid+1,r,pos);
}
int Getans(int L,int R,int l,int r,int a,int b)
{
	if(l>=a&&r<=b)
		return size[R]-size[L];
	int mid = (l+r)>>1,ans = 0;
	if(a<=mid)ans+=Getans(ls[L],ls[R],l,mid,a,b);
	if(b >mid)ans+=Getans(rs[L],rs[R],mid+1,r,a,b);
	return ans;
}
int L,R,D;
int mx = (1<<19)-1;
int getans(int l,int r,int x,int y)
{
	if(l==r)
		return x^l;
	int mid = (l+r)>>1;
	D--;
	if(x&(1<<D))
	{
		if(Getans(L,R,0,mx,max(0,l-y),max(0,mid-y)))
			return getans(l,mid,x,y);
		else 
			return getans(mid+1,r,x,y);
	}
	else
	{
		if(Getans(L,R,0,mx,max(0,mid+1-y),max(0,r-y)))
			return getans(mid+1,r,x,y);
		else 
			return getans(l,mid,x,y);
	}
}
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= n;i++)scanf("%d",&a[i]);
	for(int i = 1;i<= n;i++)
		Update(root[i],root[i-1],0,mx,a[i]);
	int x,y,l,r;
	for(int i = 1;i<= m;i++)
	{
		scanf("%d%d%d%d",&x,&y,&l,&r);
		D = 19;
		L = root[l-1],R = root[r];
		printf("%d\n",getans(0,mx,x,y));
	}
	return 0;
}
