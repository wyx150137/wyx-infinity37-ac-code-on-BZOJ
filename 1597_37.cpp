
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long LL;
const int N = 50005;
struct LAND{int wid,lth;}ld[N];
int line[N],L,R;
int l[N],w[N];
LL f[N];
bool cmp(LAND a,LAND b)
{
    if(a.lth!=b.lth)return a.lth>b.lth;
    return a.wid<b.wid;
}
int main()
{
    int n;
    scanf("%d",&n);
    for(int i = 1;i<= n;i++)
        scanf("%d%d",&ld[i].wid,&ld[i].lth);
    sort(ld+1,ld+n+1,cmp);
    int cnt = 0;
    for(int i = 1;i<= n;i++)
    {
        if(cnt==0||ld[i].wid>w[cnt])
        {
            cnt++;
            w[cnt] = ld[i].wid;
            l[cnt] = ld[i].lth;
        }
    }
    int L = 1,R = 1;line[L] =0;
    for(int i = 1;i<= cnt;i++)
    {
        while(L<R&&(LL)(l[line[L+1]+1]-l[line[L]+1])*w[i]<f[line[L]]-f[line[L+1]])
            L++;
        f[i] = f[line[L]]+(LL)l[line[L]+1]*w[i];
        while(L<R&&(LL)(l[line[R]+1]-l[i+1])*(f[line[R]]-f[line[R-1]])>(LL)(l[line[R-1]+1]-l[line[R]+1])*(f[i]-f[line[R]]))
            R--;
        line[++R] = i;
    }
    printf("%lld\n",f[cnt]);
    return 0;
}
