
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long LL;
const int N = 1e5+5;
const int mod1 = 130117;
const int mod2 = 600011;
const int seed = 37;
int a[N<<1], b[N<<1], sum[N<<1][2], num[N<<1][2], mi[N<<1][2], F[N<<1], G[N<<1];
int n, m, ans, l, r;
bool judge(int l1,int r1,int l2,int r2) 
{
    int x,y;
    int mod = mod1;
    x = (LL)(sum[r1][0]-(LL)sum[l1-1][0]*mi[r1-l1+1][0]%mod)%mod;
    y = (LL)(num[l2][0]-(LL)num[r2+1][0]*mi[r2-l2+1][0]%mod)%mod;
    (x+=mod)%=mod, (y+=mod)%=mod;
    if(x!=y) return 0;
    mod = mod2;
    x = (LL)(sum[r1][1]-(LL)sum[l1-1][1]*mi[r1-l1+1][1]%mod)%mod;
    y = (LL)(num[l2][1]-(LL)num[r2+1][1]*mi[r2-l2+1][1]%mod)%mod;
    (x+=mod)%=mod, (y+=mod)%=mod;
    if(x!=y) return 0;
    return 1;
}
inline int solve(int j,int k) 
{
    int l = 0, r = min( j, n-k+1);
    while(l < r) 
    {
        int mid = (l+r+1)>>1;
        if(judge(j-mid+1,j,k,k+mid-1)) l = mid;
        else r = mid - 1;
    }
    return l;
}
char s[N];
int main() 
{
    scanf("%d",&n);
    mi[0][0] = mi[0][1] = 1;
    for(int i=1;i<=n;++i) 
    {
        mi[i][0] = (LL)mi[i-1][0]*seed%mod1;
        mi[i][1] = (LL)mi[i-1][1]*seed%mod2;
    }
    a[0] = b[0] = 0; 
    a[2*n+2] = b[2*n+2] = 28;
    a[1] = b[1] = 27;
    scanf("%s",s+1);
    for(int i=1;i<=n;++i) 
        a[i<<1] = s[i] - 'A' + 1,a[i<<1|1] = 27;
    scanf("%s",s+1);
    for(int i=1;i<=n;++i) 
        b[i<<1] = s[i] - 'A' + 1,b[i<<1|1] = 27;
    int j = 0;
    for(int i=2;i<=(n<<1);++i) 
    {
        if(i <= F[j]+j) F[i] = min(F[2*j-i],j+F[j]-i);
        while(a[i-F[i]-1] == a[i+F[i]+1]) F[i] ++;
        if(i+F[i]>j+F[j]) j = i;
    }
    j = 0;
    for(int i=2;i<=(n<<1);++i) 
    {
        if(i <= j+G[j]) G[i] = min(G[2*j-i],j+G[j]-i);
        while(b[i-G[i]-1] == b[i+G[i]+1]) G[i] ++;
        if(i+G[i]>j+G[j]) j = i;
    }
    for(int i=2;i<=(n<<1);++i) ans = max(ans,max(F[i],G[i]));
    for(int i=1;i<=n;++i) 
    {
        sum[i][0] = (LL)((LL)sum[i-1][0]*seed%mod1+a[i<<1])%mod1;
        sum[i][1] = (LL)((LL)sum[i-1][1]*seed%mod2+a[i<<1])%mod2;
    }
    for(int i=n;i>=1;--i) 
    {
        num[i][0] = (LL)((LL)num[i+1][0]*seed%mod1+b[i<<1])%mod1;
        num[i][1] = (LL)((LL)num[i+1][1]*seed%mod2+b[i<<1])%mod2;
    }
    for(int i=2;i<=(n<<1);++i) 
    {
        l = i - F[i], r = i + F[i];
        l = (l+1) >> 1; r >>= 1;
        ans = max(ans,F[i]+solve(l-1,r)*2);
    }
    for(int i=2;i<=(n<<1);++i) 
    {
        l = i - G[i], r = i + G[i];
        l = (l+1) >> 1, r >>= 1;
        ans = max(ans,G[i]+solve(l,r+1)*2);
    }
    printf("%d\n",ans);
}
