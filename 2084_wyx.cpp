
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 500000+5;
using namespace std;

char str[N];
int p[N];

void solve()
{
	int len = strlen(str+1);
	str[0] = '!' ;
	char *s = str;
	int mx = 0, id = 0;
	for(int i=1;i<=len;++i)
	{
		if(mx < i) p[i] = 0;
		else p[i] = min(mx-i,p[2*id-i]);
		while(s[i+p[i]+1] + s[i-p[i]] == '1' + '0') p[i] ++;
		if(mx < i + p[i]) mx = i + p[i], id = i;
	}	
}

int main()
{
	int n; cin >> n;
	scanf("%s",str+1); solve();
	long long ans = 0;
	for(int i=1;i<=n;++i)  ans = ans + p[i];
	cout << ans << endl;
}
