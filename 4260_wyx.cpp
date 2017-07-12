
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 400000+5;
const int Maxm = N * 40;
#define lowbit(x) ((x)&(-x))
using namespace std;

int tr[Maxm],ch[Maxm][2],root[N],sz;

void change(int x,int y,int val)
{
	for(int i=30;~i;--i)
	{
		int tmp = (1<<i) & val ? 1 : 0;
		ch[y][0] = ch[x][0], ch[y][1] = ch[x][1] , tr[y] = tr[x] + 1;
		x = ch[x][tmp], y = (ch[y][tmp] = ++sz);
	}
	tr[y] =tr[x] + 1;
}

int ask(int L,int R,int val)
{
	int ans = 0;
	for(int i=30;~i;--i)
	{
		int tmp = (1<<i) & val ? 0 : 1;
		if(tr[ch[R][tmp]] - tr[ch[L][tmp]]) ans += (1<<i);
		else tmp ^= 1; R = ch[R][tmp], L = ch[L][tmp];
	}
	return ans;
}

int be[N],ed[N];
int a[N];

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int tmp[N];

void updata(int x,int val)
{
	while(x < N)
	{
		tmp[x] = max(tmp[x],val);
		x += lowbit(x);
	}
}

int ask(int x)
{
	int ans = 0;
	while(x)
	{
		ans = max(ans,tmp[x]);
		x -= lowbit(x);
	}
	return ans;
}

int main()
{
	int n= read();
	for(int i=1;i<=n;++i) a[i] = read() ^ a[i-1];
	for(int i=1;i<=n;++i) change(root[i-1],root[i] = ++sz,a[i]);
	int tmp = root[n]; 
	change(tmp,root[n] = ++sz,0);
	for(int i=1;i<=n;++i)
	{
		be[i] = ask(root[0],root[i],a[i]);
		be[i] = max(be[i],a[i]);
		ed[i] = ask(root[i-1],root[n],a[i-1]);
	}
	for(int i=1;i<=n;++i) updata(i,be[i]);
	int ans = 0;
	for(int i=n;i>1;--i)  
		ans = max(ans,ed[i]+ask(i-1));
	cout << ans << endl;
}
