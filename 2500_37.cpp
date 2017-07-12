
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1e6+5;
typedef long long LL;
LL f[N],t[N],hap[N];
int Q1[N],Q2[N],f_no[N],l1,l2,r1,r2;
inline int read()
{
	int x = 0, f = 1; char ch = getchar();
	while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar(); }
	while (ch >= '0' && ch <= '9') { x = x * 10 + ch - '0'; ch = getchar(); }
	return x * f;
}
struct E
{
	int next,to,val;
}e[N];
int head[N],tot;
void add(int x,int y,int f)
{
	e[++tot].to = y;
	e[tot].next = head[x];
	e[tot].val  = f;
	head[x] = tot;
}
void dfs(int x)
{
	for(int i = head[x];i;i = e[i].next)
	{
		dfs(e[i].to);
		if(f[e[i].to]+e[i].val>f[x])
		{
			t[x] = f[x];
			f[x] = f[e[i].to]+e[i].val;
			f_no[x] = e[i].to;
		}else if(f[e[i].to]+e[i].val>t[x])
			t[x] = f[e[i].to]+e[i].val;
	}
}
void redfs(int x,LL v)
{
	hap[x] = max(f[x],v);
	for(int i = head[x];i;i = e[i].next)
	{
		LL tmp = f_no[x]==e[i].to?t[x]:f[x];
		redfs(e[i].to,max(v,tmp)+e[i].val);
	}
}
int main()
{
	int n,m,x,y,ans = 0;
	scanf("%d%d",&n,&m);
	for(int i = 2;i<= n;i++)
	{
		x = read();y = read();
		//if(x==i)root = i;
		add(x,i,y);
	}
	dfs(1);
	redfs(1,0);
	int j = 1;
	r1 = r2 = -1;
	for(int i = 1;i<= n;i++)
	{
		while(l1<=r1&&hap[i]>hap[Q1[r1]])r1--;
		Q1[++r1] = i;
		while(l2<=r2&&hap[i]<hap[Q2[r2]])r2--;
		Q2[++r2] = i;
		while(hap[Q1[l1]]-hap[Q2[l2]]>m)
		{
			j++;
			while(l1<=r1&&Q1[l1]<j)l1++;
			while(l2<=r2&&Q2[l2]<j)l2++;
		}
		ans = max(ans,i-j+1);
	}
	printf("%d\n",ans);
	return 0;
}
