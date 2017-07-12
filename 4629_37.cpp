
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 505;
int ch[N][26];
char s[N];
int a[110],fail[N],last[N],w[N],cnt;
void addnew(int v)
{
	int i = 1,now = 0;
	while(s[i])
	{
		if(!ch[now][s[i]-'a'])ch[now][s[i]-'a'] = ++cnt;
		now = ch[now][s[i]-'a'];
		i++;
	}
	w[now]+=v;
}
int q[N],hd,tl;
void Build_fail()
{
	hd = 1,tl = 0;
	for(int i = 0;i<26;i++)
		if(ch[0][i])q[++tl]=ch[0][i];
	while(hd<=tl)
	{
		int x = q[hd++];
		for(int i = 0;i<26;i++)
		{
			int j = ch[x][i];
			if(!j){ch[x][i]=ch[fail[x]][i];continue;}
			int k = fail[x];
			while(k&&!ch[k][i])k=fail[k];
			fail[j] = ch[k][i];
			w[j]+=w[fail[j]];
			if(w[fail[j]])last[j] = fail[j];
			else last[j]=last[fail[j]];
			q[++tl]=j;
		}
	}
}
int f[N][N][6];
bool used[N][N][6];
int K,m;
void dp(int n,int x,int k)
{
	if(k>K||used[n][x][k])return;
	used[n][x][k]=true;
	f[n][x][k]=w[x];
	if(n==m)return ;
	int maxn = -707185547707185547LL,maxb = 0;
	for(int i = 0;i<26;i++)
	{
		dp(n+1,ch[x][i],k);
		if(k<K)
			dp(n+1,ch[x][i],k+1);
		if(f[n+1][ch[x][i]][k]>maxn)
		{
			maxn = f[n+1][ch[x][i]][k];
			maxb = i;
		}
	}
	maxn = 707185547707185547LL;
	for(int i = 0;i<26;i++)
	{
		if(i==maxb)maxn = min(maxn,f[n+1][ch[x][i]][k]);
		else if(k<K)maxn = min(maxn,f[n+1][ch[x][i]][k+1]);
	}
	f[n][x][k]+=maxn;
}
ll di[205][205],tmp[205][205],ret[205][205];
ll ans;
void solve1(int M,bool chu)
{
	ans = 0;
	if(chu)
	{
		memset(di,0xef,sizeof(di));
		for(int i = 0;i<= cnt;i++)
			for(int j = 0;j<26;j++)
				di[i][ch[i][j]]=w[ch[i][j]];
		for(int i = 0;i<= cnt;i++)
			for(int j = 0;j<= cnt;j++)
				ret[i][j]=di[i][j];
		M--;
		while(M)
		{
			for(int i = 0;i<= cnt;i++)
				for(int j = 0;j<= cnt;j++)
					tmp[i][j]=-707185547707185547LL;
			if(M&1)
			{
				for(int i = 0;i<= cnt;i++)
					for(int k = 0;k<= cnt;k++)
						for(int j = 0;j<= cnt;j++)
							tmp[i][j]=max(tmp[i][j],ret[i][k]+di[k][j]);
				for(int i = 0;i<= cnt;i++)
					for(int j = 0;j<= cnt;j++)
						ret[i][j]=tmp[i][j];
			}
			for(int i = 0;i<= cnt;i++)
				for(int j = 0;j<= cnt;j++)
					tmp[i][j]=-707185547707185547LL;
			for(int i = 0;i<= cnt;i++)
				for(int k = 0;k<= cnt;k++)
					for(int j = 0;j<= cnt;j++)
						tmp[i][j]=max(tmp[i][j],di[i][k]+di[k][j]);
			for(int i = 0;i<= cnt;i++)
				for(int j = 0;j<= cnt;j++)
					di[i][j]=tmp[i][j];
			M>>=1;
		}
		memset(di,0xef,sizeof(di));
		for(int i = 0;i<= cnt;i++)
			for(int j = 0;j<26;j++)
				di[i][ch[i][j]]=w[ch[i][j]];
	}
	else
	{
		for(int i = 0;i<= cnt;i++)
			for(int j = 0;j<= cnt;j++)
			{
				tmp[i][j]=-707185547707185547LL;
				for(int k = 0;k<= cnt;k++)
					tmp[i][j]=max(tmp[i][j],ret[i][k]+di[k][j]);
			}
		for(int i = 0;i<= cnt;i++)
			for(int j = 0;j<= cnt;j++)
				ret[i][j]=tmp[i][j];
	}
	for(int i = 0;i<= cnt;i++)
		ans = max(ans,ret[0][i]);
}
void solve2()
{
	int M = m;
	int P = M-300;
	ll res = 0;
	int st;
	for(;P<=M-250;P++)
	{
		for(int i = 0;i<= 300;i++)
			for(int j = 0;j<= cnt;j++)
				for(int k = 0;k<= K;k++)
					used[i][j][k]=false;
		m = M-P;
		dp(0,0,0);
		solve1(P,(P==M-300));
		res = max(res,f[0][0][0]+ans);
	}
	printf("%lld\n",res+1);
}
int main()
{
	int n;
	scanf("%d%d%d",&n,&m,&K);
	for(int i = 1;i<= n;i++)
	{
		scanf("%s%d",s+1,&a[i]);
		addnew(a[i]);
	}
	Build_fail();
	if(m>500&&K==0&&cnt<=200){solve1(m,true);printf("%lld\n",ans);}
	else if(m>500&&K!=0&&cnt<=51){solve2();}
	else
	{
		dp(0,0,0);
		printf("%d\n",f[0][0][0]);
	}
	return 0;
}
