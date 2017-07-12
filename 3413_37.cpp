
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 2e5+5;
char s[N],b[N];
int ch[N][10],len[N],fa[N],n,m,fl,cnt=1,last=1,rt[N],pp;
struct E{int next,to,val;}e[N<<1];
int head[N],tot;
void add(int x,int y,int f)
{
	e[++tot].to = y;
	e[tot].next = head[x];
	e[tot].val = f;
	head[x] = tot;
}
int in[N],out[N],dfn,id[N],to[N];
void dfs(int x)
{
	in[x] = ++dfn;
	if(to[x])id[dfn] = n-len[x];
	else id[dfn] = -1;
	for(int i = head[x];i;i=e[i].next)
		dfs(e[i].to);
	out[x] = dfn;
}
int L[N*20],R[N*20],sz[N*20],ID;
void update(int &x,int y,int l,int r,int k)
{
	sz[x = ++ID] = sz[y]+1;
	L[x]=L[y],R[x]=R[y];
	if(l==r)return ;
	int mid=(l+r)>>1;
	if(k<=mid)update(L[x],L[y],l,mid,k);
	else update(R[x],R[y],mid+1,r,k);
}
int getans(int k,int l,int r,int x)
{
	if(!k)return 0;
	if(r<=x)return sz[k];
	int mid = (l+r)>>1;
	int ans = getans(L[k],l,mid,x);
	if(x>mid)ans+=getans(R[k],mid+1,r,x);
	return ans;
}
int getm(int x,int y)
{
	int l = 0,r = n,mid;
	while(l<r)
	{
		mid = (l+r)>>1;
		if(sz[L[y]]-sz[L[x]])
			x = L[x],y = L[y],r = mid;
		else x = R[x],y=R[y],l=mid+1;
	}
	return l;
}
void insert(int x,int y)
{
	int p = last,np = ++cnt,q,nq;
	last = np;len[np] = len[p]+1;
	for(;p&&!ch[p][x];p=fa[p])ch[p][x] = np;
	if(!p)fa[np] = 1;
	else
	{
		q = ch[p][x];
		if(len[q]==len[p]+1)fa[np] = q;
		else
		{
			fa[nq=++cnt]=fa[q];
			len[nq] = len[p]+1;
			memcpy(ch[nq],ch[q],sizeof(ch[q]));
			fa[np] = fa[q] = nq;
			for(;p&&ch[p][x]==q;p=fa[p])ch[p][x] = nq;
		}
	}
	to[last] = y;
}
bool match(int lenb)
{
	int w = 1,ff = 1,i,j;pp = 1;
	for(fl = 0;w<=lenb&&ff;)
		for(ff = 0,i = head[pp];i;i=e[i].next)
			if(s[e[i].val]==b[w])
			{
				int tt = e[i].to;
				for(fl=j=0;j<min(len[tt]-len[pp],lenb-w+1);fl++,j++)
					if(s[e[i].val+j]!=b[w+j])
						return pp=tt,0;
				w+=len[tt]-len[pp];pp=tt;ff=1;break;
			}
	return ff;
}
int v[N];
int main()
{
	scanf("%d%s",&n,s+1);
	for(int i = n;i>=1;i--)
		insert(s[i]-'0',i);
	int p,i,j;
	for(v[1] = 1,i = 1;i<=cnt;i++)
		if(to[i])
			for(p = n,j = i;!v[j];j=fa[j])
				p-=len[j]-len[fa[j]],v[j]=true,add(fa[j],j,p+1);
	dfs(1);
	for(i = 1;i<= dfn;i++)
		if(id[i]>=0)
			update(rt[i],rt[i-1],0,n,id[i]);
		else rt[i] = rt[i-1];
	scanf("%d",&m);
	int ans,w;
	while(m--)
	{
		scanf("%s",b+1);
		int lenb = strlen(b+1);
		ans = w = match(lenb)?getm(rt[in[pp]-1],rt[out[pp]]):n;
		for(ans+=fl*(getans(rt[out[pp]],0,n,w)-getans(rt[in[pp]-1],0,n,w)),pp=fa[pp];pp;pp=fa[pp])
            ans+=(len[pp]-len[fa[pp]])*(getans(rt[out[pp]],0,n,w)-getans(rt[in[pp]-1],0,n,w));
        printf("%d\n",ans);
	}
	return 0;
}
