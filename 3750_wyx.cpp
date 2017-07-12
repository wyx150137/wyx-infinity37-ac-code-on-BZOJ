
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 1000+5;
using namespace std;

struct data
{
	int x,y;
	data () {}
	data (int _x,int _y)
	:x(_x),y(_y){}
}p[N*N];

int cnt;
char s1[N][N],s2[N][N];

int main()
{
	int T;
	cin >> T;
	int n,m,a,b;
	while(T--)
	{
		cin >> n >> m >> a >> b;
		for(int i=1;i<=n;++i)scanf("%s",s1[i]+1);
		cnt = 0;
		for(int i=1;i<=a;++i)
		{
			scanf("%s",s2[i]+1);
			for(int j=1;j<=b;++j)
				if(s2[i][j] == 'x')
					p[++cnt] = data(i,j);	
		}
		bool flag = false;
		for(int i=1;i<=n;++i)
		{
			for(int j=1;j<=m;++j)
			{
				if(s1[i][j] == 'x')
				{
					for(int k=1;k<=cnt;++k)
					{
						data t1 = data(i+p[k].x-p[1].x,j+p[k].y-p[1].y);
						if(t1.x > n || t1.y > m )
						{
							flag = 1;
							break;
						}
						if(s1[t1.x][t1.y] != 'x')
						{
							flag = 1;
							break;
						}
						s1[t1.x][t1.y] = '.';
					}
				}
				if(flag) break;
			}
			if(flag) break;
		}
		if(flag)
			puts("NIE");
		else puts("TAK");
	}
}
