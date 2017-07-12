
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 5e4+5;
const int M = 1e5+5;
const int Q = 5e4+5;
struct E
{
	int x,y,a,b,id;
	void read(int no)
	{
		scanf("%d%d%d%d",&x,&y,&a,&b);
		id = no;
	}
	bool operator <(const E &s)const
	{
		if(a==s.a)return b<s.b;
		return a<s.a;
	}
}e[M],ask[Q],tmp[Q];
struct Opt
{
	int x,y,fa,mxa,mxb,sz;
}opt[Q];
bool cmp(const E &x,const E &y)
{
	if(x.b==y.b)return x.a<y.a;
	return x.b<y.b;
}
int tot,top;
int fa[N],size[N],mxa[Q],mxb[Q],ans[N];
int getfa(int x)
{
	if(fa[x]==x)return x;
	else return getfa(fa[x]);
}
void merge(int x,int y,int a,int b)
{
	x = getfa(x),y = getfa(y);
	if(size[x]>size[y])swap(x,y);
	opt[++tot].x = x,opt[tot].mxa = mxa[y],opt[tot].mxb = mxb[y];
	opt[tot].y = y,opt[tot].fa = fa[x],opt[tot].sz = size[y];
	if(x==y)
	{
		mxa[x] = max(mxa[x],a);
		mxb[x] = max(mxb[x],b);
		return ;
	}
	fa[x] = y,size[y]+=size[x];
	mxa[y] = max(mxa[y],max(mxa[x],a));
	mxb[y] = max(mxb[y],max(mxb[x],b));
}
void go_back()
{
	while(tot)
	{
		fa[opt[tot].x] = opt[tot].fa;
		mxa[opt[tot].y] = opt[tot].mxa;
		mxb[opt[tot].y] = opt[tot].mxb;
		size[opt[tot].y] = opt[tot].sz;
		tot--;
	}
}
int main()
{
	int n,m,q;
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= m;i++)
		e[i].read(i);
	scanf("%d",&q);
	for(int i = 1;i<= q;i++)
		ask[i].read(i);
	sort(e+1,e+m+1);
	sort(ask+1,ask+q+1,cmp);
	int block = sqrt(m);
	for(int i = 1;i<= m;i+=block)
	{
		top = 0;
		for(int j = 1;j<= q;j++)
			if(ask[j].a>=e[i].a&&(i+block>m||ask[j].a<e[i+block].a))
				tmp[++top] = ask[j];
		sort(e+1,e+i,cmp);
		for(int j = 1;j<= n;j++)fa[j]=j,size[j]=1,mxa[j]=mxb[j]=-1;
		for(int j = 1,k = 1;j<= top;j++)
		{
			for(;k<i&&e[k].b<=tmp[j].b;k++)
				merge(e[k].x,e[k].y,e[k].a,e[k].b);
			tot = 0;
			for(int l = i;l<i+block&&l<=m;l++)
				if(e[l].a<=tmp[j].a&&e[l].b<=tmp[j].b)
					merge(e[l].x,e[l].y,e[l].a,e[l].b);
			int x = getfa(tmp[j].x),y = getfa(tmp[j].y);
			ans[tmp[j].id] = x==y&&mxa[x]==tmp[j].a&&mxb[x]==tmp[j].b;
			go_back();
		}
	}
	for(int i = 1;i<= q;i++)
		if(ans[i])printf("Yes\n");
		else printf("No\n");
	return 0;
}
