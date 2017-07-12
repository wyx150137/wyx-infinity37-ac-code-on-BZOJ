
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<cmath>
using namespace std;
typedef long double ld;
int tt,n,l,t;
char s[10];
int trie[60][26],pos[60],tot,fail[60];
ld f[60][356],p[26],a[60][60];
queue<int> q;
void mkfail()
{
	q.push(0);
	while(!q.empty())
	{
		int x=q.front();q.pop();
		for(int i=0;i<t;i++)
		{
			if(trie[x][i])
			{
				if(x) fail[trie[x][i]]=trie[fail[x]][i];
				q.push(trie[x][i]);
			}else trie[x][i]=trie[fail[x]][i];
		}
	}
}
void Gauss(int n)
{
	for(int i=0;i<=n;i++)
	{
		ld mx=0;int pos;
		for(int j=i;j<=n;j++)
		{
			if(fabs(a[j][i])>mx)
			{
				mx=fabs(a[j][i]);
				pos=j;
			}
		}
		for(int j=i;j<=n+1;j++) swap(a[i][j],a[pos][j]);
		for(int j=i+1;j<=n;j++)
		{
			ld f=a[j][i]/a[i][i];
			for(int k=i;k<=tot+1;k++)
				a[j][k]-=f*a[i][k];
		}
	}
	for(int i=n;i>=0;i--)
	{
		for(int j=i+1;j<=n;j++)
			a[i][tot+1]-=a[i][j]*a[j][tot+1];
		a[i][tot+1]/=a[i][i];
	}
}

void calc(int x)
{
	memset(a,0,sizeof a);
	for(int i=0;i<=tot;i++)
	{
		a[i][i]=1;
		if(pos[i]!=-1&&((1<<pos[i])&x)) a[i][tot+1]=f[i][x^(1<<pos[i])];
		else
		{
			a[i][tot+1]=1;
			for(int j=0;j<t;j++)
				a[i][trie[i][j]]-=p[j];
		}
	}
	Gauss(tot);
	for(int i=0;i<=tot;i++) f[i][x]=a[i][tot+1];
}
int main()
{
	scanf("%d",&tt);
	while(tt--)
	{
		memset(trie,0,sizeof trie);
		memset(pos,-1,sizeof pos);
		memset(fail,0,sizeof fail);
		memset(f,0,sizeof f);
		tot=0;
		scanf("%d%d%d",&n,&l,&t);
		for(int i=0;i<n;i++)
		{
			scanf("%s",s);
			int id=0;
			for(int j=0;s[j];j++)
				if(trie[id][s[j]-'a']) id=trie[id][s[j]-'a'];
				else id=trie[id][s[j]-'a']=++tot;
			pos[id]=i;
		}
		for(int i=0,x;i<t;i++)
		{
			scanf("%d",&x);
			p[i]=x/10000.0;
		}
		mkfail();
		for(int i=1;i<(1<<n);i++)
			calc(i);
		printf("%.10f\n",(double)f[0][(1<<n)-1]);
	}
	return 0;
}
