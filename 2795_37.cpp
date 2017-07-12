
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long LL;
const int MOD = 23333333;
const int SED = 37;
const int N = 500005;
int nxt[N],pow[N],n;
int sum[N][26];
void init()
{
	pow[0] = 1;
	for(int i = 1;i<= n;i++)
		pow[i] = (LL)pow[i-1]*SED%MOD;
}
char s[N];
int gcd(int x,int y)
{
	if(y==0)return x;
	return gcd(y,x%y);
}
int gethash(int a,int b)
{
	int lth = b-a+1;
	return (LL)(nxt[a]-(LL)nxt[b+1]*pow[lth]%MOD+MOD)%MOD;
}
int main()
{
	int a,b;
	scanf("%d",&n);
	scanf("%s",s+1);
	for(int i = 1;i<= n;i++)
		for(int j = 0;j<26;j++)
			sum[i][j] = sum[i-1][j]+(s[i]==j+'a');
	for(int i = n;i>=1;i--)
		nxt[i] = ((LL)nxt[i+1]*SED+s[i]-'a')%MOD;
	init();
	int q;
	scanf("%d",&q);
	for(int i = 1;i<= q;i++)
	{
		scanf("%d%d",&a,&b);
		int tmp = b-a+1;
		int lth = tmp;
		for(int j = 0;j<26;j++)
			tmp = gcd(tmp,sum[b][j]-sum[a-1][j]);
		int ans = lth;
		for(int j = 1;j*j<= tmp;j++)
		{
			if(tmp%j==0)
			{
				if(gethash(a,b-lth/j)==gethash(a+lth/j,b))
					ans = min(ans,lth/j);
				if(gethash(a,b-lth/(tmp/j))==gethash(a+lth/(tmp/j),b))
					ans = min(ans,lth/(tmp/j));
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
