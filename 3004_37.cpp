
#include <stdio.h>
#include <queue>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1200005;
int fa[N],size[N],f[N],ind[N];
int Div[2200],cnt;
void getdiv(int x)
{
	for(int i = 1;i*i<= x;i++)
	{
		if(i*i==x)
			Div[++cnt] = i;
		else if(x%i==0)
			Div[++cnt] = i,Div[++cnt] = x/i;
	}
	return ;
}
queue<int>Q;
int main()
{
	int n;
	scanf("%d",&n);
	getdiv(n);
	sort(Div+1,Div+cnt+1);
	for(int id = 1;id<= 10;id++)
	{
		memset(ind,0,sizeof(ind));
		if(id==1)
			for(int i = 2;i<= n;i++)
			{
				if(i==n)scanf("%d",&fa[i]);
				else scanf("%d,",&fa[i]);
				ind[fa[i]]++;
			}
		else
			for(int i = 2;i<= n;i++)
				{fa[i] = (fa[i]+19940105)%(i-1)+1;ind[fa[i]]++;}
		memset(size,0,sizeof(size));
		memset(f,0,sizeof(f));
		for(int i = 1;i<= n;i++)
			if(!ind[i])
				Q.push(i);
		while(!Q.empty())
		{
			int x = Q.front();
			Q.pop();
			size[x]++;
			ind[fa[x]]--;
			size[fa[x]]+=size[x];
			if(!ind[fa[x]])
				Q.push(fa[x]);
		}
		for(int i = 1;i<= n;i++)
			f[size[i]]++;
		printf("Case #%d:\n",id);
		for(int i = 1;i<= cnt;i++)
		{
			int num = 0;
			for(int j = Div[i];j<=n;j+=Div[i])
				num+=f[j];
			if(num==n/Div[i])
				printf("%d\n",Div[i]);
		}
	}
	return 0;
}
