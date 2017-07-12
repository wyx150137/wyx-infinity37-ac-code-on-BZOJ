
#include <stdio.h>
#include <queue>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
typedef long long LL;
using namespace std;
const int N = 1005;
LL INF;
int city[N];
bool v[N];
int d2[N],k2[N][N],n;
LL d1[N],k1[N][N];
queue<int>Q;
void spfa(int s)
{
	memset(d1,0x3f,sizeof(d1));
	memset(d2,0x3f,sizeof(d2));
	d1[s] = 0;d2[s] = 0;
	v[s] = true;
	Q.push(s);
	while(!Q.empty())
	{
		int x = Q.front();
		Q.pop();
		v[x]=false;
		for(int i = 1;i<= n;i++)
		{
			if(k1[x][i]==INF)continue;
			if(d1[x]+k1[x][i]<d1[i])
			{
				d1[i] = d1[x]+k1[x][i];
				d2[i] = d2[x]+k2[x][i];
				if(!v[i])Q.push(i),v[i] = true;
			}else if(d1[x]+k1[x][i]>d1[i])continue;
			else if(d2[x]+k2[x][i]<d2[i])
			{
				d2[i] = d2[x]+k2[x][i];
				if(!v[i])Q.push(i),v[i] = true;
			}
		}
	}
}
int main()
{
	memset(k1,0x3f,sizeof(k1));
	memset(k2,0x3f,sizeof(k2));
	INF = k1[0][0];
	int s,t,m;
	scanf("%d%d%d",&s,&t,&m);
	for(int i = 1;i<= m;i++)
	{
		int cost,len;
		scanf("%d%d",&cost,&len);
		for(int j = 1;j<= len;j++)
		{
			scanf("%d",&city[j]);
			n = max(n,city[j]);
		}
		for(int j = 1;j<= len;j++)
			for(int k = j+1;k<= len;k++)
			{
				if(k1[city[j]][city[k]]==cost)
					k2[city[j]][city[k]] = min(k2[city[j]][city[k]],k-j);
				if(k1[city[j]][city[k]]>cost)
				{
					k1[city[j]][city[k]] = cost;
					k2[city[j]][city[k]] = k-j;
				}
			}
	}
	spfa(s);
	if(d1[t]!=INF)printf("%lld %d\n",d1[t],d2[t]);
	else printf("-1 -1\n");
	return 0;
}
