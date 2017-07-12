
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#define N 100+5
#define MAXN 500001
#define inf 10000000
using namespace std;
int f[MAXN],w[N],c[N],n,m;
inline int read()
{
    int x = 0, f = 1; char ch = getchar();
    while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar(); }
    while (ch >= '0' && ch <= '9') { x = x * 10 + ch - '0'; ch = getchar(); }
    return x * f;
}
int main()
{
    memset(f,0x3f,sizeof f);f[0]=0;
    cin>>n>>m;
    for(int i=1;i<=n;++i)w[i]=read(),c[i]=read();
    for(int i=1;i<=n;++i)
        for(int j=w[i];j<=m+5000;++j)
            f[j]=min(f[j],f[j-w[i]]+c[i]);
    int ans=inf;
    for(int i=m;i<=m+5000;++i)ans=min(ans,f[i]);
    cout<<ans;
}
