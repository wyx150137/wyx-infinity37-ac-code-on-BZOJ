
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const ll mod1 = 1e9+7;
const ll mod2 = 1e9+9;
const ll base1 = 2591;
const ll base2 = 2593;
const int N = 1e3+5;
const int MOD = N*N;
ll sum1[N][N],sum2[N][N];
ll basel[3]={0,1,1},baser[3]={0,1,1};
char s[N][N];
ll ans_time,ans1,ans2;
struct Hash_list
{
	int next;
	ll hv1,hv2;
	int times;
}e[N*N];
int head[N*N],tot;
inline int& Hash(ll h1,ll h2)
{
	ll x = h1*h2%MOD;
	for(int i = head[x];i;i=e[i].next)
		if(e[i].hv1==h1&&e[i].hv2==h2)
			return e[i].times;
	tot++;
	e[tot].next = head[x];e[tot].hv1 = h1,e[tot].hv2 = h2;
	e[tot].times = 0;head[x] = tot;
	return e[tot].times;
}
int n,m,a,b;
ll gethash1(int i,int j)
{
	return 
		((sum1[i][j]-
		sum1[i-a][j]*basel[1]-
		sum1[i][j-b]*baser[1]+
		sum1[i-a][j-b]*basel[1]%mod1*baser[1])%mod1+mod1)%mod1;
}
ll gethash2(int i,int j)
{
	return 
		((sum2[i][j]-
		sum2[i-a][j]*basel[2]-
		sum2[i][j-b]*baser[2]+
		sum2[i-a][j-b]*basel[2]%mod2*baser[2])%mod2+mod2)%mod2;
}
int main()
{
	//freopen("x.in","r",stdin);
	scanf("%d %d\n",&n,&m);
	for(int i = 1;i<= n;i++)
	{
		fread(s[i]+1,m+1,1,stdin);
		for(int j = 1;j<= m;j++)
			sum1[i][j] = sum2[i][j] = s[i][j];
	}
	for(int i = 1;i<= n;i++)
		for(int j = 1;j<= m;j++)
			sum1[i][j]=(sum1[i][j]+sum1[i-1][j]*base1)%mod1,
			sum2[i][j]=(sum2[i][j]+sum2[i-1][j]*base1)%mod2;
	for(int i = 1;i<= n;i++)
		for(int j = 1;j<= m;j++)
			sum1[i][j]=(sum1[i][j]+sum1[i][j-1]*base2)%mod1,
			sum2[i][j]=(sum2[i][j]+sum2[i][j-1]*base2)%mod2;
	scanf("%d%d",&a,&b);
	printf("%d %d\n",a,b);
	for(int i = 1;i<= a;i++)
		basel[1]*=base1,basel[1]%=mod1,
		basel[2]*=base1,basel[2]%=mod2;
	for(int i = 1;i<= b;i++)
		baser[1]*=base2,baser[1]%=mod1,
		baser[2]*=base2,baser[2]%=mod2;
	ans_time = 0;
	for(int i = a;i<= n;i++)
		for(int j = b;j<= m;j++)
		{
			ll hash1 = gethash1(i,j);
			ll hash2 = gethash2(i,j);
			int &val = Hash(hash1,hash2);
			if(++val>ans_time)
			{
				ans_time = val;
				ans1 = hash1,ans2 = hash2;
			}
		}
	bool flag = true;
	for(int i = a;i<= n&&flag;i++)
		for(int j = b;j<= m&&flag;j++)
		{
			ll hash1 = gethash1(i,j);
			ll hash2 = gethash2(i,j);
			if(hash1==ans1&&hash2==ans2)
			{
				for(int k=i-a+1;k<=i;k++,puts(""))
					for(int l = j-b+1;l<=j;l++)
						putchar(s[k][l]);
				flag = false;
			}
		}
	printf("%lld\n",ans_time);
	for(int i = a;i<= n;i++)
		for(int j = b;j<= m;j++)
		{
			ll hash1 = gethash1(i,j);
			ll hash2 = gethash2(i,j);
			if(hash1==ans1&&hash2==ans2)
				printf("%d %d\n",i-a+1,j-b+1);
		}
	return 0;
}
