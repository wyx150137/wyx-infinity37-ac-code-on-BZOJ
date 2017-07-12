
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
#define s(i) (s[i]-'A')
const int P = 6005;
const int N = 65;
const int Len = 105;
const int mod = 10007;
char s[Len];
int f[Len][P];
struct AC_Machine
{
	int ch[P][26],cnt,fail[P],q[P],h,t;
	bool danger[P];
	AC_Machine()
	{
		cnt = 1;
		for(int i = 0;i<26;i++)ch[0][i] = 1;
	}
	void insert()
	{
		int now = 1,i = 0;
		while(s[i])
		{
			if(!ch[now][s(i)])ch[now][s(i)] = ++cnt;
			now = ch[now][s(i)];
			i++;
		}
		danger[now] = true;
	}
	void build()
	{
		h = t,t = -1;
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
				if(danger[fail[to]])
					danger[to] = true;
				q[++t] = to;
			}
		}
	}
	void dp(int x)
	{
		for(int i = 1;i<= cnt;i++)
		{
			if(danger[i]||!f[x-1][i])continue;
			for(int j = 0;j<26;j++)
			{
				int k=i;
				while(!ch[k][j])k=fail[k];
				(f[x][ch[k][j]]+=f[x-1][i])%=mod;
			}
		}
	}
}AC;
int quick_pow(int x,int y)
{
	if(y==0)return 1;
	int tmp = quick_pow(x,y>>1);
	if(y&1)return tmp*tmp%mod*x%mod;
	return tmp*tmp%mod;
}
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	int ans = quick_pow(26,m);
	for(int i = 1;i<= n;i++)
	{
		scanf("%s",s);
		AC.insert();
	}
	AC.build();
	f[0][1] = 1;
	for(int i = 1;i<=m;i++)AC.dp(i);
	for(int i = 1;i<= AC.cnt;i++)
		if(!AC.danger[i])
			ans = (ans-f[m][i]+mod)%mod;
	printf("%d\n",ans);
	return 0;
}
