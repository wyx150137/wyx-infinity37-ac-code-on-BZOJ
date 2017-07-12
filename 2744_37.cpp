
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 3005;
struct E
{int next,to;}e[N*N>>2];
int head[N],tot=1;
void add(int x,int y)
{
	e[++tot].to =y;
	e[tot].next =head[x];
	head[x]=tot;
}
int res[N],sta[N],ban[N],dfn[N];
int a[N],b[N],A,B,m,n,ans,T1,T2;
bool map[N][N];
int cnt(int x)
{
	int ans = 0;
	while(x)
		x-=x&(-x),ans++;
	return ans;
}
bool get_partner(int x)
{
	if(ban[x]==T1)return false;
	for(int i = head[x];i;i=e[i].next)
		if(ban[e[i].to]!=T1&&sta[e[i].to]!=T2)
		{
			sta[e[i].to]=T2;
			if(!res[e[i].to]||dfn[e[i].to]!=T1||get_partner(res[e[i].to]))
			{
				dfn[e[i].to]=T1;
				res[e[i].to]=x;
				return true;
			}
		}
	return false;
}
int getans(int x=0,int y=0)
{
	T1++;
	int ans = 0;
	for(int i = 1;i<= B;i++)
		if(map[x][i]||map[y][i])
			ban[i]=T1,ans++;
	for(int i = 1;i<= B;i++)
		if(b[i]&1)
		{
			++T2;
			if(get_partner(i))
				ans++;
		}
	return B-ans;
}
int main()
{
	scanf("%d%d%d",&A,&B,&m);
	for(int i = 1;i<= A;i++)scanf("%d",&a[i]);
	for(int i = 1;i<= B;i++)scanf("%d",&b[i]);
	memset(map,true,sizeof(map));
	int x,y;
	for(int i = 1;i<= m;i++)
	{
		scanf("%d%d",&x,&y);
		map[x][y]=false;
	}
	for(int i = 1;i<= B;i++)
		if(b[i]&1)
			for(int j = 1;j<= B;j++)
				if(~b[j]&1)
					if(~cnt(b[i]|b[j])&1)
						add(i,j);
	int ans;
	for(int i = 1;i<=B;i++)map[0][i]=0;
	ans=getans();
	for(int i = 1;i<=A;i++)
		ans=max(ans,getans(i)+1);
	for(int i = 1;i<= A;i++)
		if(a[i]&1)
			for(int j = 1;j<= A;j++)
				if(~a[j]&1)
					ans = max(ans,getans(i,j)+2);
	printf("%d\n",ans);
	return 0;
}
