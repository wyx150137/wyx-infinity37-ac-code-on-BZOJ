
#include <bitset>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 3000+5;
using namespace std;

bitset <N> mp[N],vis;

char getc()
{
    static const int LEN = 1<<15;
    static char buf[LEN],*S=buf,*T=buf;
    if(S == T)
    {
        T = (S=buf)+fread(buf,1,LEN,stdin);
        if(S == T)return EOF;
    }
    return *S++;
}
  
inline int read()
{
    static char ch;
    static int D;
    while(!isdigit(ch=getc()));
    for(D=ch-'0'; isdigit(ch=getc());)
        D=(D<<3)+(D<<1)+(ch-'0');
    return D;
}

int main()
{
	int n = read(), m = read(),x,y;
	int i,j;


	for(i=1;i<=m;++i)
	{
		x = read(), y = read();
		mp[x][y] = mp[y][x] = 1;
	}	

	for(i=1;i<=n;++i)
		if(!vis[i])
			for(j=i+1;j<=n;++j)
				if(!vis[j] && !mp[i][j])
				{
					vis[i] = vis[j] = 1;
					break;
				}


	int cnt = 0;
	int tt = n / 3;

	for(int i=1;i<=n;++i)
		if(!vis[i])
		{
			++cnt;if(cnt!=tt) printf("%d ",i);
			else {printf("%d\n",i);break;}
		}
}
