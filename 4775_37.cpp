
#include <stdio.h>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
#define fir first
#define sec second
using namespace std;

const int N = 1e5+5;
struct E
{int next,to;}e[N<<1];
int head[N],tot,dep[N],fa[N][18];
void add(int x,int y)
{
	e[++tot].to = y;e[tot].next = head[x];head[x] = tot;
	e[++tot].to = x;e[tot].next = head[y];head[y] = tot;
}
void dfs(int x)
{
	dep[x] = dep[fa[x][0]]+1;
	for(int i = 1;i<= 17;i++)fa[x][i]=fa[fa[x][i-1]][i-1];
	for(int i = head[x];i;i=e[i].next)
		if(e[i].to!=fa[x][0])
		{
			fa[e[i].to][0] = x;
			dfs(e[i].to);
		}
}
int getlca(int x,int y)
{
	if(dep[x]<dep[y])swap(x,y);
	for(int i = 17;i>= 0;i--)
		if(dep[fa[x][i]]>=dep[y])x = fa[x][i];
	if(x==y)return x;
	for(int i = 17;i>=0;i--)
		if(fa[x][i]!=fa[y][i])
			x = fa[x][i],y = fa[y][i];
	return fa[x][0];
}
int getdis(int x,int y)
{
	return dep[x]+dep[y]-2*dep[getlca(x,y)];
}
bool used[N];
int size[N],f[N],sum,root;
void get_root(int x,int pre)
{
	size[x] = 1;
	f[x] = 0;
	for(int i = head[x];i;i=e[i].next)
		if(!used[e[i].to]&&e[i].to!=pre)
		{
			get_root(e[i].to,x);
			size[x]+=size[e[i].to];
			f[x] = max(f[x],size[e[i].to]);
		}
	f[x] = max(f[x],sum-size[x]);
	if(f[x]<f[root])root = x;
}	
void get_size(int x,int pre)
{
	size[x] = 1;
	for(int i = head[x];i;i=e[i].next)
		if(e[i].to!=pre&&!used[e[i].to])
		{
			get_size(e[i].to,x);
			size[x]+=size[e[i].to];
		}
}
vector<int>E[N];
int father[N];
pair<double,double>A[N];
double w[N],d[N],pw[N],pd[N],A1[N],pA1[N],A2[N],pA2[N],A3[N],pA3[N];
void build(int x,int pre)
{
	get_size(x,0);
	sum = size[x];
	f[root = 0]=sum;
	get_root(x,0);
	x = root;
	father[x] = pre;
	used[x] = true;
	E[pre].push_back(x);
	for(int i = head[x];i;i=e[i].next)
		if(!used[e[i].to])
			build(e[i].to,x);
}
inline void Add(int x)
{
	double y = A[x].fir*(1-A[x].fir);
	w[x]+=A[x].fir,A3[x]+=y;
	for(int i = x;father[i];i=father[i])
	{
		double D = getdis(x,father[i]);
		d[father[i]]+=D*A[x].fir;pd[i]+=D*A[x].fir;
		w[father[i]]+=A[x].fir;pw[i]+=A[x].fir;

		A1[father[i]]+=D*D*y;pA1[i]+=D*D*y;
		A2[father[i]]+=D*2*y;pA2[i]+=D*2*y;
		A3[father[i]]+=y;pA3[i]+=y;
	}
}
inline void Del(int x)
{
	double y = A[x].fir*(1-A[x].fir);
	w[x]-=A[x].fir,A3[x]-=y;
	for(int i = x;father[i];i=father[i])
	{
		double D = getdis(x,father[i]);
		d[father[i]]-=D*A[x].fir;pd[i]-=D*A[x].fir;
		w[father[i]]-=A[x].fir;pw[i]-=A[x].fir;

		A1[father[i]]-=D*D*y;pA1[i]-=D*D*y;
		A2[father[i]]-=D*2*y;pA2[i]-=D*2*y;
		A3[father[i]]-=y;pA3[i]-=y;
	}
}
inline void update(int x,double p)
{
	double k0 = p/100.0,k1 = (100.0-p)/100.0;
	Del(x);
	A[x] = make_pair(A[x].fir*k1+A[x].sec*k0,A[x].fir*k0+A[x].sec*k1);
	Add(x);
}
inline void getans(int x)
{
	double ans1 = d[x],ans2 = A1[x];
	for(int i = x;father[i];i=father[i])
	{
		double D = getdis(x,father[i]);
		ans1 += d[father[i]]-pd[i]+D*w[father[i]]-D*pw[i];
		ans2 += A1[father[i]]-pA1[i]+D*A2[father[i]]-D*pA2[i]+D*D*A3[father[i]]-D*D*pA3[i];
	}
	printf("%.13f\n",ans1*ans1+ans2);
}
int main()
{
	//freopen("x.in","r",stdin);
	//freopen("x.out","w",stdout);
	int n,m,x,y,id;
	double p;
	scanf("%d%d%d",&id,&n,&m);
	for(int i = 1;i<= n;i++)scanf("%d",&x),A[i]=make_pair(x,x^1);
	for(int i = 1;i< n;i++)
	{
		scanf("%d%d",&x,&y);
		add(x,y);
	}
	dfs(1);
	build(1,0);
	for(int i = 1;i<= n;i++)Add(i);
	int opt;
	for(int i = 1;i<= m;i++)
	{
		scanf("%d",&opt);
		if(opt==1)
		{
			scanf("%d%lf",&x,&p);
			update(x,p);
		}else
		{
			scanf("%d",&x);
			getans(x);
		}
	}
	return 0;
}
