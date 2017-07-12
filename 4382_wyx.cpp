
#include <map>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1100000+5;
const int seed = 2333333;
typedef unsigned long long ULL;

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

map <ULL,int>mp;

ULL col[N],val[N],cnt;
ULL sum[N];
int pre[N],next[N],q[N],a[N],n,k;
bool vis[N];

int calc(int x,int y)
{
	int tt  = y - x;
	return abs(tt-(n-tt));
}

int main()
{
	col[0] = 1;
	n = read(), k = read();
	for(int i=1;i<=n;++i)col[i] = col[i-1] * seed;
	int tot = 0;
	for(int i=1;i<=n;++i) a[i] = read();

	for(int i=1;i<=n;++i)
	{
		if(pre[a[i]])
		{
			val[pre[a[i]]] += col[++tot];
			val[i] -= col[tot];
		}
		pre[a[i]] = i;
	}

	for(int i=1;i<=n;++i) sum[i] = sum[i-1] + val[i] ;

	for(int i=1;i<=n;++i)
	{
		if(mp[sum[i]])
			next[mp[sum[i]]] = i;
		mp[sum[i]] = i;
	}

	int ans = n;
	int tail = 0;
	for(int i=1;i<=n;++i)
		if(!vis[i])
		{
			tail = 0;
			for(int j=i;j;j=next[j])
				vis[j] = 1,q[++tail] = j;
	//		puts("");
			cnt += (ULL)(tail)*(tail-1)/2;
			for(int i=1,j=1;i<=tail;i++)
            {
            	while(j < i && calc(q[j],q[i]) > calc(q[j+1],q[i])) ++j;
            	ans = min(ans,calc(q[j],q[i]));
            }
		}
	cout << cnt << " " << ans << endl;
	
}
