
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int sed = 299;
typedef unsigned long long ll;
const int N = 6e6+5;
ll pow[205];
ll hash[N];
char s[205];
int cnt;
int main()
{
	int n,l,q;
	pow[0]=1;
	for(int i = 1;i<205;i++)pow[i]=pow[i-1]*sed;
	scanf("%d%d%d",&n,&l,&q);
	for(int i = 1;i<= n;i++)
	{
		ll tmp = 0;
		scanf("%s",s+1);
		int lth = strlen(s+1);
		for(int i = 1;i<=lth;i++)
			tmp = tmp*sed+s[i];
		for(int i = 1;i<=lth;i++)
		{
			ll tt = tmp-s[i]*pow[lth-i];
			hash[++cnt] = tt;
		}
	}
	sort(hash+1,hash+cnt+1);
	ll ans = 0;
	int cc = 0;
	for(int i = 1;i<= cnt;i++)
	{
		if(i==1||hash[i]!=hash[i-1])
			cc=-1;
		cc++;
		ans+=cc;
	}
	printf("%llu\n",ans);
	return 0;
}
