
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 301;
struct T
{
	int c[N][N];
	T()
	{
		memset(c,0,sizeof(c));
	}
	void update(int x,int y,int v)
	{
		for(int i= x;i<N;i+=i&(-i))
			for(int j = y;j<N;j+=j&(-j))
				c[i][j]+=v;
	}
	int getans(int x,int y)
	{
		int ans= 0;
		for(int i= x;i>0;i-=i&(-i))
			for(int j = y;j>0;j-=j&(-j))
				ans+=c[i][j];
		return ans;
	}
}tree[105];
int map[N][N];
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= n;i++)
		for(int j = 1;j<= m;j++)
		{
			scanf("%d",&map[i][j]);
			tree[map[i][j]].update(i,j,1);
		}
	int q,opt,a,b,c,d,v;
	scanf("%d",&q);
	for(int i = 1;i<= q;i++)
	{
		scanf("%d",&opt);
		if(opt==1)
		{
			scanf("%d%d%d",&a,&b,&v);
			tree[map[a][b]].update(a,b,-1);
			tree[v].update(a,b,1);
			map[a][b] = v;
		}else
		{
			int ans = 0;
			scanf("%d%d%d%d%d",&a,&b,&c,&d,&v);
			ans = ans+tree[v].getans(b,d);
			ans = ans-tree[v].getans(b,c-1);
			ans = ans-tree[v].getans(a-1,d);
			ans = ans+tree[v].getans(a-1,c-1);
			printf("%d\n",ans);
		}
	}
	return 0;
}
