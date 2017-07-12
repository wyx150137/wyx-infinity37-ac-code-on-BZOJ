
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
const int N = 1e6+5;
typedef long long ll;
using namespace std;
struct aa{int l, r;}a[N], b[N];
int n, now, mxp, l, flag[N];
ll ans;
bool cmp(aa a, aa b)
{
    if(a.l!=b.l)return a.l<b.l;
    return a.r>b.r;
}
ll get(int i, int j)
{
    if(b[i].r<b[j].l)return 0;
    return (ll)(b[i].r-b[j].l+1)*(b[j].r-b[i].l+1);
}
int main()
{
    scanf("%d",&n);
    for(int i=1; i<=n; i++)
    {
    	scanf("%d%d",&a[i].l,&a[i].r);
    	a[i].r--;
    }
    sort(a+1, a+1+n, cmp);
    now=mxp=ans=0;
    for(int i=1; i<=n; i++)
    {
        if(a[i].r<=now)
        {
            flag[i]=mxp;
            ans=max(ans, (ll)(a[i].r-a[i].l+1)*(a[mxp].r-a[mxp].l+1));
        }
        else flag[i]=0;
        if(now<a[i].r){now=a[i].r; mxp=i;}
    }
    l=0;
    for(int i=1; i<=n; i++)if(!flag[i])b[++l]=a[i];
    now=2;
    for(int i=1; i<=l-1; i++)
    {
        if(now==i)now++;
        while(now<=l-1&&get(i, now)<get(i, now+1))now++;
        ans=max(ans, get(i, now));
    }
    printf("%lld", ans);
    return 0;
}
