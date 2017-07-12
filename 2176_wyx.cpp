
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>

using namespace std;

unsigned char str[10000000+5];
int len;

int solve()
{
	int i,j,k;
	for(i=0,j=1,k=0;i<len&&j<len;k=0)
	{
		while(str[(i+k)%len] == str[(j+k)%len]) k ++; if(k == len) break;
		if(str[(i+k)%len] > str[(j+k)%len]) i += k + 1, i = (i==j) ? i + 1 : i;
		else j += k + 1, j = (i==j) ? j + 1 : j;
	}
	return min(i,j);
}

int main()
{
	cin >> len;
	scanf("%s",str);
	int tt = solve();
	for(int i=0;i<len;++i)
		printf("%c",str[(tt+i)%len]);
}	
