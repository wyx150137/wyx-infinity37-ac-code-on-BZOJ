
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 3e5+5;
int fa[N],size[N],deg[N],size2[N],num0,num2,numc;
int getfa(int x)
{
	if(fa[x]==x||!fa[x])return fa[x]=x;
	else return fa[x] = getfa(fa[x]);
}
void del(int x)
{
	if(deg[x]==0)num0--;
	if(deg[x]==2)num2--,size2[getfa(x)]--;
}
void add(int x)
{
	if(deg[x]==0)num0++;
	if(deg[x]==2)num2++,size2[getfa(x)]++;
}
void delc(int x){if(size[x]==size2[x])numc--;}
void addc(int x){if(size[x]==size2[x])numc++;}
void merge(int u,int v)
{
	int x = getfa(u),y = getfa(v);
	if(x^y)
	{
		delc(x),delc(y),del(u),del(v);
		deg[u]++,deg[v]++;
		add(u),add(v);
		fa[x] = y,size[y]+=size[x],size2[y]+=size2[x];
		addc(y);
	}else
	{
		delc(x),del(u),del(v);
		deg[u]++,deg[v]++;
		add(u),add(v),addc(x);
	}
}
int a[N],idx[N],ans1[N],ans2[N];
bool cmp(int x,int y)
{
	return a[x]>a[y];
}
struct E
{
	int x,y,w;
	bool operator <(const E &s)const
	{
		return w>s.w;
	}
}e[N];
int main()
{
	int n,m,q;
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= m;i++)
		scanf("%d%d%d",&e[i].x,&e[i].y,&e[i].w);
	sort(e+1,e+m+1);
	scanf("%d",&q);
	for(int i = 1;i<= q;i++)scanf("%d",&a[i]),idx[i]=i;
	sort(idx+1,idx+q+1,cmp);
	for(int i = 1;i<= n;i++)
		deg[i]=0,fa[i]=i,size[i]=1,size2[i]=0;
	num0 = n;
	int pnt = 1;
	int curm = 0;
	for(int i = 1;i<= q;i++)
	{
		while(pnt<=m&&e[pnt].w>=a[idx[i]])
			merge(e[pnt].x,e[pnt].y),pnt++,curm++;
		ans1[idx[i]] = n-num0-num2+numc;
		ans2[idx[i]] = curm-num2+numc;
	}
	for(int i = 1;i<= q;i++)
		printf("%d %d\n",ans1[i],ans2[i]);
	return 0;
}
