
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;
map <int,int>mp;
inline int read()
{
	int x = 0, f = 1; char ch = getchar();
	while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar(); }
	while (ch >= '0' && ch <= '9') { x = x * 10 + ch - '0'; ch = getchar(); }
	return x * f;
}
int main()
{
	int T=read();
	while(T--)
	{
		mp.clear();
		int n=read();
		for(int i=1;i<=n;++i)
		{
			int tmp=read();
			if(!mp[tmp])
			{
				mp[tmp]=1;
				if(i==1)
					printf("%d",tmp);
				else
					printf(" %d",tmp);
			}
		}
		puts("");
	}
}
