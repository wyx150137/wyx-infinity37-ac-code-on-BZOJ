
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1e5+5;
int s[N];char str[N];
bool ins[N],vis[N];
struct AC_Machine
{
	int ch[N][2],fail[N];bool end[N];
	int cnt,q[N],h,t;
	AC_Machine()
	{
		cnt = 1;
		for(int i = 0;i<2;i++)
			ch[0][i] = 1;
	}
	void insert(int len)
	{
		int now = 1;
		for(int i = 1;i<=len;i++)
		{
			if(!ch[now][s[i]])ch[now][s[i]]=++cnt;
			now = ch[now][s[i]];
		}
		end[now] = true;
	}
	void build()
	{
		h = 0,t = -1;
		q[++t] = 1,fail[0] = 1;
		while(h<=t)
		{
			int x = q[h++];
			for(int i = 0;i<2;i++)
			{
				int j = ch[x][i];
				if(!j)
				{
					ch[x][i]=ch[fail[x]][i];
					continue;
				}
				int k = fail[x];
				while(!ch[k][i])k = fail[k];
				fail[j] = ch[k][i];
				end[j]|=end[fail[j]];
				q[++t]=j;
			}
		}
	}
	bool dfs(int x)
	{
		ins[x] = true;
		for(int i = 0;i<2;i++)
		{
			int v = ch[x][i];
			if(ins[v])return true;
			if(vis[v]||end[v])continue;
			vis[v] = true;
			if(dfs(v))return true;
		}
		ins[x] = false;
		return false;
	}
}AC;
int main()
{
	int n;
	scanf("%d",&n);
	for(int i = 1;i<= n;i++)
	{
		scanf("%s",str+1);
		int len = strlen(str+1);
		for(int j = 1;j<= len;j++)
			s[j] = str[j]-'0';
		AC.insert(len);
	}
	AC.build();
	if(AC.dfs(1))printf("TAK\n");
	else printf("NIE\n");
	return 0;
}
