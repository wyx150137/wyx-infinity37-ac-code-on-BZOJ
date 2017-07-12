
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N=100005;
int to[N<<1],ne[N<<1],val[N<<1],v[N<<1];
int fi[N],V[N],num[N],mx[N],fa[N],dep[N],f[N],g[N];
int q[N],d[N],n,L,R,tot=0,cur,rt;
bool u[N];
inline int read() 
{
    int x=0,f=1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
    while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
    return x*f;
}
void add(int x,int y,int z)
{
	to[++tot]=y;val[tot]=z;ne[tot]=fi[x];fi[x]=tot;
}
void findrt(int x)
{
	num[x]=1;mx[x]=0;
	for (int i=fi[x];i;i=ne[i])
	if (!u[to[i]] && to[i]!=fa[x])
	{
		fa[to[i]]=x;
		findrt(to[i]);
		num[x]+=num[to[i]];
		mx[x]=std::max(mx[x],num[to[i]]);
	}
	mx[x]=std::max(mx[x],cur-num[x]);
	if (mx[x]<mx[rt]) rt=x;
}
bool work(int x,int sum)
{
	if (sum<=L) return 0;
	cur=sum;rt=0;
	findrt(x);u[x=rt]=1;
	int maxdep=0;f[0]=0;
	for (int i=fi[x];i;i=ne[i])
	if (!u[to[i]])
	{
		int s=1,t=1,head=1,tail=0;
		for (int j=maxdep;j>=L;j--)
		{
			for (;head<=tail && f[d[tail]]<=f[j];tail--);
			d[++tail]=j;
		}
		fa[q[1]=to[i]]=x;dep[to[i]]=1;g[to[i]]=v[i];
		for (;s<=t;s++)
		{
			for (;head<=tail && d[head]+dep[q[s]]>R;head++);
			if (dep[q[s]]<=L)
			{
				for (;head<=tail && f[d[tail]]<=f[L-dep[q[s]]];tail--);
				d[++tail]=L-dep[q[s]];
			}
			if (head<=tail && f[d[head]]+g[q[s]]>=0) return 1;
			if (dep[q[s]]>=R) continue;
			for (int j=fi[q[s]];j;j=ne[j])
			if (!u[to[j]] && to[j]!=fa[q[s]])
			{
				fa[q[++t]=to[j]]=q[s];
				dep[to[j]]=dep[q[s]]+1;
				g[to[j]]=g[q[s]]+v[j];
			}
		}
		maxdep=std::max(maxdep,dep[q[t]]);
		for (int j=1;j<=t;j++) f[dep[q[j]]]=std::max(f[dep[q[j]]],g[q[j]]);
	}
	for (int i=0;i<=maxdep;i++) f[i]=-n;
	for (int i=fi[x];i;i=ne[i])
	if (!u[to[i]])
	{
		if (num[to[i]]>num[x]) num[to[i]]=sum-num[x];
		if (work(to[i],num[to[i]])) return 1;
	}
	return 0;
}
bool check(int mid)
{
	for (int i=1;i<=tot;i++)
		if (val[i]<mid) v[i]=-1;else v[i]=1;
	for (int i=0;i<=n;i++) u[i]=false,fa[i]=0,f[i]=-n;
	mx[0]=n;
	return work(1,n);
}
int main()
{
	n = read();
	L = read();
	R = read();
	for (int i=1;i<n;i++)
	{
		int x,y,z;
		x = read();y = read();z = read();
		add(x,y,z);add(y,x,z);V[i]=z;
	}
	std::sort(V+1,V+n);
	int m=std::unique(V+1,V+n)-V-1;
	V[0]=-1;
	int l=1,r=m,ans=0,mid;
	for (;l<=r;)
	{
		mid=(l+r)>>1;
		if (check(V[mid])) ans=mid,l=mid+1;
			else r=mid-1;
	}
	printf("%d\n",V[ans]);
}
