
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int base = 60383;
const int mod = 1747969;
const int T = 205;
const int N = 5005;
const int M = 1000005;
struct HASH
{int next,cnt;ull to;}Hash[M];
int hd[mod+5],Cnt;
ull pow[T],hash[N];
int id[T][N],size[T][N],ans;
void Insert(ull x)
{
	int p = x%mod;
	for(int i = hd[p];i;i=Hash[i].next)
		if(Hash[i].to==x)
		{
			ans+=(Hash[i].cnt<<1)+1;
			Hash[i].cnt++;
			return ;
		}
	ans++;
	Hash[++Cnt].to = x;Hash[Cnt].next = hd[p];hd[p] = Cnt;
	Hash[Cnt].cnt = 1;
}
void Delete(ull x)
{
	int p = x%mod;
	for(int i = hd[p];i;i=Hash[i].next)
		if(Hash[i].to==x)
		{
			ans-=(Hash[i].cnt<<1)-1;
			--Hash[i].cnt;
			return ;
		}
}
struct E
{int next,to;}e[M<<1];
int head[T][N],tot;
void add(int d,int x,int y)
{
	e[++tot].to = y;
	e[tot].next = head[d][x];
	head[d][x] = tot;
}
void dfs(int d,int x,int pre,int fa)
{
	Delete(hash[x]);
	hash[x]-=pow[d]*id[d][x];
	id[d][x] = fa;
	hash[x]+=pow[d]*id[d][x];
	Insert(hash[x]);
	for(int i = head[d][x];i;i=e[i].next)if(e[i].to!=pre)
		dfs(d,e[i].to,x,fa);
}
void uni(int d,int x,int y)
{
	if(id[d][x]==id[d][y])return ;
	if(size[d][id[d][x]]<size[d][id[d][y]])swap(x,y);
	size[d][id[d][x]]+=size[d][id[d][y]];
	add(d,x,y),add(d,y,x);
	dfs(d,y,x,id[d][x]);
}
int main()
{
	int d,n,m;
	scanf("%d%d%d",&d,&n,&m);
	pow[0]=1;
	for(int i = 1;i<= d;i++)pow[i]=pow[i-1]*base;
	for(int i = 1;i<= d;i++)
		for(int j = 1;j<= n;j++)
			id[i][j]=j,size[i][j]=1,hash[j]+=pow[i]*j;
	for(int j = 1;j<=n;j++)Insert(hash[j]);
	int a,b,k;
	for(int i = 1;i<= m;i++)
	{
		scanf("%d%d%d",&a,&b,&k);
		uni(k,a,b);
		printf("%d\n",ans);
	}
}
