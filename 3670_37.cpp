
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 1e6+5;
const int mod = 1e9+7;
char s[N];
int nxt[N],dep[N],len;
void getnxt()
{
	int i = 0,j = -1;
	nxt[i] = j;
	dep[i] = 0;
	while(i<len)
	{
		if(j==-1||s[i]==s[j])
		{
			i++,j++;
			dep[i] = dep[j]+1;
			nxt[i] = j;
		}else j = nxt[j];
	}
}
void getans()
{
	int i = 0,j = -1;
	ll ans = 1;
	while(i<len)
	{
		if(j==-1||s[i]==s[j])
		{
			i++,j++;
			while(j!=-1&&(j<<1)>i)
				j = nxt[j];
			if(j!=-1&&i!=-1)
				ans = ans*(dep[j]+1)%mod;
		}else
			j = nxt[j];
	}
	printf("%lld\n",ans);
}	
int main()
{
	int n;
	scanf("%d",&n);
	while(n--)
	{
		scanf("%s",s);
		len = strlen(s);
		getnxt();
		getans();
	}
	return 0;
}
