
#include <stdio.h>
#include <bitset>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 2050;
bitset<N>r[N],u[N],v[N];
char s[N];
int main()
{
	int n;
	scanf("%d",&n);
	scanf("%s",s+1);
	int x =1024,y = 1024,ans = 0;
	for(int i = 1;i<= n;i++)
	{
		v[x][y] = true;
		if(s[i]=='E')
		{
			x++;
			if(!r[x-1][y]&&v[x][y])
				ans++;
			r[x-1][y] = true;
		}else if(s[i]=='W')
		{
			x--;
			if(!r[x][y]&&v[x][y])
				ans++;
			r[x][y] = true;
		}else if(s[i]=='N')
		{
			y--;
			if(!u[x][y]&&v[x][y])
				ans++;
			u[x][y] = true;
		}else
		{
			y++;
			if(!u[x][y-1]&&v[x][y])
				ans++;
			u[x][y-1] = true;
		}
	}
	printf("%d\n",ans);
	return 0;
}
