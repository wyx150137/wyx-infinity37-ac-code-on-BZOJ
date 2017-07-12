
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>

const int N = 600000+5;

using namespace std;

int cnt;
int root[N];

int son[N*24][2];
int size[N*24];

void insert(int x,int y,int val)
{
	for(int i=23;~i;--i)
	{
		int tmp = (1<<i) & val ? 1 : 0;
		son[y][0] = son[x][0], son[y][1] = son[x][1], size[y] = size[x] + 1;
		x = son[x][tmp], y = (son[y][tmp] = ++cnt);
	}
	size[y] = size[x] + 1;
}

int ask(int L,int R,int val)
{
	int ans = 0;
	for(int i=23;~i;--i)
	{
		int tmp = (1<<i) & val ? 1 : 0; tmp ^= 1;
		if(size[son[R][tmp]] - size[son[L][tmp]]) ans += (1<<i);
		else tmp ^= 1;
		R = son[R][tmp], L = son[L][tmp];
	}
	return ans;
}

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch - '0';ch = getchar();}
	return x*f;
}

int T[N];

int main()
{
//	freopen("04.in", "r", stdin);
	int n = read() , m = read();
//	insert(root[0],root[0],0);
	for(int i=2;i<=n+1;++i) T[i] = read() ^ T[i-1];
	for(int i=1;i<=n+1;++i) insert(root[i-1],root[i]=++cnt,T[i]);
//	for(int i=1;i<=n+1;++i) cout  << T[i] << " " << root[i] << endl;puts("");
	char str[10]; ++n;
	while(m--)
	{
		scanf("%s",str);
		if(str[0] == 'A')
		{
			++n;T[n] = read()^T[n-1];root[n] = ++cnt;
			insert(root[n-1],root[n],T[n]);
		}
		else
		{
			int L = read(), R = read(), x = read();
			printf("%d\n",ask(root[L-1],root[R],T[n]^x));
		}
	}
}
