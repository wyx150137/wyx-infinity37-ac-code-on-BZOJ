
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 3e5+5;
typedef long long ll;
const ll INF = 1e18;
int root[N],fa[N],d[N],a[N],death[N],ans[N];
ll h[N],v[N];
struct Merge_Heap
{
	#define ls son[p][0]
	#define rs son[p][1]
	int son[N][2],cnt;
	int id[N],level[N],exper[N];ll val[N],add[N],mul[N];
	void Push_down(int p)
	{
		if(mul[p]!=1)
		{
			val[p] = val[p]*mul[p];
			mul[ls]*=mul[p],mul[rs]*=mul[p];
			add[ls]*=mul[p],add[rs]*=mul[p];
			mul[p] = 1;
		}
		if(add[p])
		{
			val[p] = val[p]+add[p];
			add[ls]+=add[p],add[rs]+=add[p];
			add[p] = 0;
		}
		if(exper[p])
		{
			level[p]+=exper[p];
			exper[ls]+=exper[p],exper[rs]+=exper[p];
			exper[p] = 0;
		}
	}
	int merge(int x,int y)
	{
		if(!x||!y)return x+y;
		Push_down(x),Push_down(y);
		if(val[x]>val[y])swap(x,y);
		int tmp = rand()&1;
		son[x][tmp] = merge(son[x][tmp],y);
		return x;
	}
	void init(int p,ll _val,int _id)
	{
		++cnt;
		val[cnt] = _val,id[cnt] = _id;
		mul[cnt] = 1,add[cnt] = 0;
		root[p] = merge(root[p],cnt);
	}
	void Fight(int k)
	{
		for(int p = root[k];p;p=root[k])
		{
			Push_down(p);
			if(val[p]>=h[k])return ;
			ans[id[p]] = level[p];
			death[k]++;
			root[k] = merge(ls,rs);
		}
	}
	void Go(int k)
	{
		Push_down(root[k]);
		if(a[k])mul[root[k]]=v[k];
		else add[root[k]]=v[k];
		exper[root[k]]++;
		root[fa[k]] = merge(root[fa[k]],root[k]);
	}
}mh;
int stack[N],top;
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= n;i++)scanf("%lld",&h[i]);
	for(int i = 2;i<= n;i++)
	{
		scanf("%d%d%lld",&fa[i],&a[i],&v[i]);
		d[fa[i]]++;
	}
	int s;ll c;
	for(int i = 1;i<= m;i++)
	{
		scanf("%lld%d",&c,&s);
		mh.init(s,c,i);
	}
	d[0] = 1,h[0] = INF;
	for(int i = 1;i<= n;i++)if(!d[i])stack[++top]=i;
	while(top)
	{
		int x = stack[top];
		top--;
		mh.Fight(x);
		if(x)
		{
			mh.Go(x);
			d[fa[x]]--;
			if(!d[fa[x]])stack[++top]=fa[x];
		}
	}
	for(int i = 1;i<= n;i++)
		printf("%d\n",death[i]);
	for(int i = 1;i<= m;i++)
		printf("%d\n",ans[i]);
	return 0;
}
