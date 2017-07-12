
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
const int mod = 10007;
const int N = 1000+5;
using namespace std;
int ans = 0;
char s[N];
int main()
{
	register int i;scanf("%s",s);
	for(i=0;s[i];++i) (ans=(ans<<1)+(ans<<3)+(s[i]-'0'))%=mod;
	cout<<(ans*(ans+1)%mod*(ans+2)%mod*1668%mod)<<endl;
	return 0;
}
