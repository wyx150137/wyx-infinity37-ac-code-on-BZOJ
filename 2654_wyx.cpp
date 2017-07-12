
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#define N 50000+5
#define M 200000+5
using namespace std;
int fa[N],rank[N],m,n,ans,need;
int find(int x)
{
	return (fa[x]^x)?fa[x]=find(fa[x]):fa[x];
}
void Union(int x,int y)
{
	int fx=find(x),fy=find(y);
	if(fx==fy)return ;
	if(rank[fx]<rank[fy])swap(fx,fy);
	rank[fx]+=rank[fy];fa[fy]=fx;
}
struct graph
{
	int from,to,val,deval,F;
	bool operator <(const graph &z)const
	{
		if(val+deval!=z.val+z.deval)return val+deval<z.val+z.deval;
		else return F>z.F;
	}
}edge[M];
inline int read()
{
	int x = 0, f = 1; char ch = getchar();
	while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar(); }
	while (ch >= '0' && ch <= '9') { x = x * 10 + ch - '0'; ch = getchar(); }
	return x * f;
}	
int Kruskal(int k)
{
	for(int i=0;i<n;++i)
		fa[i]=i,rank[i]=1;
	for(int i=1;i<=m;++i)
		if(edge[i].F)
			edge[i].deval=-k;
	sort(edge+1,edge+m+1);
		int cnt=0,decnt=0;
		ans=0;
		for(int i=1;i<=m;++i)
		{
			int fx=find(edge[i].from),fy=find(edge[i].to);
		if(fx==fy)continue;
		Union(fx,fy);if(edge[i].F)decnt++;
		cnt++;
		ans+=edge[i].val;
		//cout<<"true at LINE 53  now k=="<<k<<endl;
		if(cnt==n-1)break;
	}
	return decnt;
}
int main()
{	
	cin>>n>>m>>need;
	for(int i=1;i<=m;++i)
	{
		edge[i].from=read(),edge[i].to=read(),edge[i].val=read();
		int tmp1=read();if(tmp1)edge[i].F=false,edge[i].deval=0;
		else edge[i].F=true,edge[i].deval=0;
	}
	int l=-100,r=101;
	while(l<r)
	{
		int mid=(l+r)>>1;
		int tmp=Kruskal(mid);
		//printf("%d tmp=%d\n",__LINE__,tmp );
		if(tmp>=need)r=mid;
		else l=mid+1;
		//cout<<"l="<<l<<" && r="<<r<<" &&  mid="<<mid<<"  &&  tmp="<<tmp<<endl;
		//printf(" ans==%d \n",ans );
	}
	ans=0;
	//cout<<l<<endl;
	for(int i=1;i<=m;++i){edge[i].deval=0;if(edge[i].F)edge[i].val-=l;}
	for(int i=0;i<n;++i)fa[i]=i,rank[i]=1;
	sort(edge+1,edge+m+1);
	int cnt=0;
	for(int i=1;i<=m;++i)
	{
		int fx=find(edge[i].from),fy=find(edge[i].to);
		if(fx==fy)continue;
		//printf("%d %d %d\n",edge[i].from,edge[i].to,edge[i].val);
		Union(fx,fy);
		ans+=edge[i].val;
		cnt++;
		if(cnt==n-1)break;
	}
	/*for(int i=0;i<=n;++i)
		if(fa[i]==i)
			cout<<i<<endl;*/
	cout<<ans+need*l;
}
