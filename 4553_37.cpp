
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int MX = 1e5;
const int N = 1e5+5;
const int M = 1e7+5;
int rot[N],ls[M],rs[M],mx[M],tot,f[N],a[N];
void update(int &p,int l,int r,int pos,int val)
{
	if(!p)p = ++tot;
	mx[p] = max(mx[p],val);
	if(l==r)return ;
	int mid = (l+r)>>1;
	if(pos<=mid)update(ls[p],l,mid,pos,val);
	else update(rs[p],mid+1,r,pos,val);
}
int getans(int p,int l,int r,int a,int b)
{
	if(!p)return 0;
	if(l>=a&&r<=b)return mx[p];
	int mid = (l+r)>>1;
	if(b<=mid)return getans(ls[p],l,mid,a,b);
	else if(a>mid)return getans(rs[p],mid+1,r,a,b);
	else return max(getans(ls[p],l,mid,a,b),getans(rs[p],mid+1,r,a,b));
}
void Update(int x,int y)
{
	for(int i = x;i<=MX;i+=i&(-i))
		update(rot[i],1,MX,a[y],f[y]);
}
int Getans(int x,int y)
{
	int ans = 0;
	for(int i = x;i;i-=i&(-i))
		ans = max(ans,getans(rot[i],1,MX,1,y));
	return ans;
}
int Mx[N],Mn[N];
int main()
{
	int n,m,x,y;
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= n;i++)scanf("%d",&a[i]),Mx[i]=Mn[i]=a[i];
	for(int i = 1;i<= m;i++)
	{
		scanf("%d%d",&x,&y);
		Mx[x] = max(Mx[x],y);Mn[x] = min(Mn[x],y); 
	}
	//for(int i = 1;i<= n;i++)f[i] = 1;
	for(int i = 1;i<= n;i++)
	{
		f[i] = Getans(a[i],Mn[i])+1;
		Update(Mx[i],i);
	}
	int ans = 0;
	for(int i = 1;i<= n;i++)ans = max(ans,f[i]);
	printf("%d\n",ans);
	return 0;
}
