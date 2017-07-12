
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<set>
#include<ctime>
#include<vector>
#include<queue>
#include<algorithm>
#include<map>
#include<cmath>
#define mod 30031
#define inf 1000000000
#define rad 100000000
#define pa pair<int,int>
#define ll long long 
using namespace std;
int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int bin[20];
int n,K,P,cnt;
int v[205];
struct M{
	ll v[205][205];
	M(){
		memset(v,0,sizeof(v));
	}
	friend M operator*(M a,M b){
		M c;
		for(int i=1;i<=cnt;i++)
			for(int j=1;j<=cnt;j++)
			{
				for(int k=1;k<=cnt;k++)
					c.v[i][j]+=a.v[i][k]*b.v[k][j];
				c.v[i][j]%=mod;
			}
		return c;
	}
	friend M operator^(M a,int b){
		M ans;
		for(int i=1;i<=cnt;i++)ans.v[i][i]=1;
		for(int i=b;i;i>>=1,a=a*a)
			if(i&1)ans=ans*a;
		return ans;
	}
}a,b,ans;
int lowbit(int x)
{
	return x&(-x);
}
void dfs(int now,int num,int sta)
{
	if(num==K)
	{
		v[++cnt]=sta;
		return;
	}
	for(int i=now-1;i;i--)
		dfs(i,num+1,sta+bin[i-1]);
}
void pre()
{
	for(int i=1;i<=cnt;i++)
		for(int j=1;j<=cnt;j++)
		{
			int x=(v[i]<<1)^bin[P]^v[j];
			if(x==lowbit(x))
			    b.v[i][j]=1;
		}
}
int main()
{
	bin[0]=1;for(int i=1;i<20;i++)bin[i]=bin[i-1]<<1;
	n=read();K=read();P=read();
	dfs(P,1,bin[P-1]);
	pre();
	ans.v[1][1]=1;
	M t=b^(n-K);
	ans=ans*t;
	printf("%d\n",ans.v[1][1]);
	return 0;
}
