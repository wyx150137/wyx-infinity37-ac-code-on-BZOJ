
#include <stdio.h>
#include <queue>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 2e5+5;
int nxt[N];
bool ins[N],vis[N];
int head[N],tot,ind[N];
queue<int>Q;
void getans(int x,int c)
{
	vis[x] = true;
	ins[x] = c;
	if(!vis[nxt[x]])getans(nxt[x],c^1);
}
int main()
{
	int n,x;
	scanf("%d",&n);
	n<<=1;
	for(int i = 1;i<= n;i++)
		scanf("%d",&nxt[i]),ind[nxt[i]]++;
	for(int i = 1;i<= n;i++)
		if(!ind[i])
			Q.push(i),vis[i]=true;
	while(!Q.empty())
	{
		int x = Q.front();
		Q.pop();
		ins[x] = true;
		int y = nxt[x];
		if(vis[y])continue;
		vis[y] = true;
		int z = nxt[y];
		if(!--ind[z])
		{
			Q.push(z);
			vis[z] = true;
		}
	}
	for(int i = 1;i<= n;i++)
		if(!vis[i])
			getans(i,1);
	for(int i = 1;i<= n;i++)
		if(ins[i])printf("%d ",i);
	return 0;
}
