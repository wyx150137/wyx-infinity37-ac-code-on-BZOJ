
#include <stdio.h>
#include <map>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1e5+5;
int s[N];
vector<int>a[20005],st[N],V,M;
bool vis[N],mark[N];
int ans1[N],ans2[N];
struct AC_Machine
{
	map<int,int>ch[N];
	int fail[N];bool end[N];
	int cnt,q[N],h,t;
	AC_Machine()
	{
		cnt = 1;
		for(int i=-1;i<=10000;i++)
            ch[0][i]=1;
        fail[1]=0;
	}
	void insert(int len,int id)
	{
		int now = 1;
		for(int i = 1;i<=len;i++)
		{
			if(!ch[now][s[i]])ch[now][s[i]]=++cnt;
			now = ch[now][s[i]];
		}
		st[now].push_back(id);
	}
	void build()
	{
		h = 0,t = -1;
		q[++t]=1,fail[0] =1;
		while(h<=t)
		{
			int x = q[h++];
			map<int,int>::iterator it;
			for(it=ch[x].begin();it!=ch[x].end();it++)
			{
				int i = it->first;
				int to = it->second;
				int k = fail[x];
				while(!ch[k][i])k = fail[k];
				fail[to] = ch[k][i];
				q[++t]=to;
			}
		}
	}
	void get(int id,int x)
	{
		for(int i = x;i;i=fail[i])
			if(!vis[i])
			{
				vis[i] = true;V.push_back(i);
				for(int j= 0;j<st[i].size();j++)
					if(!mark[st[i][j]])
					{
						mark[st[i][j]]=true;
						M.push_back(st[i][j]);
						ans1[st[i][j]]++;
						ans2[id]++;
					}
			}
			else break;
	}
	void solve(int x)
	{
		int now = 1;
		int sz = a[x].size();
		for(int i = 0;i<sz;i++)
		{
			int t = a[x][i];
			while(!ch[now][t])now = fail[now];
			now = ch[now][t],get(x,now);
		}
		for(int i= 0;i<V.size();i++)vis[V[i]] = false;
		for(int i= 0;i<M.size();i++)mark[M[i]] = false;
		V.clear();M.clear();
	}
}AC;
int main()
{
	int n,m,l;
	scanf("%d%d",&n,&m);
	for(int i= 1;i<= n;i++)
	{
		int x;
		scanf("%d",&l);
		for(int j = 1;j<= l;j++)
		{
			scanf("%d",&x);
			a[i].push_back(x);
		}
		a[i].push_back(-1);
		scanf("%d",&l);
		for(int j = 1;j<= l;j++)
		{
			scanf("%d",&x);
			a[i].push_back(x);
		}
	}
	for(int i = 1;i<= m;i++)
	{
		scanf("%d",&l);
		for(int k =1;k<= l;k++)
			scanf("%d",&s[k]);
		AC.insert(l,i);
	}
	AC.build();
	for(int i= 1;i<= n;i++)
		AC.solve(i);
	for(int i = 1;i<= m;i++)printf("%d\n",ans1[i]);
	for(int i = 1;i<= n;i++)
	{
		printf("%d",ans2[i]);
		if(i!=n)printf(" ");
	}
	return 0;
}
