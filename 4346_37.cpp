
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 2e5+5;
const int INF = 1e9;
struct E
{int next,to;}e[N<<1];
int head[N],tot;
void add(int x,int y)
{
	e[++tot].to = y;e[tot].next = head[x];head[x] = tot;
	e[++tot].to = x;e[tot].next = head[y];head[y] = tot;
}
int f[N][3][3],g[N][3],p[N][3],q[N][3],c[3][3];
void dp(int x,int fa)
{
	p[x][1] = 1,p[x][2] = 2;
	memset(g[x],0x3f,sizeof(g[x]));
	memset(f[x],0x3f,sizeof(f[x]));
	f[x][0][0] = 0;
	for(int i = head[x];i;i=e[i].next)
		if(e[i].to!=fa)
		{
			int y = e[i].to;
			dp(y,x);
			int tmp = min(min(p[y][1],p[y][2]),q[y][1]);
			for(int j = 0;j<3;j++)
				tmp = min(tmp,g[y][j]);
			p[x][1]+=tmp,p[x][2]+=min(tmp,q[y][2]);
			memset(c,0x3f,sizeof(c));
			for(int j = 0;j<3;j++)
				for(int k = 0;k<3;k++)
					if(f[x][j][k]<INF)
					{
						tmp = f[x][j][k];
						for (int l=1; l<3; l++) c[min(2,j+l)][k]=min(c[min(2,j+l)][k],tmp+p[y][l]);  
                   		for (int l=0; l<3; l++) c[j][max(k,2-l)]=min(c[j][max(k,2-l)],tmp+g[y][l]);  
					}
			memcpy(f[x],c,sizeof(c));
		}
	for (int i=0; i<3; i++)  
        for (int j=0; j<=i; j++) g[x][i]=min(g[x][i],f[x][i][j]);  
    q[x][1]=min(f[x][0][1],f[x][1][2]);  
    q[x][2]=f[x][0][2];  
}
int main()
{
	int n,x,y;
	scanf("%d",&n);
    for (int i=1; i<n; i++){  
    	scanf("%d%d",&x,&y); 
        add(x,y);
    }  
    dp(1,0); 
    int ans=min(p[1][1],p[1][2]);  
    for (int i=0; i<3; i++) ans=min(ans,g[1][i]);  
    printf("%d\n",ans);  
	return 0;
}
