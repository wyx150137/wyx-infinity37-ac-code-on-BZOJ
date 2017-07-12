
#include <stdio.h>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 100005;
char s[N];
char a[N];
int no[N];
int p[N],maxp,id;
struct Q
{int l,r;}q[N];
vector<int>w[N];
int f[N],c[N];
void update(int x,int y)
{
	for(int i = x;i<N;i+=i&(-i))
		c[i] = min(c[i],y);
}
int getans(int x)
{
	int ans = 0x3f3f3f3f;
	for(int i = x;i>0;i-=i&(-i))
		ans = min(ans,c[i]);
	return ans;
}
int main()
{
	while(scanf("%s",s+1)!=EOF)
	{
		memset(p,0,sizeof(p));
		int n = strlen(s+1);
		int len = 0;
		for(int i = 1;i<=n;i++)
		{
			a[++len]=s[i];
			no[len] = i;
			if(i!=n)a[++len]='^';
		}
		maxp = id = 1;
		for(int i = 1;i<= len;i++)
		{
			p[i] = max(0,min(p[2*id-i],maxp-i));
			while(i+p[i]<=len&&i-p[i]>=1&&a[i+p[i]]==a[i-p[i]])p[i]++;
			p[i]--;
			if(i+p[i]>maxp){maxp = i+p[i],id = i;}
			q[i]=(Q){no[i-p[i]]?no[i-p[i]]:no[i-p[i]+1],no[i+p[i]]?no[i+p[i]]:no[i+p[i]-1]};
		}
		for(int i = 1;i<= len;i++)
			w[i].clear();
		for(int i = 1;i<=len;i++)
			if(q[i].l<=q[i].r)
				w[q[i].r].push_back(q[i].l);
		memset(f,0x3f,sizeof(f));
		memset(c,0x3f,sizeof(c));
		update(n+1,0);
		for(int i = 1;i<= n;i++)
		{
			for(int j = 0;j<w[i].size();j++)
				f[i] = min(f[i],getans(n-w[i][j]+2)+1);
			update(n-i+1,f[i]);
		}
		printf("%d\n",f[n]-1);
	}
	return 0;
}
