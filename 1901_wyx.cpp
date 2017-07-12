
#include <cstdio>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int maxn=10005;
int d[maxn];
int n,m;
int a[maxn];
int lowbit(int x){
	return x&-x;
}
int get(int x)
{
	int ans=0;
	while(x)
		ans+=d[x],x-=lowbit(x);
	return ans;
}
void updata(int x,int y)
{
	while(x<=n)
		d[x]+=y,x+=lowbit(x);
}
struct qes
{
	int x,y,z,ty,ind,cur,delta;
}q[maxn*3];

int cnt=0,anss[maxn],tmp[maxn],md,mx;
bool part(qes &Q)
{
	if(Q.ty==3)
	{
		if(Q.cur+Q.delta>Q.z-1)
			return true;
		Q.cur+=Q.delta;Q.delta=0;
			return false;
	}
	return Q.y<=md;
}
void solve(int lef,int rig,int l,int r){
	if(lef>rig)return;
	if(l==r)
	{
		for(int i=lef;i<=rig;i++)if(q[i].ty==3)
			anss[q[i].ind]=l;
		return;
	}
	int mid=(l+r)>>1;md=mid;
	for(int i=lef;i<=rig;i++)
	{
		if(q[i].ty==1&&q[i].y<=mid)
			updata(q[i].x,1);
		if(q[i].ty==2&&q[i].y<=mid)
			updata(q[i].x,-1);
		if(q[i].ty==3)
			q[i].delta=get(q[i].y)-get(q[i].x-1);
	}
	for(int i=lef;i<=rig;i++)
	{
		if(q[i].ty==1&&q[i].y<=mid)updata(q[i].x,-1);
		if(q[i].ty==2&&q[i].y<=mid)updata(q[i].x,1);
	}
	int dv=stable_partition(q+lef,q+rig+1,part)-q-1;
	solve(lef,dv,l,mid);
	solve(dv+1,rig,mid+1,r);
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);mx=max(mx,a[i]);
		q[++cnt]=(qes){i,a[i],0,1,0,0,0};
	}
	for(int i=1;i<=m;i++)
	{
		char op=getchar();while(op!='Q'&&op!='C')op=getchar();
		if(op=='Q')
		{
			int l,r,k;
			scanf("%d%d%d",&l,&r,&k);
			q[++cnt]=(qes){l,r,k,3,++anss[0],0,0};
		}
		else
		{
			int x,y;
			scanf("%d%d",&x,&y);
			q[++cnt]=(qes){x,a[x],0,2,0,0,0};
			q[++cnt]=(qes){x,y,0,1,0,0,0};
			a[x]=y;mx=max(mx,a[x]);
		}
	}	
	solve(1,cnt,0,mx);
	for(int i=1;i<=anss[0];i++)
		printf("%d\n",anss[i]);
	return 0;
}
