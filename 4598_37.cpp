
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1e6+5;
typedef unsigned long long ull;
typedef long long ll;
const int sed = 37;
struct E
{
	int next,to;
}e[N<<1];
int head[N],tot;
void add(int x,int y)
{
	e[++tot].to = y;e[tot].next = head[x];head[x] = tot;
	e[++tot].to = x;e[tot].next = head[y];head[y] = tot;
}
int size[N],f[N],sum,maxd,root,n,m;
bool used[N];
void get_root(int x,int fa,int dep)
{
	maxd = max(maxd,dep);
	size[x] = 1,f[x] = 0;
	for(int i = head[x];i;i=e[i].next)
		if(e[i].to!=fa&&!used[e[i].to])
		{
			get_root(e[i].to,x,dep+1);
			size[x]+=size[e[i].to];
			f[x] = max(f[x],size[e[i].to]);
		}
	f[x] = max(f[x],sum-size[x]);
	if(f[x]<f[root])root = x;
}
int cntz[N],cntd[N],tcz[N],tcd[N],mod[N],val[N];
ull hz[N],hd[N];
void dfs(int x,int fa,ull hash,int dep)
{
	hash = hash*sed+val[x];
	if(hash==hz[dep])cntz[mod[dep]]++;
	if(hash==hd[dep])cntd[mod[dep]]++;
	for(int i = head[x];i;i=e[i].next)
		if(e[i].to!=fa&&!used[e[i].to])
			dfs(e[i].to,x,hash,dep+1);
}
ll ans;
void work(int x)
{
	root = 0;
	sum = size[x];
	maxd = 0;
	get_root(x,0,1);
	if(sum<m||2*maxd<m)return ;
	x = root;
	used[x] = true;
	memset(tcz,0,sizeof(int)*(m+1));
	memset(tcd,0,sizeof(int)*(m+1));
	for(int i = head[x];i;i=e[i].next)
		if(!used[e[i].to])
		{
			memset(cntz,0,sizeof(int)*(m+1));
			memset(cntd,0,sizeof(int)*(m+1));
			dfs(e[i].to,x,val[x],2);
			cntz[m] = cntz[0],cntd[m] = cntd[0];
			cntz[m+1] = cntz[1],cntd[m+1] = cntd[1];
			ans+=cntz[0]+cntd[0];
			for(int x = 0;x<m;x++)
			{
				ans+=(ll)cntz[m-x+1]*tcd[x];
				ans+=(ll)cntd[m-x+1]*tcz[x];
			}
			for(int x = 0;x<m;x++)
				tcz[x]+=cntz[x],tcd[x]+=cntd[x];
		}
	for(int i = head[x];i;i=e[i].next)
		if(!used[e[i].to])
			work(e[i].to);
}
char P[N],s[N];
int main()
{
	int cas;
	scanf("%d",&cas);
	while(cas--)
	{
		tot = 0;
		memset(head,0,sizeof(head));
		ans = 0;
		memset(used,0,sizeof(used));
		scanf("%d%d",&n,&m);
		scanf("%s",s+1);
		for(int i = 1;i<= n;i++)
			val[i] = s[i]-'A'+1;
		int x,y;
		for(int i = 1;i< n;i++)
		{
			scanf("%d%d",&x,&y);
			add(x,y);
		}
		scanf("%s",P+1);
		ull pp = 1;
		for(int i = 1,j = 1,k = m;i<= n;i++,pp = pp*sed)
		{
			mod[i] = i%m;
			hz[i] = (P[j]-'A'+1)*pp+hz[i-1];
			hd[i] = (P[k]-'A'+1)*pp+hd[i-1];
			j++;if(j==m+1)j=1;
			k--;if(k==0)k=m;
		}
		f[0] = size[1] = n;
		if(m>1)work(1);
		else 
		{
			for(int i = 1;i<= n;i++)ans+=(val[i]==P[1]-'A'+1);
		}
		printf("%lld\n",ans);
	}
	return 0;
}
