
#include <stdio.h>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
#define s(i) (s[i]-'a')
const int N = 1e5+5;
char s[N];
struct Gragh
{int next,to;}e[N<<1];
int head[N],tot,Dfn;
void add(int x,int y)
{e[++tot].to = y;e[tot].next = head[x];head[x] = tot;}
struct P
{int no,x;};
int dfn[N],end[N];
void dfs(int x)
{
	dfn[x] = ++Dfn;
	for(int i = head[x];i;i=e[i].next)
		dfs(e[i].to);
	end[x] = Dfn;
}
int c[N],id[N];
void update(int x,int y)
{
	for(int i = x;i<N;i+=i&(-i))
		c[i]+=y;
}
int getans(int x)
{
	int ans = 0;
	for(int i = x;i>0;i-=i&(-i))
		ans+=c[i];
	return ans;
}
vector<P>ask[N];
int ans[N];
struct AC_Machine
{
	int ch[N][26],sum[N],fail[N],from[N];
	int q[N],h,t,cnt;
	AC_Machine()
	{
		cnt = 1;
		for(int i = 0;i<26;i++)
			ch[0][i] = 1;
	}
	void insert()
	{
		scanf("%s",s);
		int now = 1,i = 0,num = 0;
		while(s[i])
		{
			if(s[i]=='P')
			{
				num++;
				id[num] = now;
				sum[now]++;i++;continue;
			}
			if(s[i]=='B'){now = from[now];i++;continue;}
			if(!ch[now][s(i)])
				{ch[now][s(i)]=++cnt;from[cnt]=now;}
			now = ch[now][s(i)];
			i++;
		}
	}
	void build()
	{
		h = 0,t = -1;
		q[++t] = 1,fail[1] = 0;
		while(h<=t)
		{
			int x = q[h++];
			for(int i = 0;i<26;i++)
			{
				int to = ch[x][i];
				if(!to)continue;
				int k = fail[x];
				while(!ch[k][i])k = fail[k];
				fail[to] = ch[k][i];
				q[++t] = to;
				add(fail[to],to);
			}
		}
	}
}AC;
int main()
{
	AC.insert();
	AC.build();
	dfs(1);
	int m,x,y;
	scanf("%d",&m);
	for(int i = 1;i<= m;i++)
	{
		scanf("%d%d",&x,&y);
		ask[y].push_back((P){i,x});
	}
	int num = 0,n = strlen(s)-1,now = 1;
	for(int i =0;i<=n;i++)
	{
		if(s[i]=='P')
		{
			num++;
			int sz = ask[num].size();
			for(int j = 0;j<sz;j++)
			{
				int x = id[ask[num][j].x];
				ans[ask[num][j].no] = getans(end[x])-getans(dfn[x]-1);
			}
			continue;
		}
		if(s[i]=='B'){update(dfn[now],-1);now = AC.from[now];continue;}
		now = AC.ch[now][s(i)];
		update(dfn[now],1);
	}
	for(int i = 1;i<= m;i++)
		printf("%d\n",ans[i]);
	return 0;
}
