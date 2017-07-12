
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int mod = 10007;
char s[1005];
int quick_pow(int x,int y)
{
	if(y==0)return 1;
	int tmp = quick_pow(x,y>>1);
	if(y&1)return tmp*tmp%mod*x%mod;
	else return tmp*tmp%mod;
}
int main()
{	
	int d,n=0;
	scanf("%s",s+1);
	for(int i = 1;s[i];i++)
		n = (n*10+s[i]-'0')%mod;
	int ans = n*(n+1)%mod*(n+2)%mod;
	ans = ans*quick_pow(6,mod-2)%mod;
	printf("%d\n",ans);
	return 0;
}
