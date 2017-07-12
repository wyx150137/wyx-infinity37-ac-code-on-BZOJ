
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 60
#define inf 0x3f3f3f3f
using namespace std;
int n,m,a[N],ans;
bool check(int mid)
{
    int remain=min(m,mid);
    for(int i=1;i<=n;i++)
    {
        if(a[i]>=mid)continue;
        remain-=mid-a[i];
        if(remain<0)return 0;
    }
    return 1;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    int l=0,r=inf,mid,ans;
    while(l<=r)
    {
        if(r-l<=3)
        {
            ans=0;
            for(int i=l;i<=r;i++)
                if(check(i))ans=i;
            printf("%d\n",ans);
            return 0;
        }
        mid=(l+r)>>1;
        if(check(mid))l=mid;
        else r=mid-1;
    }
    printf("%d\n",ans);
    return 0;
}
