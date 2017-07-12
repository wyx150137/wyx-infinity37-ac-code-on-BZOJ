
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
#define s(i) (s[i]-'a')
const int Len = 1<<20;
char w[Len+5];
char s[35];
	int ch[305][26],fail[305],cnt,q[305],h,t;
	bool end[305];
	int len[305];
	void init()
	{
		cnt = 1;
		for(int i = 0;i<26;i++)
			ch[0][i] =1;
	}
	void insert()
	{
		int now = 1,i = 0;
		while(s[i])
		{
			if(!ch[now][s(i)])ch[now][s(i)]=++cnt;
			now = ch[now][s(i)];
			i++;
		}
		len[now] = i;
	}
	void build()
	{
		int h = 0,t = -1;
		q[++t] = 1,fail[0] =1;
		while(h<=t)
		{
			int x=q[h++];
			for(int i = 0;i<26;i++)
			{
				int j=ch[x][i];
				if(!j)continue;
				int k = fail[x];
				while(!ch[k][i])k = fail[k];
				fail[j] = ch[k][i];
				end[j]|=end[fail[j]];
				q[++t]=j;
			}
		}
	}
bool v[Len+5];
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	init();
	for(int i = 1;i<=n;i++)
	{
		scanf("%s",s);
		insert();
	}
	build();
	for(int i = 1;i<= m;i++)
	{
		scanf("%s",w+1);
		int lth = strlen(w+1);
		int now = 1,ans = 0;
		v[0]=true;
		for(int j = 1;j<=lth;j++)
		{
			while(now!=1&&!ch[now][w[j]-'a'])
				now = fail[now];
			if(ch[now][w[j]-'a'])
			{
				now = ch[now][w[j]-'a'];
				for(int tmp = now;tmp!=1;tmp = fail[tmp])
					if(len[tmp])
					{
						v[j]|=v[j-len[tmp]];
						if(v[j])break;
					}
			}
			if(v[j])ans =max(ans,j);
		}
		for(int j = 1;j<=lth;j++)v[j] = false;
		printf("%d\n",ans);
	}
	return 0;
}
