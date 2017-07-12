
#include <map>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#define N 200000+5
using namespace std;

map <pair<int,int>,int> mp;
int A,B,C;
char str[N];

int main()
{
	int n; cin >> n;
	scanf("%s",str+1);
	int ans = 0;
	mp[make_pair(0,0)] = 0;
	for(int i=1;i<=n;++i)
	{
		if(str[i] == 'J') ++ A;
		else if(str[i] == 'O') ++ B;
		else ++C;
		if(mp.find(make_pair(A-B,B-C)) == mp.end())
			mp[make_pair(A-B,B-C)] = i;
		else
			ans = max(ans,i-mp[make_pair(A-B,B-C)]);
	}
	printf("%d\n",ans);
}
