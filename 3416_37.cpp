
#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int N = 1e6+5;
bool last[N<<1];
char in[N];
int a[N],q[N],t;
vector<int>ans[N];
int main()
{
	int n,k;
	scanf("%d%d",&n,&k);
	scanf("%s",in+1);
	for(int i = 1;i<= n;i++)
	{
		if(in[i]=='c')a[i] = a[i-1]-k;
		else a[i] = a[i-1]+1;
	}
	int cnt = 0;
	last[n] = true;
	for(int i = 1;i<= n;i++)
	{
		a[i]+=n;
		if(last[a[i]])
		{
			cnt++;
			for(int j = t-k+1;j<= t;j++)
				ans[cnt].push_back(q[j]),last[a[q[j]]] = false;
			ans[cnt].push_back(i);
			t-=k;
		}else
		{
			t++;
			q[t] = i;
			last[a[i]] =true;
		}
	}
	for(int i = cnt;i>=1;i--)
	{
		for(unsigned int j = 0;j<ans[i].size();j++)
			printf("%d ",ans[i][j]);
		printf("\n");
	}
	return 0;
}
