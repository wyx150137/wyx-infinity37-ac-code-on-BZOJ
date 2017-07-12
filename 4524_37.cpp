
#include <stdio.h>
#include <set>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 18000000+5;
struct Heap
{
	int ls,rs;
	int dis;ll key,mul;
}tr[N];
int tot;
ll n;int E;
ll quick_pow(ll x,ll y)
{
	ll res = 1;
	while(y)
	{
		if(y&1)res=res*x;
		x = x*x;
		y>>=1;
	}
	return res;
}
int newnode(int x)
{
	if(!x)return 0;
	int t = ++tot;
	tr[t] = tr[x];
	return t;
}
int multi(int x,ll y)
{
	int t = newnode(x);
	tr[t].mul*=y,tr[t].key*=y;
	return t;
}
void Push_down(int x)
{
	if(tr[x].mul>1)
	{
		tr[x].ls = multi(tr[x].ls,tr[x].mul);
		tr[x].rs = multi(tr[x].rs,tr[x].mul);
		tr[x].mul = 1;
	}
}
int merge(int x,int y)
{
	if(!x)return newnode(y);
	if(!y)return newnode(x);
	Push_down(x),Push_down(y);
	if(tr[x].key<tr[y].key)swap(x,y);
	int t = newnode(x);
	tr[t].rs = merge(tr[x].rs,y);
	if(tr[tr[t].rs].dis>tr[tr[t].ls].dis)
		swap(tr[t].ls,tr[t].rs);
	tr[t].dis = tr[tr[t].rs].dis+1;
	return t;
}
int pop(int x)
{
	Push_down(x);
	return merge(tr[x].ls,tr[x].rs);
}
struct Int
{
	int id;
	Int(int _id):id(_id){}
	bool operator <(const Int &s)const
	{
		return tr[id].key>tr[s.id].key||tr[id].key==tr[s.id].key&&id<s.id;
	}
};
multiset<Int>ans;
int prime[200],cnt;
bool vis[200];
int f[200][100],g[200][200];
void get_prime()
{
	for(int i = 2;i<= 127&&i<= n;i++)
	{
		if(!vis[i])prime[++cnt]=i;
		for(int j = 1;j<=cnt&&i*prime[j]<=127;j++)
		{
			vis[i*prime[j]]=true;
			if(i%prime[j]==0)break;
		}
	}
}
int main()
{
	scanf("%lld%d",&n,&E);
	get_prime();
	f[0][0]=g[0][0]=1;
	tr[1].dis = tr[1].key = tr[1].mul = tot = 1;
	for(int i = 1;i<= cnt;i++)
	{
		for(int j = 1;j<= (int)floor(log(n)/log(prime[i]));j++)
		{
			for(int k = 1;k<= j;k++)
			{
				int t = multi(g[i-1][j-k],quick_pow(prime[i],k));
				f[i][j] =merge(f[i][j],t);
			}
			ans.insert(Int(f[i][j]));
			g[i][j] = merge(g[i-1][j],f[i][j]);
		}
		g[i][0]=g[i-1][0];
	}
	E--;
	while(E--)
	{
		int t = (*ans.begin()).id;
		ans.erase(ans.begin());
		ans.insert(Int(merge(tr[t].ls,tr[t].rs)));
	}
	printf("%lld\n",tr[(*ans.begin()).id].key);
	return 0;
}
