
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 3005;
bool map[N][N];
bool v[N];
int main()
{	
	int n,m,x,y;
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= m;i++)
	{
		scanf("%d%d",&x,&y);
		map[x][y] = map[y][x] = true;
	}
	int cnt = 0;
	for(int i = 1;i<= n;i++)
		if(!v[i])
			for(int j = i+1;j<= n;j++)
				if(!v[j]&&!map[i][j])
				{
					v[i] = v[j] = true;
					break;
				}
	for(int i = 1;i<= n;i++)
	{
		if(!v[i])
			printf("%d%c",i,++cnt==n/3?' ':'\n');
		if(cnt==n/3)break;
	}
	return 0;
}
