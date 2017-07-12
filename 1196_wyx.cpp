
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
using namespace std;
#define ll long long 
const int MAXN = 20000 + 10;
inline int read()
{
	int x = 0, f = 1; char ch = getchar();
	while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar(); }
	while (ch >= '0' && ch <= '9') { x = (x<<1)+(x<<3) + ch - '0'; ch = getchar(); }
	return x * f;
}
struct Edge
{
	int u, v, c1, c2;
}edge[MAXN<<1];
int n, m, k;
int f[MAXN];
int find(int x)
{
	return f[x] == x ? x : f[x] = find(f[x]);
}
bool check(int x)
{
    for(int i=0;i<=n;i++) 
    	f[i] = i;
    int tot = 0;
    for(int i=1;i<m;i++)
    {
        if(edge[i].c1 > x)
        	continue;
        int fx = find(edge[i].u);
        int fy = find(edge[i].v);
        if(fx^fy)
        {
            f[fy] = fx;
            tot++;
        }
    }
    if(tot < k) 
    	return false;
    for(int i=1;i<m;i++)
    {
        if(edge[i].c2 > x) continue;
        int fx = find(edge[i].u);
        int fy = find(edge[i].v);
        if(fx != fy)
        {
            f[fx] = fy;
            tot++;
        }
    }
    if(tot<n-1) 
    	return false;
    return true;
}
int main()
{
    n = read(), k = read(), m = read();
    for(int i=1;i<m;i++)
    {
        edge[i].u = read();
        edge[i].v = read();
        edge[i].c1 = read();
        edge[i].c2 = read();
    }
    int l = 0, r = 30001, ans;
    while(l <= r)
    {
        int mid=(l + r)>>1;
        if(check(mid))
        {
            ans = mid;
            r = mid-1;
        }
        else l=mid+1;
    }
    printf("%d\n", ans);
    return 0;
}
