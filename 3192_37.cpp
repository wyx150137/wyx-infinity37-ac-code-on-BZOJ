
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
struct P
{
    int tt,no,ss;
}num[100005];
int pos[100005],c[100005],lim;
bool cmp1(P a,P b){return a.tt<b.tt;}
bool cmp2(P a,P b){return a.no<b.no;}
void update(int x)
{
    for(int i = x;i<=lim;i+=(i&(-i)))
        c[i]--;
}
int check(int x)
{
    int ans = 0;
    for(int i = x;i>0;i-=(i&(-i)))
        ans+=c[i];
    return ans;
}
int main()
{
    //freopen("all.in", "r", stdin);
    //freopen("all.out", "w", stdout);
    int n,m,x;
    scanf("%d%d",&n,&m);
    lim = n+m;
    int cnt = 0;
    for(int i = 1;i<=n;i++)
    {
        scanf("%d",&x);
        cnt++;num[cnt].tt = x;num[cnt].no = n-i;
    }
    for(int i = 1;i<= m;i++)
    {
        scanf("%d",&x);
        cnt++;num[cnt].tt = x;num[cnt].no = n+i;
    }
    sort(num+1,num+cnt+1,cmp1);
    for(int i = 1;i<= cnt;i++)
        num[i].ss = i;
    sort(num+1,num+cnt+1,cmp2);
    for(int i = 1;i<= cnt;i++)
        pos[num[i].ss] = i;
    //p_n为n与n+1之间的
    for(int i = 1;i<= lim;i++)
        c[i] = i&(-i);
    int p = n;int now = n+m;long long ans = 0;
    while(now>0)
    {
        int tmp = check(p);
        if(pos[now]>p)
        {
            ans += check(pos[now]-1)-tmp;
            p = pos[now]-1;
            update(pos[now]);
        }else
        {
            ans += tmp-check(pos[now]);
            p = pos[now];
            update(pos[now]);
        }
        now--;
    }
    printf("%lld",ans);
    return 0;
}
