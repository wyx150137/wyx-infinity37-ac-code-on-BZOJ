
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 1000000+5;
using namespace std;
int fa[N];
int find(int x)
{
	return fa[x]^x?fa[x]=find(fa[x]):fa[x];
}

int p[N],V[N];
int cnt[N],MIN[N];
int id[N],sum[N];

void DFS(int x)
{
	if(MIN[x]) return;
	DFS(p[x]);
	MIN[x] = find(MIN[p[x]]-1);
	if(++cnt[MIN[x]] == 1)
		id[MIN[x]] = x;
}

inline int read()
{
	int x = 0, f = 1; char ch = getchar();
	while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar(); }
	while (ch >= '0' && ch <= '9') { x = x * 10 + ch - '0'; ch = getchar(); }
	return x * f;
}

int main()
{
 	int n = read();
    for(int i=1;i<=n;++i)fa[i] = i;
    for(int i = 1;i<= n;i++)
    {
		p[i] = read(),V[i] = read();
		if(p[i] == i) 
			V[i] = n;
		if(V[i])
		{
			fa[V[i]] = V[i] - 1;
			MIN[i] = V[i];
		}
    }

    for(int i=1;i<=n;++i)
    	if(!MIN[i])
    		DFS(i);

    for(int i=1;i<=n;++i)
    	sum[i] = sum[i-1] + (fa[i] == i);

    int tmp = 0;

    for(int i=1;i<=n;++i)
    {
    	if(cnt[i])
    	{
    		if(cnt[i] == 1 && sum[i] == tmp + 1)
    			V[id[i]] = i,tmp ++;
    		else if(cnt[i] + tmp == sum[i])
    			tmp = sum[i];
    		else cnt[i+1] += cnt[i];
    	}
    }

   	for(int i=1;i<=n;++i)
   		printf("%d\n",V[i]);
}
