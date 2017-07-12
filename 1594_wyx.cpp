
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
#define N 1100000
int fa[N],n,q;
inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}
struct query
{
	int l,r,ans;
	bool operator<(const query&z)const
	{
		return ans > z.ans;
	}
}tmp[N],ask[N];
int find(int x)
{
	return fa[x]^x?fa[x]=find(fa[x]):fa[x];
}
bool check(int mid)
{
	for(int i=1;i<=mid;++i)tmp[i]=ask[i];
	sort(tmp+1,tmp+mid+1);
	for(int i=1;i<=n;++i) fa[i]=i;
	for(int i=1,j=1;i<=mid;i=j+1,j++)
	{
		int La,Lb,Ra,Rb;
		La = Lb = tmp[i].l;
		Ra = Rb = tmp[i].r;
		while( j < mid && tmp[j+1].ans == tmp[j].ans )
		{
			j++;
			La = min(tmp[j].l,La);
			Lb = max(tmp[j].l,Lb);
			Ra = max(tmp[j].r,Ra);
			Rb = min(tmp[j].r,Rb);
		}
		if(find(Rb)+1<=Lb)
			return true;
		for(int t=Ra,p=find(t);p>=La;t=p-1,p=find(t)) 
            fa[p]=La-1;
	}
	return false;
}
int main()
{
	cin>>n>>q;
	for(int i=1;i<=q;++i)
		ask[i].l=read(),ask[i].r=read(),ask[i].ans=read();
	int l=1,r=q;
	int ans = 0;
	while(l<r)
	{
		int mid = (l+r)>>1;
		if(check(mid))
			r=mid,ans = mid;
		else l=mid+1;
	}
	cout<<ans<<endl;
}
