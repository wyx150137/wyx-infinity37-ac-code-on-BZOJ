
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long LL;
const int N = 1000005;
LL sum[N];
LL f[N];
int Q[N],L,R,n,a,b,c,x;
LL Y(int x)
{
    return f[x]+sum[x]*sum[x]*a;
}
int main()
{
    //memset(f,128,sizeof(f));
    scanf("%d%d%d%d",&n,&a,&b,&c);
    for(int i = 1;i<= n;i++)
    {
        scanf("%d",&x);
        sum[i] = sum[i-1]+x;
    }
    L = R = 1;
    Q[L] = 0;
    for(int i = 1;i<= n;i++)
    {
        while(L<R&&-(sum[i]*2*a+b)>(double)(Y(Q[L])-Y(Q[L+1]))/(double)(sum[Q[L+1]]-sum[Q[L]]))
            L++;
        f[i] = f[Q[L]]+
               (sum[i]-sum[Q[L]])*(sum[i]-sum[Q[L]])*a+(sum[i]-sum[Q[L]])*b+c;
        while(L<R&&(double)(Y(Q[R-1])-Y(Q[R]))/(double)(sum[Q[R]]-sum[Q[R-1]])>(double)(Y(Q[R])-Y(i))/(double)(sum[i]-sum[Q[R]]))
            R--;
        Q[++R] = i;
    }
    printf("%lld",f[n]);
    return 0;
}
