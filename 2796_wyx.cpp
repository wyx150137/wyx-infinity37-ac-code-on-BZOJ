
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>
using namespace std;
typedef long long LL;
const int N = 100+5;

LL f[N];

int solve(LL x)
{
	if(!x) return 0;
	int i = 1;
	while(f[i] < x) ++i;
	if(f[i] == x)return 1;
	return solve(min(f[i]-x,x-f[i-1]))+1;	
}

int main()
{
	f[1] = 1,f[2] = 1;
	for(int i=3;i<=91;++i) f[i] = f[i-1] + f[i-2];
	int T;
	cin >> T;
	while(T--)
	{
		LL tmp ;
		cin >> tmp;
		printf("%d\n",solve(tmp));
	}
}
