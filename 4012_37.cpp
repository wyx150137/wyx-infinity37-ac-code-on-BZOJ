
#include <stdio.h>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 150005;
typedef long long ll;
typedef vector<pair<int,ll> >P;
const ll INF = 1e18;
struct E
{int next,to,val;}e[N<<1];
int head[N],tot;
bool ban[N<<1];
void init()
{
	memset(head,0,sizeof(head));
	memset(ban,0,sizeof(ban));
	tot = 1;
}
void add(int x,int y,int f)
{
	e[++tot].to = y;e[tot].next = head[x];e[tot].val = f;head[x] = tot;
	e[++tot].to = x;e[tot].next = head[y];e[tot].val = f;head[y] = tot;
}
bool used[N];
int size[N],f[N],sum,root;
void get_root(int x,int from)
{
	size[x] = 1;f[x] = 0;
	for(int i = head[x];i;i = e[i].next)
		if(!used[e[i].to]&&e[i].to!=from)
		{
			get_root(e[i].to,x);
			size[x]+=size[e[i].to];
			f[x] = max(f[x],size[e[i].to]);
		}
	f[x] = max(f[x],sum-size[x]);
	if(f[x]<f[root])root = x;
}
int a[N],fa[N],dis[N];
P sum1[N];
P sum2[N];
void get_dis(int x,int from,P &s1,P &s2,ll dis)
{
	s1.push_back(pair<int,ll>(a[x],dis));
	s2.push_back(pair<int,ll>(a[x],dis));
	for(int i = head[x];i;i = e[i].next)
		if(!used[e[i].to]&&e[i].to!=from)
			get_dis(e[i].to,x,s1,s2,dis+e[i].val);
}
int work(int x)
{
	used[x] = true;
	sum1[x].push_back(pair<int,ll>(a[x],0));
	for(int i = head[x];i;i = e[i].next)
		if(!used[e[i].to])
		{
			sum=size[e[i].to];
			root = 0;
			P tmp;
			get_dis(e[i].to,x,sum1[x],tmp,e[i].val);
			get_root(e[i].to,0);
			fa[root] = x;sum2[root] = tmp;
			sum2[root].push_back(pair<int,ll>(-1,0));
			sort(sum2[root].begin(),sum2[root].end());
			for(int j = 1;j<sum2[root].size();j++)
				sum2[root][j].second+=sum2[root][j-1].second;
			work(root);
		}
	sum1[x].push_back(pair<int,ll>(-1,0));
    sort(sum1[x].begin(),sum1[x].end());
    for(int j=1;j<sum1[x].size();j++)
        sum1[x][j].second+=sum1[x][j-1].second;
}
int pos[N],T,log_2[N<<1];
ll min_dpt[N<<1][20],dpt[N];
void DFS(int x,int from)
{
	min_dpt[pos[x]=++T][0] = dpt[x];
	for(int i = head[x];i;i = e[i].next)
		if(e[i].to!=from)
		{
			dpt[e[i].to] = dpt[x]+e[i].val;
			DFS(e[i].to,x);
			min_dpt[++T][0] = dpt[x];
		}
}
void build_lca()
{
	for(int i = 2;i<=T;i++)
		log_2[i] = log_2[i>>1]+1;
	for(int j = 1;j<= log_2[T];j++)
		for(int i = 1;i+(1<<j)-1<=T;i++)
			min_dpt[i][j] = min(min_dpt[i][j-1],min_dpt[i+(1<<(j-1))][j-1]);
}
ll get_lcadpt(int x,int y)
{
	x = pos[x],y = pos[y];
	if(x>y)swap(x,y);
	int l = log_2[y-x+1];
	return min(min_dpt[x][l],min_dpt[y-(1<<l)+1][l]);
}
ll get_distance(int x,int y)
{
	return dpt[x]+dpt[y]-2*get_lcadpt(x,y);
}
ll sumv1,sumv2;int cnt1,cnt2;
int qurey1(const P &s,int x)
{
	int l = 0,r = s.size();
	while(l<r)
	{
		int mid = (l+r)>>1;
		if(s[mid].first<=x)l = mid+1;
		else r = mid;
	}
	l--;
	if(l<0)l = 0;
	return l;
}
int qurey2(const P &s,int x)
{
	int l = 0,r = s.size();
	while(l<r)
	{
		int mid = (l+r)>>1;
		if(s[mid].first<x)l = mid+1;
		else r = mid;
	}
	l--;
	if(l<0)l = 0;
	return l;
}
ll ans;
void qurey(int x,int i,int l,int r)
{
	int r1 = qurey1(sum1[fa[i]],r),l1 = qurey2(sum1[fa[i]],l);
	int r2 = qurey1(sum2[i],r),l2 = qurey2(sum2[i],l);
	ans+=sum1[fa[i]][r1].second-sum1[fa[i]][l1].second-sum2[i][r2].second+sum2[i][l2].second;
	ans+=(ll)(r1-l1-r2+l2)*get_distance(x,fa[i]);
}
void qurey(int x,int l,int r)
{
	ans = 0;
	int L = qurey2(sum1[x],l),R = qurey1(sum1[x],r);
	ans+=sum1[x][R].second-sum1[x][L].second;
	for(int i = x;fa[i];i = fa[i])
		qurey(x,i,l,r);
}
void debug1(int x)
{
	printf("%d\n",sum1[x].size());
	for(int i = 0;i<sum1[x].size();i++)
		printf("%d:%I64d ",sum1[x][i].first,sum1[x][i].second);
	printf("\n");
}
void debug2(int x)
{
	printf("%d\n",sum2[x].size());
	for(int i = 0;i<sum2[x].size();i++)
		printf("%d:%I64d ",sum2[x][i].first,sum2[x][i].second);
	printf("\n");
}
int main()
{
	int n,q,A;
	scanf("%d%d%d",&n,&q,&A);
	for(int i = 1;i<= n;i++)
		scanf("%d",&a[i]);
	int x,y,z;
	for(int i = 1;i<n;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		add(x,y,z);
	}
	DFS(1,0);
	build_lca();
	f[0] = sum = n;
	root = 0;
	get_root(1,0);
	work(root);
	ll last_ans = 0;
	for(int i = 1;i<= q;i++)
	{
		scanf("%d%d%d",&z,&x,&y);
		x = (x+last_ans)%A;
		y = (y+last_ans)%A;
		if(x>y)swap(x,y);
		qurey(z,x,y);
		printf("%lld\n",last_ans = ans);
	}
	return 0;
}
